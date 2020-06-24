
#include "qt_Kviewer/s4Kinstrument_Kline_view.h"

namespace S4{
namespace QT{

Kinstrument_Kline_view::Kinstrument_Kline_view(Kinstrument_scene*scene, QWidget *parent):
    Kinstrument_view(scene, parent)
{

}

void Kinstrument_Kline_view::setCtx(const std::shared_ptr<infKQ_t>& pInfoKQ){
    if (!pInfoKQ || !pInfoKQ->size())
        return;

    if (!pInfoKQ->isNewAtBack())
        return;

    ctx_t ctx;
    ctx.set_val_h_max((*pInfoKQ)[0]->high);
    ctx.set_val_h_min((*pInfoKQ)[0]->low);
    ctx.set_val_w_max(0);
    ctx.set_val_w_min(0);

    int n = 0;
    for(const auto& d : *pInfoKQ)
    {
        if (d->high > ctx.val_h_max()){
            ctx.set_val_h_max(d->high);
        }
        if (d->low < ctx.val_h_min()){
            ctx.set_val_h_min(d->low);
        }
        ctx.set_val_w_max(n);
        n++;
    }

    Kinstrument_view::setCtx(ctx);
}

void Kinstrument_Kline_view::paint(void){
    paintGridLines();
    //paintGridLabels();
    //onViewChange();
    //paintCrosshair();
}


} // namespace QT
} // namespace S4


