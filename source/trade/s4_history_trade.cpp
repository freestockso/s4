#include "trade/s4_history_trade.h"
#include "jsonTypes/s4_history_trade_t_dbTbl.h"

CREATE_LOCAL_LOGGER("history")

namespace S4{

bool history_trade_to_DB(const std::vector<s4_history_trade_t>& history_trade_data, 
						S4::sqlite::DB_t& history_db, const std::string& table_name)
{
    
	S4::sqlite::s4_history_trade_t_dbTbl history_tbl;
	history_db.to_table<S4::sqlite::s4_history_trade_t_dbTbl::data_t>(&history_tbl, table_name, history_trade_data);

	std::vector<S4::s4_history_trade_t> history_rd;
	history_db.read_table< S4::sqlite::s4_history_trade_t_dbTbl::data_t>(&history_tbl, table_name, history_rd);

	if (history_trade_data.size() != history_rd.size()) {
		LCL_ERR("deal DB write - read unequal! w.size={:}, r.size={:}", history_trade_data.size(), history_rd.size());
	}
	for (size_t i = 0; i < history_trade_data.size(); ++i) {
		bool match = false;
		for (size_t j = 0; j < history_rd.size(); ++j) {
			if (history_trade_data[i] == history_rd[j]) {
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
    
//return false: cannot compare
static
bool history_trade_compare_early(const s4_history_trade_t& a, const s4_history_trade_t& b, bool& a_isEarly)
{
	if (a.mktCodeStr != b.mktCodeStr){
		return false;
	}
	
	if (a.time_utcSec < b.time_utcSec){
		a_isEarly = true;
		return true;
	}
	if (a.time_utcSec > b.time_utcSec){
		a_isEarly = false;
		return true;
	}
	
	//time_utcSec == time_utcSec
	if (a.optType < b.optType){
		a_isEarly = true;
		return true;
	}
	if (a.optType > b.optType){
		a_isEarly = false;
		return true;
	}

	return false;
}

//
void sort_history_trade(std::vector<s4_history_trade_t>& history_trade_data)
{
	bool early;
	for (size_t i=0; i+1< history_trade_data.size(); ++i){
		for (size_t j=i+1; j< history_trade_data.size(); ++j){
			if ( history_trade_compare_early(history_trade_data[i], history_trade_data[j], early)){
				if (!early){
					std::swap(history_trade_data[i], history_trade_data[j]);
				}
			}else{
				json ji;
				json jj;
				s4_history_trade_t::to_json(ji, history_trade_data[i]);
				s4_history_trade_t::to_json(jj, history_trade_data[j]);
				LCL_WARN("cannot compare :{:}\nvs\n{:}", ji.dump(4), jj.dump(4));
			}
		}
	}
}



} // namespace S4
