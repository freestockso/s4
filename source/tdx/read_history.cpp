#include <fstream>
#include "string/s4string.h"
#include "tdx/read_history.h"
#include "common/s4logger.h"
#include "jsonTypes/tdx_xyzq_history_deal_t.h"
#include "jsonTypes/tdx_xyzq_history_order_t.h"
#include "types/s4convertors.h"
#include "time/s4time.h"

CREATE_LOCAL_LOGGER(tdx_read_history)

using namespace std;

#define ORDER_INDEX_PLEACEHOLDER (10000ll)

namespace S4{
namespace TDX{

static vector<string> deal_titles = {
/*
成交日期	
成交时间	
证券代码	
证券名称	
买卖标志	
成交价格	
成交数量	
成交编号	
委托编号	
股东代码	
成交金额	
佣金	
印花税	
过户费	
其他费	
备注
*/
};

//可能跳过的成交记录：打新配号、股息
bool read_history_deal(const std::string& file_name, std::vector<tdx_xyzq_history_deal_t>& deals)
{
	deals.clear();

    std::ifstream	reader(file_name);

    if(!reader.is_open()){
        LCL_ERR("can't open deal file = {:}", file_name);
        return false;
    }

    string str;
    getline(reader,str); // title
    vector<string> title = string_strip(str, "\t");
    while( getline(reader,str))
    {
        vector<string> lineV = string_strip(str, "\t");
		if (lineV.size() < title.size())
			continue;
		struct tdx_xyzq_history_deal_t deal;

		try {
			int deal_HMS = 0;
			for (size_t i = 0; i < lineV.size(); ++i) {
				const string v = lineV[i];
				const string t = title[i];
				if (t == "成交日期") {       deal.date = (time_date_t)IntConvertor::convert(v);
				}
				else if (t == "成交时间") {
					vector<string> time = string_strip(v, ":");
					if (time.size() != 3) {
						LCL_ERR("成交时间 decode size={:} != 3", time.size());
					}
					int hour = (int)IntConvertor::convert(time[0]);
					int minu = (int)IntConvertor::convert(time[1]);
					int sec = (int)IntConvertor::convert(time[2]);
					deal_HMS = hour * 10000 + minu * 100 + sec;
				}else if (t == "证券代码") { deal.stock_code = v;	//pureCodeStr
				}else if (t == "证券名称") { deal.stock_name = v;
				}else if (t == "买卖标志") { deal.opt_type = v;
				}else if (t == "成交价格") { deal.deal_price = (fprice_t)DoubleConvertor::convert(v);
				}else if (t == "成交数量") { deal.deal_vol = (vol_share_t)abs(IntConvertor::convert(v));
				}else if (t == "委托编号") { deal.id = (int)IntConvertor::convert(v);
				}else if (t == "成交金额") { deal.deal_amount = (amount_t)DoubleConvertor::convert(v);
				}else if (t == "佣金") {    deal.commission = (amount_t)DoubleConvertor::convert(v);
				}else if (t == "印花税") {	deal.stamp_duty = (amount_t)DoubleConvertor::convert(v);
				}else if (t == "过户费") {	deal.transfer_fee = (amount_t)DoubleConvertor::convert(v);
				}else if (t == "其他费") {	deal.other_fees = (amount_t)DoubleConvertor::convert(v);
				}else if (t == "备注") {    deal.remarks = v;
				}
			}
			mktCode_t mktCode = pureCodeStr_to_mktCode(deal.stock_code);
			if (deal_HMS == 0 || !isDealTime_stock(deal_HMS, mktCode)) {
				LCL_WARN("drop deal line for not-market-time:\n{:}", str);
				continue;
			}
			if (deal.deal_price == (fprice_t)0){
				LCL_WARN("drop deal line for price 0:\n{:}", str);
				continue;
			}
			deal.time_utcSec = date_to_utc(deal.date, deal_HMS);
			deal.time_format = utc_to_str(deal.time_utcSec);
			deal.id = deal.date * ORDER_INDEX_PLEACEHOLDER + deal.id;
			deals.emplace_back(move(deal));
		}
		catch (std::exception& e) {
			LCL_ERR("dec deal fail for {:}:\n{:}", e.what(), str);
			continue;
		}
    }

    return true;
}

bool read_history_order(const std::string& file_name, std::vector<tdx_xyzq_history_order_t>& orders)
{
	orders.clear();

    std::ifstream	reader(file_name);

    if(!reader.is_open()){
        LCL_ERR("can't open order file = {:}", file_name);
        return false;
    }

    string str;
    getline(reader,str); // title
    vector<string> title = string_strip(str, "\t");
    while( getline(reader,str))
    {
        vector<string> lineV = string_strip(str, "\t");
		if (lineV.size() < title.size())
			continue;
		struct tdx_xyzq_history_order_t order;

		try {
			int order_HMS = 0;
			for (size_t i = 0; i < lineV.size(); ++i) {
				const string v = lineV[i];
				const string t = title[i];
				if (t == "委托日期") {       order.date = (time_date_t)IntConvertor::convert(v);
				}
				else if (t == "委托时间") {
					vector<string> time = string_strip(v, ":");
					if (time.size() != 3) {
						LCL_ERR("委托时间 decode size={:} != 3", time.size());
					}
					int hour = (int)IntConvertor::convert(time[0]);
					int minu = (int)IntConvertor::convert(time[1]);
					int sec = (int)IntConvertor::convert(time[2]);
					order_HMS = hour * 10000 + minu * 100 + sec;
				}else if (t == "证券代码") { order.stock_code = v;	//pureCodeStr
				}else if (t == "证券名称") { order.stock_name = v;
				}else if (t == "买卖标志") { order.opt_type = v;
				}else if (t == "委托类别") { order.delegate_type = v;
				}else if (t == "状态说明") { order.status = v;
				}else if (t == "委托价格") { order.order_price = (fprice_t)DoubleConvertor::convert(v);
				}else if (t == "委托数量") { order.order_vol = (vol_share_t)abs(IntConvertor::convert(v));
				}else if (t == "成交价格") { order.deal_price = (fprice_t)DoubleConvertor::convert(v);
				}else if (t == "成交数量") { order.deal_vol = (vol_share_t)abs(IntConvertor::convert(v));
				}else if (t == "委托编号") { order.id = (int)IntConvertor::convert(v);
				}else if (t == "报价方式") { order.quote_mode = v;
				}
			}
			if (order.order_price == (fprice_t)0){
				LCL_WARN("drop order line for price 0:\n{:}", str);
				continue;
			}
			if (order.quote_mode != "买卖") {
				LCL_WARN("drop order line for quote_mode = {:}:\n{:}", order.quote_mode, str);
				continue;
			}
			order.time_utcSec = date_to_utc(order.date, order_HMS);
			order.time_format = utc_to_str(order.time_utcSec);
			order.id = order.date * ORDER_INDEX_PLEACEHOLDER + order.id;
			orders.emplace_back(move(order));
		}
		catch (std::exception& e) {
			LCL_ERR("dec deal fail for {:}:\n{:}", e.what(), str);
			continue;
		}
    }

    return true;
}

bool history_deal_to_DB(S4::sqlite::DB_t& history_db, const std::string& file_name, const std::string& table_name)
{
	std::vector<S4::tdx_xyzq_history_deal_t> deals;
	bool ret;
	ret = S4::TDX::read_history_deal(file_name, deals);
	if (!ret) {
		return false;
	}

	S4::sqlite::tdx_xyzq_history_deal_t_dbTbl deal_tbl;
	history_db.to_table<S4::sqlite::tdx_xyzq_history_deal_t_dbTbl::data_t>(&deal_tbl, table_name, deals);

	std::vector<S4::tdx_xyzq_history_deal_t> deals_rd;
	history_db.read_table< S4::sqlite::tdx_xyzq_history_deal_t_dbTbl::data_t>(&deal_tbl, table_name, deals_rd);

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
	return true;
}

bool history_order_to_DB(S4::sqlite::DB_t& history_db, const std::string& file_name, const std::string& table_name)
{
	std::vector<S4::tdx_xyzq_history_order_t> orders;
	bool ret;
	ret = S4::TDX::read_history_order(file_name, orders);
	if (!ret) {
		return false;
	}

	S4::sqlite::tdx_xyzq_history_order_t_dbTbl order_tbl;
	history_db.to_table<S4::sqlite::tdx_xyzq_history_order_t_dbTbl::data_t>(&order_tbl, table_name, orders);

	std::vector<S4::tdx_xyzq_history_order_t> orders_rd;
	history_db.read_table< S4::sqlite::tdx_xyzq_history_order_t_dbTbl::data_t>(&order_tbl, table_name, orders_rd);

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

	return true;

}


} // namespace TDX
} // namespace S4

