#pragma once

#include <QMainWindow>
#include <QModelIndex>
#include <QTableView>
#include <QStandardItemModel>

#include "dbconnectdialog.h"
#include "DBHandler.h"
#include "tablelist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SqlViewer; }
QT_END_NAMESPACE

namespace S4{

class SqlViewer : public QMainWindow
{
    Q_OBJECT
public:
    SqlViewer(QWidget *parent = nullptr);
    ~SqlViewer();

public slots:
    void connectDbDialog();

    void onConnectionDialogAccepted();
    void onConnectionDialogRejected();

//    void updateTableList();
    void openTableTab(const QModelIndex &index);


private:
    Ui::SqlViewer *ui;
    DbConnectDialog *connectionDialog = nullptr;
    QMap<QString, QTableView *> tableMap;
    DBHandler *dbHandler = nullptr;

    QStandardItemModel* _dbTree_model;

    bool tabAlreadyExists(const QString &tableName) const;
    void tabCloseRequestHandler(int index);

private:
    void onOpen();
    void onLoadConf(void);
    void onOpenDBs(void);
    void onOpenDB_orders(void);
};

}