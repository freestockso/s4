#include "tdx/read_history.h"
#include "common/s4conf.h"

CREATE_LOCAL_LOGGER("test_tdx_history")


int main(int argc, char** argv)
{
	S4::glb_conf::pInstance()->load("../json_template/glb_conf_t.json");
	S4::s4logger::pInstance()->init((void*)S4::glb_conf::pInstance()->pLogger());

	S4::glb_conf_t::db_t db = S4::glb_conf::pInstance()->db();
	std::filesystem::path db_root = db.root;
	std::filesystem::path db_history = db_root / db.history_order;

	S4::sqlite::DB_t history_db(db_history.string());
	bool ret;

	//deal <-> DB
	ret = S4::TDX::history_deal_to_DB(history_db, "../doc/20200531历史成交查询.xls", "deal_to20200531");
	if (!ret) {
		LCL_ERR("history_deal_to_DB fail!");
	}

	//order <-> DB
	ret = S4::TDX::history_order_to_DB(history_db, "../doc/20200531历史委托查询.xls", "order_to20200531");
	if (!ret) {
		LCL_ERR("history_order_to_DB fail!");
	}
}
