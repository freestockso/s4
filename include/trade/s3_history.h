#pragma once

#include "jsonTypes/s3_order_t.h"
#include "jsonTypes/s3_order_t_dbTbl.h"
#include "db_sqlite/db.h"
#include "jsonTypes/s4_history_trade_t.h"

namespace S4{
namespace S3c{  //compatible with s3

bool read_s3history(sqlite::DB_t& history_db, const std::string& table_name, const std::string& mktCodeStr, std::vector<s3_order_t>& s3data);

bool trans_s3history(const std::vector<s3_order_t>& s3data, std::vector<s4_history_trade_t>& s4data);

} // namespace S3c
} // namespace S4