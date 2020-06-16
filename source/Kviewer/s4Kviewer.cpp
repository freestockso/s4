#pragma warning(push)
# pragma warning(disable: 4189) 

#include "Kviewer/s4Kviewer.h"
#include "common/s4logger.h"

#include <QSplitter>
#include <QScrollArea>

#ifdef max
#undef max
#endif

using namespace std;

namespace S4 {
namespace QT {

s4qt_viewer::s4qt_viewer(QWidget *parent) :
    QMainWindow(parent)/*,
    ui(new Ui::s3QT)*/
{   
    //ui->setupUi(this);


	//pCLI = new cliparser(this);
	//pCLI->setFocusPolicy(Qt::StrongFocus);

	//pmyKwin = new s3qt::myKwin(this);

	//connect(pmyKwin, SIGNAL(signal_getStkInfo(const std::string & , const struct s3qt::stkInfoReq_t& , s3qt::stkInfo_t*& )),
	//	&dataIF, SLOT(getInfo(const std::string & , const struct s3qt::stkInfoReq_t& , s3qt::stkInfo_t*& )));

	//connect(pmyKwin, SIGNAL(signal_loadOrdres(const std::string &, const std::string & , const std::string & , s3qt::stkInfo_t*& )),
	//	&dataIF, SLOT(loadOrdres(const std::string &, const std::string &, const std::string &, s3qt::stkInfo_t*&)));

	//connect(pCLI, SIGNAL(getData(std::string& , std::string& , std::string& )), 
	//	pmyKwin, SLOT(getData(std::string& , std::string& , std::string& )));

    //pmyKwin->getData(std::string("sz000997"), std::string(""), std::string(""));

	
    QSplitter *splitterMain = new QSplitter(Qt::Vertical, 0); //新建主分割窗口，水平分割
    QSplitter *splitterLeft = new QSplitter(Qt::Vertical, splitterMain);
	QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitterMain);

//	QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitterMain);
	QSplitter *splitterBottum = new QSplitter(Qt::Vertical, splitterMain);

    splitterMain->setHandleWidth(1);

    //splitterLeft->addWidget(pkBar);
    //splitterRight->addWidget(pmyKwin);
	//splitterBottum->addWidget(pCLI);

	QList<int> list;
	list << 100;
	list << 50;
	list << 20;
	list << 20;
	list << 20;
	splitterMain->setSizes(list);

    //创建滚动区域。
    QScrollArea *scrollArea = new QScrollArea;
    //把label控件放进滚动区域中.注意只能设置一个控件,一个一个控件往里面加,只会显示最后一个加入的控件.
    scrollArea->setWidget(splitterMain);
    //设置对齐格式.
    scrollArea->setAlignment(Qt::AlignCenter);


    //设置水平和垂直滚动条的策略.默认是如下策略.
    //scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //设置是否自动调整部件的大小.默认是false.
    scrollArea->setWidgetResizable(true);

	scrollArea->resize(1200, 800);

	button = make_shared<QPushButton>(scrollArea);
	button->setGeometry(QRect(50, 50, 25, 25));	// x, y, w, h
	button->setText("+");

    //QHBoxLayout *layout = new QHBoxLayout(this);
    //layout->addWidget(scrollArea);

    //this->resize(600,600);

    // this->setCentralWidget(splitterMain);
	this->setCentralWidget(scrollArea);

	resize(1200, 800);

	connect(this, SIGNAL(signal_getInfo(const std::string &, const struct S4::stkInfoReq_t&, class S4::stkInfo_t*&)),
		&_data_if, SLOT(getInfo(const std::string &, const struct S4::stkInfoReq_t&, class S4::stkInfo_t*&)));
	connect(this, SIGNAL(signal_loadOrdres(const std::string &, const std::string &, const std::string &, std::vector<S4::s4_history_t>&)),
		&_data_if, SLOT(loadOrdres(const std::string &, const std::string &, const std::string &, std::vector<S4::s4_history_t>&)));


#ifndef NDEBUG
	S4::stkInfoReq_t _infoReq;
	_infoReq.endDate = _DOOMSDAY_;
	_infoReq.nbDay_preEndDate = std::numeric_limits<int>::max();

	S4::stkInfo_t* info;

	emit signal_getInfo("sz000997", _infoReq, info);
	if (info == nullptr) {
		FATAL("getInfo fail");
	}
	emit signal_getInfo("sh688004", _infoReq, info);
	if (info == nullptr) {
		FATAL("getInfo fail");
	}
	emit signal_getInfo("sh688001", _infoReq, info);
	if (info != nullptr) {
		FATAL("getInfo NG");
	}

	//////////////
	emit signal_getInfo("sz002810", _infoReq, info);
	if (info == nullptr) {
		FATAL("getInfo NG");
	}
	std::vector<S4::s4_history_t> history_data;
	emit signal_loadOrdres("sz002810", "tdx_xyzq_history", "to20200531", history_data);
	if (!history_data.size()) {
		FATAL("loadOrdres fail");
	}
#endif // !NDEBUG

}


void s4qt_viewer::load(const std::string& stkName, const std::string& stgName, const std::string& orderTblName)
{

	S4::stkInfoReq_t infoReq;
	S4::stkInfo_t* pInfo;
	std::vector<S4::s4_history_t> history_data;

	infoReq.endDate = _DOOMSDAY_;
	infoReq.nbDay_preEndDate = std::numeric_limits<int>::max();

	//infoReq.cyc_scope_list = vector<int>{ __CYC_S1__, __CYC_M1__, __CYC_L1__, __CYC_X1__ };
	// infoReq.ma_scope_list = vector<int>{ 15,60 };
	infoReq.ma_scope_list = vector<int>{5, 20, 60, 120};


	emit signal_getInfo(stkName, infoReq, pInfo);

	if (orderTblName.size() != 0) {
		emit signal_loadOrdres(stkName, stgName, orderTblName, history_data);
	}

	_data_panel.infoReq = infoReq;
	_data_panel.history = history_data;
	_data_panel.info = *pInfo;
	showData();
}

void s4qt_viewer::showData()
{

}



s4qt_viewer::~s4qt_viewer()
{
}

}
}

#pragma warning(pop)