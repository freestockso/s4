#pragma once

#include "jsonTypes/tdx_xyzq_history_deal_t.h"
#include "jsonTypes/tdx_xyzq_history_deal_t_dbTbl.h"

#include "jsonTypes/tdx_xyzq_history_order_t.h"
#include "jsonTypes/tdx_xyzq_history_order_t_dbTbl.h"

#include "db_sqlite/db.h"


namespace S4{
namespace TDX{

bool read_history_deal(const std::string& file_name, std::vector<tdx_xyzq_history_deal_t>& deals);
bool history_deal_to_DB(S4::sqlite::DB_t& history_db, const std::string& file_name, const std::string& table_name);

bool read_history_order(const std::string& file_name, std::vector<tdx_xyzq_history_order_t>& orders);
bool history_order_to_DB(S4::sqlite::DB_t& history_db, const std::string& file_name, const std::string& table_name);


} // namespace TDX
} // namespace S4

