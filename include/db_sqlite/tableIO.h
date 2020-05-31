#pragma once

#include "SQLiteCpp/SQLiteCpp.h"
#include <string>
#include <vector>

namespace S4{
namespace sqlite{

//T: type of single line in table
template <typename T>
class tableIO_t{
public:
    //db table name
	// virtual const std::string & get_name(void) const = 0;
    virtual static const std::string & get_query_build(void) const = 0;
    virtual static const std::string & get_query_insert(void) const = 0;
	// virtual void set_name(const std::string&) = 0;
    // virtual size_t get_size(void) const = 0;

	typedef std::vector<T>::iterator iter;
	typedef std::vector<T>::const_iterator const_iter;
	
	// virtual iter begin(void) = 0;
	// virtual iter end(void) = 0;

	virtual static void bind_query(SQLite::Statement & query, const_iter& nb) = 0;
	virtual static void load_query(SQLite::Statement & query, std::vector<T>& data) = 0;
	// virtual void load_query(const std::string json) = 0;
};

}
}
