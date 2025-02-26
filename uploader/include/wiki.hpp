#pragma once
#include<list>
#include<string>
#include<curlpp/Easy.hpp>
#include<nlohmann/json.hpp>
namespace wiki{
std::string get(curlpp::Easy &request);
std::string get(const std::string &url,const std::list<std::string> &header={});
std::string get(const std::string &url,const std::string &cookiejar_path,const std::list<std::string> &header={});
std::string get_token(const std::string &url,const std::string &cookiejar_path,const std::list<std::string> &header={});
std::string login(const std::string &url,const std::string &cookie_path,const std::string &username,const std::string &password,const std::string &login_token,const std::list<std::string> &header={});
}
