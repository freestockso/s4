#include "db_sqlite/db.h"
#include "types/s4convertors.h"


namespace S4 {
namespace sqlite {

DB_t::DB_t(const std::string & name, const int Mode):
	mDb(name, Mode),
	m_name(name)
{
	//INFO( "SQLite database file '{}' opened successfully", mDb.getFilename().c_str());

	//mDb.exec("PRAGMA auto_vacuum = 1");
	mDb.exec("PRAGMA temp_store = MEMORY");
	mDb.exec("PRAGMA page_size = 65536");
	mDb.exec("PRAGMA cache_size = 8000");
	//mDb.exec("PRAGMA synchronous = OFF");
	// Test if the 'test' table exists
	// const bool bExists = db.tableExists("test");
	// std::cout << "SQLite table 'test' exists=" << bExists << "\n";
}

//s3stk_sh0.db3  : sh000000 ~sh600999
//s3stk_sh1.db3 : sh601000 ~
//
//s3stk_sz0.db3 : sz000000 ~sz002399
//s3stk_sz1.db3 : sz002400 ~sz299999
//s3stk_sz2.db3 : sz300000 ~
history_data_DB_group_t::history_data_DB_group_t(const std::string & path, const int Mode)
{
	_dbLib.insert(std::pair<const std::string, std::shared_ptr<DB_t>>(std::string("sh0"), std::make_shared<DB_t>(path + "s3stk_sh0.db", Mode)));
	_dbLib.insert(std::pair<const std::string, std::shared_ptr<DB_t>>(std::string("sh1"), std::make_shared<DB_t>(path + "s3stk_sh1.db", Mode)));
	_dbLib.insert(std::pair<const std::string, std::shared_ptr<DB_t>>(std::string("sz0"), std::make_shared<DB_t>(path + "s3stk_sz0.db", Mode)));
	_dbLib.insert(std::pair<const std::string, std::shared_ptr<DB_t>>(std::string("sz1"), std::make_shared<DB_t>(path + "s3stk_sz1.db", Mode)));
	_dbLib.insert(std::pair<const std::string, std::shared_ptr<DB_t>>(std::string("sz2"), std::make_shared<DB_t>(path + "s3stk_sz2.db", Mode)));
}

const std::string history_data_DB_group_t::mapTable_to_db(const std::string& tblName) const
{
	std::string mk = tblName.substr(0, 2);
	if (mk != "sz" && mk != "sh") {
		throw SqliteDBError("Unknow market name:" + mk + " in tableName:" + tblName);
	}
	int ins = static_cast<int>(IntConvertor::convert(tblName.substr(2, 6)));

	if (mk == "sh") {
		if (ins < 601000) {
			return "sh0";
		}
		else {
			return "sh1";
		}
	}
	else if (mk == "sz") {
		if (ins < 2400) {
			return "sz0";
		}
		else if (ins < 300000) {
			return "sz1";
		}
		else {
			return "sz2";
		}
	}

	throw SqliteDBError("Unknow tableName:" + tblName);
}

}
}