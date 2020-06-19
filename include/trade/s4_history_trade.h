#include "jsonTypes/s4_history_trade_t.h"
#include "db_sqlite/db.h"

namespace S4{

bool history_trade_to_DB(const std::vector<s4_history_trade_t>& history_trade_data, S4::sqlite::DB_t& history_db, const std::string& table_name);


    
} // namespace S4