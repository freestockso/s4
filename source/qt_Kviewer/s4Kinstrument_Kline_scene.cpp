#pragma once
#include "qt_Kviewer/s4Kinstrument_Kline_scene.h"
#include "common/s4time.h"
#include "qt_Kviewer/s4KlogicBar.h"
#include "qt_Kviewer/s4KlogicCurve.h"


namespace S4{
namespace QT{

#define BAR_Z (51)
#define MA_Z (52)
    
Kinstrument_Kline_scene::Kinstrument_Kline_scene(QWidget* parent):
    Kinstrument_scene(parent)
{
}

void Kinstrument_Kline_scene::setInfoKQ(const std::shared_ptr<infKQ_t>& pInfoKQ){
    _pInfoKQ = pInfoKQ;
}

void Kinstrument_Kline_scene::setMAmap(const std::shared_ptr<std::map<int, std::shared_ptr<maQ_t>>>& pMAmap){
    _pMAmap = pMAmap;
}


void Kinstrument_Kline_scene::paint(void)
{
    calcCtx();
    initSceneCanvas();
    paint_infoKQ();
    paint_MAmap();
}

//datetime_t or time_t -> date_seq
qreal Kinstrument_Kline_scene::label_w_to_val_w(uint64_t l) const 
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

QString Kinstrument_Kline_scene::x_to_label_w(qreal x) const 
{
    int val_w = int(x_to_val_w(x) + 0.5);
    QString txt;
    if (_w_map_label.count(val_w)){
        if (_timeMode == tDAY){
            txt.sprintf("%s", date_to_str(utc_to_date(_w_map_label.at(val_w))).c_str());
        }else{
            txt.sprintf("%s", utc_to_str(_w_map_label.at(val_w)).c_str());
        }
    }else{
        txt.sprintf("N/A");
    }
    return txt;
}

QString Kinstrument_Kline_scene::y_to_label_h(qreal y) const
{
    qreal val_h = y_to_val_h(y);
    QString txt;
    txt.sprintf("%0.2f", val_h / 100.0);    //TODO: tdx stock price precision = 1% of Yuan
    return txt;
}

void Kinstrument_Kline_scene::calcCtx(void)
{
    if (!_pInfoKQ || !_pInfoKQ->size())
        return;

    if (!_pInfoKQ->isNewAtBack())
        return;

    ctx_t ctx;
    ctx.set_val_h_max((*_pInfoKQ)[0]->high_fq());
    ctx.set_val_h_min((*_pInfoKQ)[0]->low_fq());
    ctx.set_val_w_max(0);
	ctx.set_val_w_min(0);

    int n = 0;
    _label_map_w.clear();
    _w_map_label.clear();
    for(const auto& d : *_pInfoKQ)
    {
        if (d->high > ctx.val_h_max()){
            ctx.set_val_h_max(d->high_fq());
        }
        if (d->low < ctx.val_h_min()){
            ctx.set_val_h_min(d->low_fq());
        }
        ctx.set_val_w_max(n);
        _label_map_w[d->_time] = n;
        _w_map_label[n] = d->_time;
        n++;
    }

    setCtx(ctx);
}

//TODO: save for _view to make lable
void Kinstrument_Kline_scene::paint_infoKQ(void)
{
    if (!_pInfoKQ || !_pInfoKQ->size())
        return;

    _timeMode = _pInfoKQ->front()->_tMode;

    QList<logicBarData_t> bars;
    
    for(const auto& d : *_pInfoKQ)
    {
        logicBarData_t bar;
        bar.seq = label_w_to_val_w(d->_time);
        bar.O = d->open_fq();
        bar.C = d->close_fq();
        bar.H = d->high_fq();
        bar.L = d->low_fq();

        if (!bars.size()){
            bar.lastC = bar.O;
        }else{
            bar.lastC = bars.back().C;
        }
        bars.push_back(std::move(bar));
    }
    
    KlogicBarGroup_t* barGroup = new KlogicBarGroup_t(this);
    barGroup->setColor(_colorpalette->positive_boxes[0], _colorpalette->negtive_boxes[0]);
    barGroup->setType(KlogicBar_t::barType_t::BAR_JPN);
    barGroup->setLineWidth(4);
    barGroup->setVal(bars);
    barGroup->mkGroupItems();
    barGroup->setZValue(BAR_Z);
    this->addItem(barGroup);
}

void Kinstrument_Kline_scene::paint_MAmap(void){
    int n = 0;
    for(auto& m : *_pMAmap){
        paint_MA(n++, m.second);
    }
}

//TODO: save ind&scope&value&colors for _view to make label
void Kinstrument_Kline_scene::paint_MA(int ind, const std::shared_ptr<maQ_t>& maQ){
    if( !maQ || !maQ->size())
        return;

    QList<QPointF> dots;
    for (auto& ma : *maQ){
        QPointF dot;
        dot.setX(label_w_to_val_w(ma->_time));
        dot.setY(ma->C());
        dots.push_back(std::move(dot));
    }
	KlogicCurve_t* curve = new KlogicCurve_t(this);
	curve->setLineStyle(Qt::PenStyle::SolidLine);
	curve->setColor(_colorpalette->curve[ind % _colorpalette->curve.size()]);
	curve->setLineWidth(1);
	curve->setVal(dots);
	curve->mkGroupItems();
	curve->setZValue(MA_Z);
	this->addItem(curve);
}

} // namespace QT
} // namespace S4

