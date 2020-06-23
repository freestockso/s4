#pragma once

#include "qt_Kviewer/s4Kinstrument.h"
#include "qt_common/s4qt_data_if.h"

#include <QTabWidget>
#include <QKeyEvent>

namespace S4{
namespace QT{
    
class Kviewer_instrumentTab: public QTabWidget
{
    Q_OBJECT
public:
    explicit Kviewer_instrumentTab(QWidget *parent = nullptr):
        QTabWidget(parent)
    {
        setMouseTracking(true);
    }

    void addInstrument(const data_panel_t& data_panel){
        //day
        Kinstrument* K = new Kinstrument(this);
        K->setInstrument(data_panel);
        int i = addTab(K, data_panel.info.name().c_str());
        setCurrentIndex(i);
    }

};


} // namespace QT
} // namespace S4
