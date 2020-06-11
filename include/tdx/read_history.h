#pragma once
#include "market/s4codeApp.h"

#include "jsonTypes/tdx_xyzq_history_deal_t.h"
#include "jsonTypes/tdx_xyzq_history_deal_t_dbTbl.h"

#include "jsonTypes/tdx_xyzq_history_order_t.h"
#include "jsonTypes/tdx_xyzq_history_order_t_dbTbl.h"

#include "db_sqlite/db.h"

#include "jsonTypes/s4_history_t.h"
namespace S4{
namespace TDX{

bool read_history_deal(const std::string& file_name, std::vector<tdx_xyzq_history_deal_t>& deals);
bool history_deal_to_DB(S4::sqlite::DB_t& history_db, const std::string& file_name, const std::string& table_name);

bool read_history_order(const std::string& file_name, std::vector<tdx_xyzq_history_order_t>& orders);
bool history_order_to_DB(S4::sqlite::DB_t& history_db, const std::string& file_name, const std::string& table_name);

//if table_list is empty, it will read all tables from db.
bool read_histroy_DB(const std::filesystem::path& db_file_path, std::vector<s4_history_t>& history_data, 
	const std::set<std::string>& table_list = {}, const std::vector<mktCodeI_t>& stk_list = {});

} // namespace TDX
} // namespace S4

