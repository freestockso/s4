


#include "common/s4calendar.h"
#include "tdx/tdx_local.h"

using namespace std;
using namespace S4::TDX;

namespace S4{

tdxCalendar_t::tdxCalendar_t(const std::string& tdxRootPath) :
	calendar_t(9 * 3600 + 10 * 60, 15 * 3600 + 5 * 60)// YYYYMMDD 09:10:00 ~ 15:05:00
{
	tdxLocal_t tdxIF(tdxRootPath);
	vector<dayK_t> dayK;
	tdxIF.readDayK("sh000001", dayK);

	for (vector<dayK_t>::const_iterator i = dayK.begin(); i != dayK.end(); ++i) {
		//if (i->date == 20190102)break;
		push_back(i->date);
	}
	if (size()) {
		INFO("TDX-calendar has been built [0]={0:d},  [{1:d}]={2:d} !", newest(), size(), oldest());
	}
	else {
		WARN("TDX-calendar load nothing, tdx-root = {:} may be mistake!", tdxRootPath);
	}
}

}