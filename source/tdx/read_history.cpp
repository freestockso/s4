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

namespace S4{
namespace TDX{

static vector<string> deal_titles = {
//成交日期	成交时间	证券代码	证券名称	买卖标志	成交价格	成交数量	成交编号	委托编号	股东代码	成交金额	佣金	印花税	过户费	其他费	备注
};

bool read_history_deal(const std::string& file_name, std::vector<tdx_xyzq_history_deal_t>& deals)
{
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
				if (t == "成交日期") {
					deal.date = (int)IntConvertor::convert(v);
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
				}
			}
			mktCode_t mktCode = pureCodeStr_to_mktCode(deal.stock_code);
			if (deal_HMS == 0 || !isDealTime_stock(deal_HMS, mktCode)) {
				LCL_WARN("drop deal line for not-market-time:{:}", str);
			}
			deal.time_utcSec = date_to_utc(deal.date, deal_HMS);
			deal.time_format = utc_to_str(deal.time_utcSec);
		}
		catch (std::exception& e) {
			LCL_ERR("dec deal line = {:} fail: {:}", str, e.what());
			continue;
		}


    }

    return true;
}

bool read_history_order(const std::string& file_name, std::vector<tdx_xyzq_history_order_t>& orders)
{
    return true;
}

} // namespace TDX
} // namespace S4

