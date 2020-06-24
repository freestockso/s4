#include "qt_Kviewer/s4Kinstrument_indicator_tab.h"

namespace S4{
namespace QT{
    
Kinstrument_indicator_tab::Kinstrument_indicator_tab(QWidget *parent):
    QTabWidget(parent)
{
    setMouseTracking(true);
}


void Kinstrument_indicator_tab::setInstrument(std::shared_ptr<data_panel_t> data_panel){
    _data_panel = data_panel;
}


void Kinstrument_indicator_tab::paint(Kinstrument_indicator_scene::ind_type type, timeMode_t timeMode)
{
    for(auto& ctx : _tab_ctx){
        if ( ctx.second.timeMode == timeMode && ctx.second.type == type){
            setCurrentIndex(ctx.first);
            return;
        }
    }

    //need new tab
    Kinstrument_indicator_scene::indCtx_t indCtx;
    indCtx.type = type;
    indCtx.timeMode = timeMode;

    Kinstrument_indicator_scene* scene = new Kinstrument_indicator_scene(this);
    scene->paint(indCtx, _data_panel);

    Kinstrument_indicator_view* view = new Kinstrument_indicator_view(scene, this);
    view->paint();
    int i = addTab(view, indCtx.toString());
    setCurrentIndex(i);
    _tab_ctx[i] = indCtx;

}

} // namespace QT
} // namespace S4
