#include<cstdlib>
#include<exception>
#include<format>
#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include"wiki.hpp"
int main(){
	try{
		const std::string api="http://localhost/api.php";
		const std::string login_token=wiki::get_login_token(api,"/tmp/wiki_login_cookies");
		const nlohmann::json result=nlohmann::json::parse(wiki::login(api,"/tmp/wiki_login_cookies","CppHusky@uploader",std::getenv("WIKIPASS_UPLOADER"),login_token));
		const std::string csrf_token=wiki::get_csrf_token(api,"/tmp/wiki_login_cookies");
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
