#pragma once
#include "qt_Kviewer/s4Kinstrument_indicator_scene.h"
#include "common/s4time.h"
#include "qt_Kviewer/s4KlogicBar.h"
#include "qt_Kviewer/s4KlogicCurve.h"
#include "qt_Kviewer/s4KlogicRect.h"


namespace S4{
namespace QT{

#define BAR_Z (51)
#define MA_Z (52)
    
Kinstrument_indicator_scene::Kinstrument_indicator_scene(QWidget* parent):
    Kinstrument_scene(parent)
{
}

//datetime_t or time_t -> date_seq
qreal Kinstrument_indicator_scene::label_w_to_val_w(uint64_t l) const 
{
    if (!_label_map_w.size())
        return 0;

    if (_label_map_w.count(l))
        return _label_map_w.at(l);

    if (l<_label_map_w.begin()->first)
        return _label_map_w.begin()->second;

    if (l>_label_map_w.end()->first)
        return _label_map_w.end()->second;

    for (auto& m : _label_map_w){
        if (m.first > l)
            return m.second;
    }
    return _label_map_w.end()->second;
};

QString Kinstrument_indicator_scene::x_to_label_w(qreal x) const 
{
    int val_w = int(x_to_val_w(x) + 0.5);
    QString txt;
    if (_w_map_label.count(val_w)){
        if (_indCtx.timeMode == tDAY){
            txt.sprintf("%s", date_to_str(utc_to_date(_w_map_label.at(val_w))).c_str());
        }else{
            txt.sprintf("%s", utc_to_str(_w_map_label.at(val_w)).c_str());
        }
    }else{
        txt.sprintf("N/A");
    }
    return txt;
}

QString Kinstrument_indicator_scene::y_to_label_h(qreal y) const
{
    qreal val_h = y_to_val_h(y);
    QString txt;
    txt.sprintf("%0.2f", val_h / 100.0);    //TODO: tdx stock price precision = 1% of Yuan
    return txt;
}

//TODO: save for _view to make lable
void Kinstrument_indicator_scene::paint(indCtx_t indCtx, std::shared_ptr<data_panel_t> data_panel)
{
    clear();
    _indCtx = indCtx; 
    _data_panel = data_panel;

    if (indCtx.type == IND_VOL){
        paint_volumn();
    }
    return;
}

std::shared_ptr<infKQ_t> Kinstrument_indicator_scene::check_data_volumn(void)
{
    std::shared_ptr<infKQ_t> pInfoKQ;
    if (_indCtx.timeMode == tDAY){
        pInfoKQ = _data_panel->info.pDayKQ;
    }else if (_indCtx.timeMode == tMINU){
        pInfoKQ = _data_panel->info.pMinuKQ;
    }else{  //TODO
        return pInfoKQ;
    }

    if (!pInfoKQ || !pInfoKQ->size())
        return nullptr;
    if (!pInfoKQ->isNewAtBack())
        return nullptr;

    return pInfoKQ;
}

void Kinstrument_indicator_scene::calcCtx_volumn()
{
    std::shared_ptr<infKQ_t> pInfoKQ = check_data_volumn();
    if (!pInfoKQ)
        return;

    ctx_t ctx;
    ctx.set_val_h_max((*pInfoKQ)[0]->volume);
    //ctx.set_val_h_min((*pInfoKQ)[0]->volume);
	ctx.set_val_h_min(0);
    ctx.set_val_w_max(0);
    ctx.set_val_w_min(0);

    int n = 0;
    _label_map_w.clear();
    _w_map_label.clear();
    for(const auto& d : *pInfoKQ)
    {
        if (d->volume > ctx.val_h_max()){
            ctx.set_val_h_max(d->volume);
        }
        //if (d->volume < ctx.val_h_min()){
        //    ctx.set_val_h_min(d->volume);
        //}
        ctx.set_val_w_max(n);
        _label_map_w[d->_time] = n;
        _w_map_label[n] = d->_time;
        n++;
    }

	

    setCtx(ctx);

	initSceneCanvas();
}

void Kinstrument_indicator_scene::paint_volumn()
{
    std::shared_ptr<infKQ_t> pInfoKQ = check_data_volumn();
    if (!pInfoKQ)
        return;

    calcCtx_volumn();

    QList<logicRectData_h_t> vols;

    for(size_t i=0; i < pInfoKQ->size(); ++i)
    {
        const auto& d = (*pInfoKQ)[i];
        logicRectData_h_t v;
        v.seq = label_w_to_val_w(d->_time);
        v.val_top = d->volume;
        v.val_btm = 0;

        if (!vols.size()){
            v.positive = (*pInfoKQ)[i]->close_fq() > (*pInfoKQ)[i]->open_fq();
        }else{
            v.positive = (*pInfoKQ)[i]->close_fq() > (*pInfoKQ)[i-1]->close_fq();
        }
        vols.push_back(std::move(v));
    }

	KlogicRectGroup_h_t* Rect = new KlogicRectGroup_h_t(this);
	Rect->setColor(_colorpalette->positive_boxes[1], _colorpalette->negtive_boxes[1]);
	Rect->setVal(vols);
	Rect->mkGroupItems();
	Rect->setZValue(BAR_Z);
	this->addItem(Rect);

}

} // namespace QT
} // namespace S4


