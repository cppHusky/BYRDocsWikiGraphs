#include<format>
#include<list>
#include<sstream>
#include<string>
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
std::string wiki::get(const std::string &url,const std::list<std::string> &header){
	curlpp::Easy request;
	request.setOpt<curlpp::Options::Url>(url);
	request.setOpt<curlpp::Options::HttpHeader>(header);
	return get(request);
}
std::string wiki::get(const std::string &url,const std::string &cookiejar_path,const std::list<std::string> &header){
	curlpp::Easy request;
	request.setOpt<curlpp::Options::Url>(url);
	request.setOpt<curlpp::Options::CookieJar>(cookiejar_path);
	request.setOpt<curlpp::Options::HttpHeader>(header);
	return get(request);
}
std::string wiki::get_token(const std::string &url,const std::string &cookiejar_path,const std::list<std::string> &header){
	nlohmann::json response=nlohmann::json::parse(wiki::get(url,cookiejar_path,header));
	const std::string token=response["query"]["tokens"]["logintoken"];
	return token;
}
std::string wiki::login(const std::string &url,const std::string &cookie_path,const std::string &username,const std::string &password,const std::string &login_token,const std::list<std::string> &header){
	curlpp::Easy request;
	request.setOpt<curlpp::Options::Url>(url);
	request.setOpt<curlpp::Options::CookieFile>(cookie_path);
	request.setOpt<curlpp::Options::CookieJar>(cookie_path);
	curlpp::Forms form;
	form.push_back(new curlpp::FormParts::Content("format","json"));
	form.push_back(new curlpp::FormParts::Content("action","login"));
	form.push_back(new curlpp::FormParts::Content("lgname",username));
	form.push_back(new curlpp::FormParts::Content("lgpassword",password));
	form.push_back(new curlpp::FormParts::Content("lgtoken",login_token));
	request.setOpt<curlpp::Options::HttpPost>(form);
	request.setOpt<curlpp::Options::HttpHeader>(header);
	return wiki::get(request);
}
