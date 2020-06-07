#include "tdx/read_history.h"
#include "common/s4conf.h"
#include "jsonTypes/tdx_xyzq_history_deal_t_dbTbl.h"
#include "jsonTypes/tdx_xyzq_history_order_t_dbTbl.h"
#include "db_sqlite/db.h"

CREATE_LOCAL_LOGGER("test_tdx_history")


int main(int argc, char** argv)
{
	S4::glb_conf::pInstance()->load("../json_template/glb_conf_t.json");

	S4::s4logger::pInstance()->init((void*)S4::glb_conf::pInstance()->pLogger());
	S4::glb_conf_t::tdx_t tdx = S4::glb_conf::pInstance()->tdx();
	std::vector<S4::tdx_xyzq_history_deal_t> deals;
	std::vector<S4::tdx_xyzq_history_order_t> orders;
	bool ret;
	ret = S4::TDX::read_history_deal("../doc/20200531历史成交查询.xls", deals);
	ret = S4::TDX::read_history_order("../doc/20200531历史委托查询.xls", orders);

	S4::glb_conf_t::db_t db = S4::glb_conf::pInstance()->db();
	std::filesystem::path db_root = db.root;
	std::filesystem::path db_history = db_root / db.history_order;

	S4::sqlite::DB_t history_db(db_history.string());

	//deal <-> DB
	S4::sqlite::tdx_xyzq_history_deal_t_dbTbl deal_tbl;
	history_db.to_table<S4::sqlite::tdx_xyzq_history_deal_t_dbTbl::data_t>(&deal_tbl, "deal_to20200531", deals);

	std::vector<S4::tdx_xyzq_history_deal_t> deals_rd;
	history_db.read_table< S4::sqlite::tdx_xyzq_history_deal_t_dbTbl::data_t>(&deal_tbl, "deal_to20200531", deals_rd);

	if (deals.size() != deals_rd.size()) {
		LCL_ERR("deal DB write - read unequal! w.size={:}, r.size={:}", deals.size(), deals_rd.size());
	}
	for (size_t i = 0; i < min(deals.size(), deals_rd.size()); ++i) {
		if (deals[i] != deals_rd[i]) {
			LCL_ERR("deal DB write - read unequal! w[{:}] != r[{:}]", i, i);		//as example, 8 and 9 are unequal for reordered by DB
		}
		else {
			LCL_INFO("deal DB write - read OK! w[{:}] == r[{:}]", i, i);
		}
	}

	//order <-> DB
	S4::sqlite::tdx_xyzq_history_order_t_dbTbl order_tbl;
	history_db.to_table<S4::sqlite::tdx_xyzq_history_order_t_dbTbl::data_t>(&order_tbl, "order_to20200531", orders);

	std::vector<S4::tdx_xyzq_history_order_t> orders_rd;
	history_db.read_table< S4::sqlite::tdx_xyzq_history_order_t_dbTbl::data_t>(&order_tbl, "order_to20200531", orders_rd);

	if (orders.size() != orders_rd.size()) {
		LCL_ERR("order DB write - read unequal! w.size={:}, r.size={:}", orders.size(), orders_rd.size());
	}
	for (size_t i = 0; i < min(orders.size(), orders_rd.size()); ++i) {
		if (orders[i] != orders_rd[i]) {
			LCL_ERR("order DB write - read unequal! w[{:}] != r[{:}]", i, i);
		}
		else {
			LCL_INFO("order DB write - read OK! w[{:}] == r[{:}]", i, i);
		}
	}
}
