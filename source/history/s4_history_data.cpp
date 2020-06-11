#include "history/s4_history_data.h"
#include "jsonTypes/s4_history_t_dbTbl.h"

CREATE_LOCAL_LOGGER("history")

namespace S4{

bool history_data_to_DB(S4::sqlite::DB_t& history_db, const std::string& table_name, const std::vector<s4_history_t>& history_data)
{
    
	S4::sqlite::s4_history_t_dbTbl history_tbl;
	history_db.to_table<S4::sqlite::s4_history_t_dbTbl::data_t>(&history_tbl, table_name, history_data);

	std::vector<S4::s4_history_t> history_rd;
	history_db.read_table< S4::sqlite::s4_history_t_dbTbl::data_t>(&history_tbl, table_name, history_rd);

	if (history_data.size() != history_rd.size()) {
		LCL_ERR("deal DB write - read unequal! w.size={:}, r.size={:}", history_data.size(), history_rd.size());
	}
	for (size_t i = 0; i < history_data.size(); ++i) {
		bool match = false;
		for (size_t j = 0; j < history_rd.size(); ++j) {
			if (history_data[i] == history_rd[j]) {
				LCL_INFO("deal DB write - read OK! w[{:}] == r[{:}]", i, j);
				match = true;
				break;
			}
		}
		if (!match) {
			LCL_ERR("deal DB write - read unequal! w[{:}] not found", i);		//as example, 8 and 9 are unequal for reordered by DB
		}
	}
	return true;
}
    
} // namespace S4
