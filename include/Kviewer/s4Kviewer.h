#pragma once

#include <QMainWindow>
#include <QPushButton>
//#include "qt\console\cliparser.h"
//#include "qt\s4qt_view_k.h"
#include "Kviewer\s4qt_data_if.h"

//namespace Ui {
//class s4qt_viewer;
//}

namespace S4{
namespace QT{

struct data_panel_t{
	S4::stkInfoReq_t infoReq;
	S4::stkInfo_t info;
	std::vector<S4::s4_history_t> history;
};



class s4qt_viewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit s4qt_viewer(QWidget *parent = 0);
    ~s4qt_viewer();

public slots:
	void load(const std::string& mktCode, const std::string& stgName, const std::string& orderTblName);

signals:
	void signal_getInfo(const std::string & stkName, const struct S4::stkInfoReq_t& infoReq, class S4::stkInfo_t*& info);
	void signal_loadOrdres(const std::string & stkName, const std::string & stgName, const std::string & orderTblName, std::vector<S4::s4_history_t>& history_data);
private:
    //Ui::s4qt_viewer *ui;

	//s3qt::myKwin* pmyKwin;

	//cliparser* pCLI;
	data_panel_t _data_panel;
	S4::QT::s4qt_data_if _data_if;

	std::shared_ptr<QPushButton> button;

private:
	void showData();

};

}
}