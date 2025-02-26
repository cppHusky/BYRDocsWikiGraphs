#include<cstdlib>
#include<exception>
#include<format>
#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include"wiki.hpp"
int main(){
	try{
		const std::string api="https://wiki.byrdocs.org/api.php";
		const std::list<std::string> header{std::format("X-Byrdocs-Token:{}",std::getenv("WIKITOKEN"))};
		const std::string login_token=wiki::get_login_token(api,"/tmp/wiki_login_cookies",header);
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
