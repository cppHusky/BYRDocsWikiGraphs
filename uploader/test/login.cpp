#include<cstdlib>
#include<exception>
#include<format>
#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include"wiki.hpp"
const std::string API="http://localhost:8080/api.php";
int main(){
	try{
		const std::string login_token=wiki::get_login_token(API,"/tmp/wiki_login_cookies");
		const nlohmann::json result=nlohmann::json::parse(wiki::login(
			API,
			"/tmp/wiki_login_cookies",
			"CppHusky@uploader",
			std::getenv("WIKIPASS_UPLOADER"),
			login_token
		));
		std::clog<<result<<std::endl;
		assert(result["login"]["result"]=="Success");
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
