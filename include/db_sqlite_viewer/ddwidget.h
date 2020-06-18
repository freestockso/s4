#ifndef DDWIDGET_H
#define DDWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QLayout>

#include "qt/Utils.h"

namespace Ui {
class DDwidget;
}

class DDwidget : public QWidget
{
    Q_OBJECT

public:
    explicit DDwidget(QWidget *parent = nullptr);
    ~DDwidget();

signals:
    void filePathRecived(const QString& path);

public slots:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::DDwidget *ui;
    QString dbPath;
};

#endif // DDWIDGET_H
