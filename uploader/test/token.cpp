#include<exception>
#include<format>
#include<iostream>
#include<list>
#include<string>
#include<nlohmann/json.hpp>
#include"wiki.hpp"
int main(){
	try{
		const std::string api="http://localhost/api.php?";
		const std::string login_token=wiki::get_token(api+"format=json&action=query&meta=tokens&type=*","/tmp/wiki_login_token");
		std::clog<<login_token<<std::endl;
		assert(login_token.length()==42);
		assert(login_token.ends_with("+\\"));
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
