#ifndef S4CONSOLE_H
#define S4CONSOLE_H

#include <QDialog>
#include "qt_console/cliparser.h"

namespace Ui {
class s4console;
}

class s4console : public QDialog
{
    Q_OBJECT

public:
    explicit s4console(QWidget *parent = nullptr);
    ~s4console();


signals:
    void signal_load(const std::string&, const std::string&, const std::string&);

public slots:
    void emit_load(const std::string& mktCode, const std::string& stgName, const std::string& orderTblName) {
        emit signal_load(mktCode, stgName, orderTblName);
    }

private:
    Ui::s4console *ui;
	cliparser* _cli;
    QWidget *widget;
};

#endif // S4CONSOLE_H
