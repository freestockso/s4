#include "qt_kviewer/s4console.h"
#include "ui_s4console.h"

s4console::s4console(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::s4console)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

s4console::~s4console()
{
    delete ui;
}
