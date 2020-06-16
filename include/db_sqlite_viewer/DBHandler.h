#ifndef OPENFILE_H
#define OPENFILE_H

#include <QDebug>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>



class DBHandler
{
private:
    QString dbName;
public:
    explicit DBHandler(const QString &dbPath);
    DBHandler(const DBHandler &dbh) = delete;
    DBHandler &operator=(DBHandler &&dbh) = delete;
    ~DBHandler();

    QStringList getTables() const;
	QSqlQueryModel *getTableData(const QString &tableName) const;

    void onOpenFileActionTriggered();

};

#endif // OPENFILE_H
