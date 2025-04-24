#include<cstdlib>
#include<exception>
#include<format>
#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include"wiki.hpp"
const std::string API="http://localhost:8080/api.php";
const std::string LOGIN="/tmp/wiki_login_cookies";
const std::string CSRF="/tmp/wiki_csrf_cookies";
int main(){
	try{
		const std::string login_token=wiki::get_login_token(API,LOGIN);
		wiki::login(
			API,
			LOGIN,
			"CppHusky@uploader",
			std::getenv("WIKIPASS_UPLOADER"),
			login_token
		);
		const std::string csrf_token=wiki::get_csrf_token(API,LOGIN,CSRF);
		const nlohmann::json result=wiki::upload(
			API,
			CSRF,
			"24-25-大学物理（下）-期中-第一题图.svg",
			"24-25-大学物理（下）-期中-第一题图.svg",
			csrf_token
		);
		assert(result["upload"]["result"]=="Warning");
		assert(result["upload"].find("warnings")!=result["upload"].end());
	}catch(const curlpp::RuntimeError &e){
		std::cerr<<e.what()<<std::endl;
		assert(false);
	}catch(const curlpp::LogicError &e){
		std::cerr<<e.what()<<std::endl;
		assert(false);
	}catch(const std::exception &e){
		std::cerr<<e.what()<<std::endl;
		assert(false);
	}
}
