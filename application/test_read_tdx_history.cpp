#include "tdx/read_history.h"
#include "common/s4conf.h"

CREATE_LOCAL_LOGGER("test_tdx_history")


int main(int argc, char** argv)
{
	S4::gbl_conf_t::tdx_t tdx = S4::glb_conf::pInstance()->tdx();
	std::vector<S4::tdx_xyzq_history_deal_t> deals;
	std::vector<S4::tdx_xyzq_history_order_t> orders;
	bool ret;
	ret = S4::TDX::read_history_deal("../doc/20200531历史成交查询.xls", deals);
	ret = S4::TDX::read_history_order("../doc/20200531历史委托查询.xls", orders);

}
