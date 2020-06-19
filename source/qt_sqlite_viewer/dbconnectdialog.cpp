#include "qt_sqlite_viewer/dbconnectdialog.h"
#include "ui_dbconnectdialog.h"
#include "qt_sqlite_viewer/DBHandler.h"

DbConnectDialog::DbConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbConnectDialog)
{
    ui->setupUi(this);
    auto buttons = ui->buttonBox->buttons();
    auto *okButton = (QPushButton*)buttons[0];
    okButton->setDisabled(true);


    DDwidget *ddw = new DDwidget(this);
    connect(ddw,&DDwidget::filePathRecived,this, &DbConnectDialog::onOpenFileDialog);

    ui->verticalLayout->insertWidget(0,ddw,2);
    ddw->show();
}

DbConnectDialog::~DbConnectDialog()
{
    delete ui;
}

DBHandler *DbConnectDialog::getDBHandler() const
{
    return connection;
}


void DbConnectDialog::onOpenFileDialog(const QString &path)
{
     if(!Utils::fileCanBeOpened(path)){
         return;
     }

    connection = new DBHandler(path);

    auto buttons = ui->buttonBox->buttons();
    ((QPushButton*)buttons[0])->setDisabled(false);
}
