#include "qt_Kviewer/s4Kinstrument_Kline_tab.h"

namespace S4{
namespace QT{
    
Kinstrument_Kline_tab::Kinstrument_Kline_tab(QWidget *parent):
    QTabWidget(parent)
{
    setMouseTracking(true);
}


void Kinstrument_Kline_tab::setInstrument(std::shared_ptr<data_panel_t> data_panel){
    _data_panel = data_panel;
    //day
    if (data_panel->info.pDayKQ && data_panel->info.pDayKQ->size()){
        Kinstrument_Kline_scene* _K_scene = new Kinstrument_Kline_scene(this);
        _K_scene->setInfoKQ(data_panel->info.pDayKQ);
        _K_scene->setMAmap(data_panel->info.pMAlib);
        _K_scene->paint();
        Kinstrument_Kline_view* _K_view = new Kinstrument_Kline_view(_K_scene, this);
        _K_view->setCtx(data_panel->info.pDayKQ);
        _K_view->paint();
        int i = addTab(_K_view, "day");
        setCurrentIndex(i);
        _timeMode = tDAY;
    }
}



} // namespace QT
} // namespace S4
