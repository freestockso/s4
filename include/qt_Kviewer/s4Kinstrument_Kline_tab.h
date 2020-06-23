#pragma once

#include "qt_Kviewer/s4Kinstrument_Kline_view.h"
#include "qt_Kviewer/s4Kinstrument_Kline_scene.h"
#include "qt_common/s4qt_data_if.h"

#include <QTabWidget>
#include <QKeyEvent>

namespace S4{
namespace QT{
    
class Kinstrument_Kline_tab: public QTabWidget
{
    Q_OBJECT
public:
    explicit Kinstrument_Kline_tab(QWidget *parent = nullptr):
        QTabWidget(parent)
    {
        setMouseTracking(true);
    }

    void setInstrument(const data_panel_t& data_panel){
        //day
        if (data_panel.info.pDayKQ && data_panel.info.pDayKQ->size()){
            Kinstrument_Kline_scene* _K_scene = new Kinstrument_Kline_scene(this);
            _K_scene->setInfoKQ(data_panel.info.pDayKQ);
            _K_scene->setMAmap(data_panel.info.pMAlib);
            _K_scene->paint();
            Kinstrument_Kline_view* _K_view = new Kinstrument_Kline_view(_K_scene, this);
            _K_view->setCtx(data_panel.info.pDayKQ);
            _K_view->paint();
            int i = addTab(_K_view, "day");
            setCurrentIndex(i);
        }
    }

};


} // namespace QT
} // namespace S4
