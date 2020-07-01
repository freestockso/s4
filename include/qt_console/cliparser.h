#pragma once

#include "qt_console/qconsole.h"


class cliparser : public QConsole {
	Q_OBJECT

public:
	cliparser(QWidget *parent = NULL, const QString &welcomeText = "");

signals:
	void getData(const std::string& stkName, const std::string& stgName, const std::string& orderTblName);
	
public slots:
	void handlCommand(const QString &command);

private:
	void handlCommand_getData(QStringList& split_cmd);
private:
	QString _stkName = "";
	QString _stgName = "";
	QString _orderTblName = "";
};