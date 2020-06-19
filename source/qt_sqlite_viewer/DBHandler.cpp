#include "qt_sqlite_viewer/DBHandler.h"

DBHandler::DBHandler(const QString &dbPath) {

    //    QSqlDatabase::removeDatabase(dbPath);
    qDebug() << dbPath;
    dbName = dbPath;
    if(!QSqlDatabase::contains(dbName)){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE",dbName);
        db.setDatabaseName(dbPath);

        if (!db.open()){
            qDebug() << "Unable to open database";
        }
        else{
            qDebug() << "Successfully opened database";
        }
    }
    else{
        qDebug() << "Database already exists";
    }

}

DBHandler::~DBHandler()
{
    QSqlDatabase::database(dbName).close();
}

QStringList DBHandler::getTables() const
{
    return QSqlDatabase::database(dbName).tables();
}

QSqlQueryModel* DBHandler::getTableData(const QString &tableName) const
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlDatabase db = QSqlDatabase::database(dbName);
    QSqlQuery q(db);
    db.open();
    
    q.clear();
    q.exec("select * from "+tableName);
    //    q.bindValue(":table",tableName);
    //    q.exec();
    if (q.lastError().isValid()){
        qDebug() << q.lastError();
    }
    model->setQuery(q);

    return model;
}

