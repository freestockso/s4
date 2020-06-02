#include <fstream>
#include "string/s4string.h"
#include "tdx/read_history.h"
#include "common/s4logger.h"

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
        


    }

    return true;
}

bool read_history_order(const std::string& file_name, std::vector<tdx_xyzq_history_order_t>& orders)
{
    return true;
}

} // namespace TDX
} // namespace S4

