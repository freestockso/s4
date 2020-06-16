#pragma once

#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include "common/s4logger.h"

namespace S4{

using json = nlohmann::json;
typedef std::shared_ptr<json> json_ptr_t;
inline json_ptr_t make_json_ptr(void) {
	return std::make_shared<json>();
}

inline std::shared_ptr<nlohmann::json> readJsonFile(const std::string& filename){
	std::fstream in(filename.c_str());
	std::ostringstream tmp;
 
    std::shared_ptr<nlohmann::json> ret(new nlohmann::json);

	if(!in)
	{
        return std::move(ret);
	}
	else
	{
		tmp << in.rdbuf();

		try
		{
			ret = std::make_shared<json>(nlohmann::json::parse(tmp.str()));
		}
		catch (nlohmann::json::parse_error& e)
		{
			// output exception information
			 ERR("json parse fail:{:}\nerrorInfo:{:}\nexception id:{:}\nbyte position of error:{:}",
			 	tmp.str(), e.what(), e.id, e.byte);
		}
	}

	return std::move(ret);
}


#define JSON_NO_START       -1
#define JSON_WAITING_STOP   -2
#define JSON_ILLEGAL_STOP   -3


bool searchJson(std::string str, int & start, int & stop, int* ec=nullptr);

}//namespace S4
