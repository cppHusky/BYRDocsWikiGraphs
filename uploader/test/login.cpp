#include<cstdlib>
#include<exception>
#include<format>
#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include"wiki.hpp"
int main(){
	try{
		const std::string api="http://localhost/api.php?";
		const std::string login_token=wiki::get_token(api+"format=json&action=query&meta=tokens&type=login","/tmp/wiki_login_token");
		const nlohmann::json result=nlohmann::json::parse(wiki::login(api+"format=json&action=login","/tmp/wiki_login_token","CppHusky@uploader",std::getenv("WIKIPASS_UPLOADER"),login_token));
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
