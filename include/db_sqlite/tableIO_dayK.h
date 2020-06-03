#pragma once

#include "types/s4type.h"
#include "db_sqlite/tableIO.h"

#include <vector>

namespace S4 {
namespace sqlite {


class dbTbl_dayK_t : public tableIO_t<struct dayK_t>{
public:
	//code: sz000997 -> tbl_name=sz000997_day
	dbTbl_dayK_t(const std::string code);
    
    //name: sz000997 -> tbl_name=sz000997_day
	virtual void set_name(const std::string& name) override;

    virtual const std::string & get_query_build(void) const override { return m_qurey_build;};

    virtual const std::string & get_query_insert(void) const override { return m_qurey_insert;};
    
    virtual void bind_query(SQLite::Statement& query, const std::vector<struct dayK_t>& data, size_t nb) override;
    virtual void load_query(SQLite::Statement& query, std::vector<dayK_t>& data) override;
private:
	std::string m_name;
    std::string m_qurey_build;
    std::string m_qurey_insert;

};

}
}

