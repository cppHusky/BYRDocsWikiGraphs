#include<cstdlib>
#include<exception>
#include<filesystem>
#include<format>
#include<fstream>
#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include"wiki.hpp"
const std::string API="https://wiki.byrdocs.org/api.php";
const std::string LOGIN="/tmp/wiki_login_cookies";
const std::string CSRF="/tmp/wiki_csrf_cookies";
const std::list<std::string> HEADER{std::format("X-Byrdocs-Token:{}",std::getenv("WIKITOKEN"))};
int main(int argc,char *argv[]){
	try{
		if(argc!=2){
			std::cout<<std::format(R"(Usage: {} <path-to-file>)",argv[0])<<std::endl;
			return 1;
		}
		std::string file_path{argv[1]};
		std::filesystem::path fs_path{file_path};
		std::clog<<"Logging in... ";
		const std::string login_token=wiki::get_login_token(API,LOGIN,HEADER);
		wiki::login(
			API,
			LOGIN,
			"CppHusky@uploader",
			std::getenv("WIKIPASS_UPLOADER"),
			login_token,
			HEADER
		);
		std::clog<<"Logged in."<<std::endl;
		std::clog<<std::format("Started uploading {}...",argv[1])<<std::endl;
		const std::string csrf_token=wiki::get_csrf_token(API,LOGIN,CSRF,HEADER);
		if(!std::filesystem::exists(fs_path)){
			std::cerr<<std::format("{}: file does not exist.",file_path)<<std::endl;
			return 2;
		}
		if(std::filesystem::is_directory(fs_path)){
			std::cerr<<std::format("{}: is a directory.",file_path)<<std::endl;
			return 3;
		}
		std::string filename{std::filesystem::path{file_path}.filename()};
		nlohmann::json result=wiki::upload(
			API,
			CSRF,
			filename,
			file_path,
			csrf_token,
			HEADER
		);
		if(result["upload"]["result"]!="Success"){
			std::clog<<"The uploader bot encountered a non-success result. See the log in current directory for more information."<<std::endl;
			std::ofstream logs{std::format("{}.log",filename)};
			logs<<result<<std::endl;
		}
		else
			std::clog<<std::format(
				"Success. See https://wiki.byrdocs.org/w/文件:{} for details.",
				filename
			)<<std::endl;
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
