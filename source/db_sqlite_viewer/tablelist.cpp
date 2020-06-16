#include "db_sqlite_viewer/tablelist.h"

TableList::TableList(const QStringList &strList,QObject *parent):QAbstractListModel(parent)
{
    stringList = QStringList(strList);
}

QVariant TableList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
        return QVariant();
    if(role == Qt::DisplayRole){
        return stringList.at(index.row());
    }

    return QVariant();
}

int TableList::rowCount(const QModelIndex &index) const
{
    return stringList.length();
}

int TableList::columnCount(const QModelIndex &parent) const
{
    return stringList.length();
}
