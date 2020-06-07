#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>

namespace S4{
namespace sqlite{

//T: type of single line in table
template <typename T>
class tableIO_t{
public:
	//db table name
	virtual void set_name(const std::string& name) { m_name = name; }	//query_build / insert need table name
	virtual const std::string& get_name(void) const { return m_name; }
    virtual const std::string & get_query_build(void) const = 0;
    virtual const std::string & get_query_insert(void) const = 0;
    // virtual size_t get_size(void) const = 0;

	//typedef std::vector<T>::iterator iter;
	//typedef std::vector<T>::const_iterator const_iter;
	
	// virtual iter begin(void) = 0;
	// virtual iter end(void) = 0;

	virtual void bind_query(SQLite::Statement & query, const std::vector<T>& data, size_t nb) = 0;
	virtual void load_query(SQLite::Statement & query, std::vector<T>& data) = 0;
	// virtual void load_query(const std::string json) = 0;
protected:
	std::string m_name;
};

}
}
