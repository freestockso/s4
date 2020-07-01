#include "qt_console/cliparser.h"


cliparser::cliparser(QWidget *parent, const QString &welcomeText)
{
	setCmdColor(Qt::blue);
	setOutColor(Qt::black);
	// 将信号 mySignal() 与槽 mySlot() 相关联
	connect(this, SIGNAL(execCommand(const QString &)), SLOT(handlCommand(const QString &)));

}

void cliparser::handlCommand(const QString &command)
{
	QStringList split_cmd = command.split(" ", QString::SkipEmptyParts);//.toLower()

	if (split_cmd.size() && split_cmd[0] == "ld") {
		handlCommand_getData(split_cmd);
	}


	printCommandExecutionResults(command+" done!");
}


void cliparser::handlCommand_getData(QStringList& split_cmd)
{
	bool stk_found = false;
	bool stg_found = false;
	bool tbl_found = false;
	for (int i = 0; i < split_cmd.size(); ++i) {
		if (split_cmd[i].startsWith("stk=")) {
			stk_found = 1;
			_stkName = split_cmd[i].section('=', 1, 1);
		}
		else if (split_cmd[i].startsWith("stg=")) {
			stg_found = 1;
			_stgName = split_cmd[i].section('=', 1, 1);
		}
		else if (split_cmd[i].startsWith("tbl=")) {
			tbl_found = 1;
			_orderTblName = split_cmd[i].section('=', 1, 1);
		}
	}

	if (!stg_found)
		_stgName = "";
	if (!tbl_found)
		_orderTblName = "";

	QString log = "getData(";
	log += _stkName + ", " + _stgName + ", " + _orderTblName+")";

	if (stk_found || stg_found || tbl_found) {
		emit getData(_stkName.toStdString(), _stgName.toStdString(), _orderTblName.toStdString());
		log += "emited!";
	}
	else {
		log += "already emited, skip!";
	}
	printCommandExecutionResults(log);
}
