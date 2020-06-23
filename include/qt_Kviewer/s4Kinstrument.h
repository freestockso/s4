#pragma once

#include "qt_common/s4qt_data_if.h"
#include "qt_Kviewer/s4Kinstrument_Kline_tab.h"

#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QTabWidget>
#include <QDebug>
#include <QMouseEvent>


namespace S4{
namespace QT{
    

class Kinstrument: public QWidget
{
    Q_OBJECT
public:
    explicit Kinstrument(QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent* )
    {
        //qDebug() << "Kinstrument " << hasMouseTracking() << " " << event->pos().x() << ", " << event->pos().y();
    }

    void setInstrument(const data_panel_t& data_panel){
        _data_panel = data_panel;

        _K_tab->setInstrument(data_panel);
    }
private:
    // K line tab
    Kinstrument_Kline_tab* _K_tab;
    // vol/indicator tab
    QTabWidget* _indicator_tab;
    // cyc/... tab
    QTabWidget* _cyc_tab;
    // basic tab
    QTabWidget* _basic_tab;

private:
    data_panel_t _data_panel;

};


} // namespace QT
} // namespace S4
