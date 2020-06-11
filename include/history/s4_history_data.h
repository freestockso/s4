#include "jsonTypes/s4_history_t.h"
#include "db_sqlite/db.h"

namespace S4{

bool history_data_to_DB(S4::sqlite::DB_t& history_db, const std::string& table_name, const std::vector<s4_history_t>& history_data);


    
} // namespace S4