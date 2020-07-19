#include "tdx/tdx_local.h"
#include "common/s4conf.h"
#include "common/s4string.h"
#include "data/s4thread_data_if.h"
#include <filesystem>

CREATE_LOCAL_LOGGER("make_ml")

using namespace S4;
using namespace std;
using namespace std::filesystem;

#define _FILE_FIELD_SEP_ ","
#define _FILE_LINE_END_ "\n"

int main(int argc, char** argv)
{
	glb_conf::pInstance()->load("../worksapce/glb_conf_ctx_t_y.json");
	s4logger::pInstance()->init((void*)glb_conf::pInstance()->pLogger());
	std::shared_ptr<tdxCalendar_t> pCalendar = glb_conf::pInstance()->calendar();

	thread_data_if_t _th_data_if;
	string stkName = "sz399006";
	stkInfoReq_t infoReq;
	infoReq.endDate = _DOOMSDAY_;
	infoReq.nbDay_preEndDate = _DOOMSDAY_;
	infoReq.needMinu = false;
	infoReq.needSnap = false;
	infoReq.ma_scope_list = { 10, 20, 60, 120 };

	stkInfo_t* info;

	if (_th_data_if.getNowLib() == nullptr || _th_data_if.getNowLib()->count(stkName) == 0) {
		_th_data_if.preload({ stkName }, infoReq);
		while (!_th_data_if.preloadReady());
		_th_data_if.usePreload(true);
	}

	if (_th_data_if.getNowLib()->count(stkName) == 0) {
		LCL_WARN("no such instrument: {:}", stkName);
		return -1;
	}

	info = _th_data_if.getNowLib()->get(stkName);
	LCL_INFO("getInfo {:} successd: {:} ~ {:} = {:}", stkName, info->pDayKQ->front()->_date, info->pDayKQ->back()->_date, info->pDayKQ->size());
	info->newAtBack();
	info->setBase(date_to_utc(pCalendar->newest()), 0);

	if (info->getDay(0)) {
		LCL_INFO("base at {:}", info->getDay(0)->_date);
	}
	else {
		LCL_FATAL("base error!");
	}

	int material_scope = 120;
	int predicate_scope = 20;

	int i = (int)predicate_scope;
	std::string f;
	std::string title;
	bool title_done = false;
	while (info->getDay(i) && info->getDay(i + (int)material_scope))
	{
		string l;

		if (!title_done) title += "date" _FILE_FIELD_SEP_;
		l += IntConvertor::convert(info->getDay(i)->_date) + _FILE_FIELD_SEP_;

		for (int j = 0; j < material_scope; ++j) {
			if (!title_done) title += "d" + IntConvertor::convert(j) + _FILE_FIELD_SEP_;
			l += IntConvertor::convert(info->getDay(i + j)->close) + _FILE_FIELD_SEP_;
		}

		if (!title_done) title += "rise" _FILE_FIELD_SEP_;
		double rise = CALC_R_PERCENT(info->getDay(i - predicate_scope)->close, info->getDay(i)->close);
		l += DoubleConvertor::convert(rise) + _FILE_FIELD_SEP_;

		if (!title_done) title += "rise_class" _FILE_FIELD_SEP_;
		int rc = (int)(rise / 10.0);
		l += "c" + IntConvertor::convert(rc)+ _FILE_FIELD_SEP_;

		if (!title_done) f += move(title) + _FILE_LINE_END_;
		title_done = true;
		f += move(l) + _FILE_LINE_END_;
		i++;
	}

	write_string_to_file("../worksapce/" + stkName + "_ml.csv", f, true);


	return 0;
}