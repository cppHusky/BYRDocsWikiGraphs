#include<cstdlib>
#include<exception>
#include<format>
#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include"wiki.hpp"
int main(){
	try{
		const std::string API="http://localhost:8080/api.php";
		const std::string login_token=wiki::get_login_token(API,"/tmp/wiki_login_cookies");
		wiki::login(
			API,
			"/tmp/wiki_login_cookies",
			"CppHusky@uploader",
			std::getenv("WIKIPASS_UPLOADER"),
			login_token
		);
		const std::string csrf_token=wiki::get_csrf_token(API,"/tmp/wiki_login_cookies","/tmp/wiki_csrf_cookies");
		std::clog<<csrf_token<<std::endl;
		assert(csrf_token.length()==42);
		assert(csrf_token.ends_with("+\\"));
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
