#ifndef TABLELIST_H
#define TABLELIST_H
#include <QAbstractItemModel>
#include <QStringList>
#include <QtDebug>
class TableList : public QAbstractListModel
{
    Q_OBJECT
private:
    QStringList stringList;
public:
    TableList(const QStringList &strList, QObject *parent = 0);

   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
   int rowCount(const QModelIndex &parent = QModelIndex()) const ;
   int columnCount(const QModelIndex &parent = QModelIndex()) const;
};

#endif // TABLELIST_H
