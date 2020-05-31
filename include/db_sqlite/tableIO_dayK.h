#ifndef _S3_SQLITE_TBL_DAYK_H_
#define _S3_SQLITE_TBL_DAYK_H_

#include "types/s4type.h"
#include "db_sqlite/db.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include <vector>

class dbTbl_dayK_t : public dbTble_t<size_t>{
public:
	//code: sz000997 -> tbl_name=sz000997_day
	dbTbl_dayK_t(const std::string code);

	virtual void set_name(const std::string& name);
    
    void setDataIO(vec_dayK_t & Kque){ m_Kque = &Kque;};

	const std::string & get_name(void) const { return m_name;  };

    const std::string & get_query_build(void) const { return m_qurey_build;};

    const std::string & get_query_insert(void) const { return m_qurey_insert;};
    
    size_t get_size(void) const { 
        if(m_Kque==NULL) return 0;
        return m_Kque->size(); 
    };

	iter begin(void) { return 0; };
	iter end(void) { return m_Kque->size(); };

    void bind_query(SQLite::Statement & query, iter nb);
    void load_query(SQLite::Statement & query, const std::vector<std::string> * cols=NULL);
private:
	std::string m_name;
    std::string m_qurey_build;
    std::string m_qurey_insert;

	vec_dayK_t * m_Kque;

};



#endif