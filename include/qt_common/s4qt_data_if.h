#pragma once

#include "data/s4thread_data_if.h"
#include "tdx/read_history.h"

#include <QWidget>

namespace S4 {
namespace QT{

struct data_panel_t{
	S4::stkInfoReq_t infoReq;
	S4::stkInfo_t info;
	std::vector<S4::s4_history_trade_t> history;
};

class s4qt_data_if : public QWidget
{
	Q_OBJECT
public:

public slots:
	void getInfo(const std::string & stkName, const struct S4::stkInfoReq_t& infoReq, class S4::stkInfo_t*& info);
	void loadOrdres(const std::string & stkName, const std::string & stgName, const std::string & orderTblName, std::vector<S4::s4_history_trade_t>& history_trade_data);

private:
	thread_data_if_t _th_data_if;

};



}//namespace QT
}//namespace S4