#include<stdexcept>
#include<format>
#include<fstream>
#include<list>
#include<sstream>
#include<string>
#include<system_error>
#include<curlpp/cURLpp.hpp>
#include<curlpp/Easy.hpp>
#include<curlpp/Form.hpp>
#include<curlpp/Options.hpp>
#include<nlohmann/json.hpp>
#include"wiki.hpp"
std::string wiki::get(curlpp::Easy &request){
	std::stringstream response;
	request.setOpt<curlpp::Options::WriteStream>(&response);
	request.perform();
	return response.str();
}
void wiki::init_request(curlpp::Easy &request,const std::string &url,const std::vector<std::pair<std::string,std::string>> &formstr,const std::list<std::string> &header){
	request.setOpt<curlpp::Options::Url>(url);
	request.setOpt<curlpp::Options::HttpHeader>(header);
	curlpp::Forms form;
	for(const std::pair<std::string,std::string> &it:formstr)
		form.push_back(new curlpp::FormParts::Content(it.first,it.second));
	request.setOpt<curlpp::Options::HttpPost>(form);
}
std::string wiki::get_login_token(const std::string &api,const std::string &cookiejar_path,const std::list<std::string> &header){
	curlpp::Easy request;
	request.setOpt<curlpp::Options::CookieJar>(cookiejar_path);
	request.setOpt<curlpp::Options::HttpHeader>(header);
	init_request(
		request,
		api+"?format=json",
		{{"action","query"},{"meta","tokens"},{"type","login"}},
		header
	);
	nlohmann::json response=nlohmann::json::parse(wiki::get(request));
	return response["query"]["tokens"]["logintoken"];
}
std::string wiki::get_csrf_token(const std::string &api,const std::string &login_cookie_path,const std::string &csrf_cookie_path,const std::list<std::string> &header){
	curlpp::Easy request;
	request.setOpt<curlpp::Options::CookieFile>(login_cookie_path);
	request.setOpt<curlpp::Options::CookieJar>(csrf_cookie_path);
	request.setOpt<curlpp::Options::HttpHeader>(header);
	init_request(
		request,
		api+"?format=json",
		{{"action","query"},{"meta","tokens"},{"type","csrf"}},
		header
	);
	nlohmann::json response=nlohmann::json::parse(wiki::get(request));
	return response["query"]["tokens"]["csrftoken"];
}
std::string wiki::login(const std::string &api,const std::string &cookie_path,const std::string &username,const std::string &password,const std::string &login_token,const std::list<std::string> &header){
	curlpp::Easy request;
	request.setOpt<curlpp::Options::CookieFile>(cookie_path);
	request.setOpt<curlpp::Options::CookieJar>(cookie_path);
	init_request(
		request,
		api+"?format=json",
		{{"action","login"},{"lgname",username},{"lgpassword",password},{"lgtoken",login_token}},
		header
	);
	return wiki::get(request);
}
nlohmann::json wiki::upload(const std::string &api,const std::string &cookie_path,const std::string &file_name,const std::string &file_path,const std::string &csrf_token,const std::list<std::string> &header){
	curlpp::Easy request;
	std::ifstream file{file_path,std::ios::in|std::ios::binary};
	if(!file)
		throw std::runtime_error{std::format("Error: {} doesn't exist.",file_path)};
	request.setOpt<curlpp::Options::Url>(api+"?format=json");
	request.setOpt<curlpp::Options::CookieFile>(cookie_path);
	request.setOpt<curlpp::Options::ReadStream>(&file);
	request.setOpt<curlpp::Options::Upload>(true);
	curlpp::Forms form;
	form.push_back(new curlpp::FormParts::Content("action","upload"));
	form.push_back(new curlpp::FormParts::Content("filename",file_name));
	form.push_back(new curlpp::FormParts::File("file",file_path));
	form.push_back(new curlpp::FormParts::Content("token",csrf_token));
	request.setOpt<curlpp::Options::HttpPost>(form);
	request.setOpt<curlpp::Options::HttpHeader>(header);
	nlohmann::json response=nlohmann::json::parse(wiki::get(request));
	return response;
}
