#ifndef SQLVIEWER_H
#define SQLVIEWER_H

#include <QMainWindow>
#include <QModelIndex>
#include <QTableView>

#include "dbconnectdialog.h"
#include "DBHandler.h"
#include "tablelist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SqlViewer; }
QT_END_NAMESPACE

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

    bool tabAlreadyExists(const QString &tableName) const;
    void tabCloseRequestHandler(int index);
};
#endif // SQLVIEWER_H
