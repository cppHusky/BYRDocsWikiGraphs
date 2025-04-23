#pragma once
#include<list>
#include<string>
#include<curlpp/Easy.hpp>
#include<nlohmann/json.hpp>
namespace wiki{
std::string get(curlpp::Easy &request);
void init_request(curlpp::Easy &request,const std::string &url,const std::vector<std::pair<std::string,std::string>> &formstr,const std::list<std::string> &header={});
std::string get_login_token(const std::string &api,const std::string &cookiejar_path,const std::list<std::string> &header={});
std::string get_csrf_token(const std::string &api,const std::string &login_cookie_path,const std::string &csrf_cookie_path,const std::list<std::string> &header={});
std::string login(const std::string &api,const std::string &cookie_path,const std::string &username,const std::string &password,const std::string &login_token,const std::list<std::string> &header={});
nlohmann::json upload(const std::string &api,const std::string &cookie_path,const std::string &file_name,const std::string &file_path,const std::string &csrf_token,const std::list<std::string> &header={});
}
