#pragma once

#include "common/s4time.h"
#include "qt_Kviewer/s4Kinstrument_scene.h"
#include "qt_Kviewer/s4KlogicBar.h"


namespace S4{
namespace QT{

#define BAR_Z (51)
    
class Kinstrument_Kline_scene : public Kinstrument_scene
{
public:
    Kinstrument_Kline_scene(QWidget* parent = 0):
        Kinstrument_scene(parent)
    {
    }

    void setInfoKQ(const std::shared_ptr<infKQ_t>& pInfoKQ){
        _pInfoKQ = pInfoKQ;
    }

    void setMAmap(const std::shared_ptr<std::map<int, std::shared_ptr<maQ_t>>>& pMAmap){
        _pMAmap = pMAmap;
    }


    void paint(void)
    {
        calcCtx();
        initSceneCanvas();
        paint_infoKQ();
        paint_MAmap();
    }

    //datetime_t or time_t -> date_seq
    virtual qreal label_w_to_val_w(uint64_t l) const override{
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

    virtual QString x_to_label_w(qreal x) const override
    {
        int val_w = int(x_to_val_w(x) + 0.5);
        QString txt;
        if (_w_map_label.count(val_w)){
            txt.sprintf("%s", date_to_str(_w_map_label.at(val_w)).c_str());
        }else{
            txt.sprintf("N/A");
        }
        return txt;
    }

    virtual QString y_to_label_h(qreal y) const override
    {
        qreal val_h = y_to_val_h(y);
        QString txt;
        txt.sprintf("%0.2f", val_h / 100.0);    //TODO: tdx stock price precision = 1% of Yuan
        return txt;
    }
private:
    std::map<uint64_t, int> _label_map_w;
    std::map<int, uint64_t> _w_map_label;

    std::shared_ptr<infKQ_t> _pInfoKQ;
    std::shared_ptr<std::map<int, std::shared_ptr<maQ_t>>> _pMAmap;

private:
    void calcCtx(void){
        if (!_pInfoKQ || !_pInfoKQ->size())
            return;

        if (!_pInfoKQ->isNewAtBack())
            return;

        ctx_t ctx;
        ctx.set_val_h_max((*_pInfoKQ)[0]->high);
        ctx.set_val_h_min((*_pInfoKQ)[0]->low);
        ctx.set_val_w_max(0);
        ctx.set_val_w_min(0);

        int n = 0;
        _label_map_w.clear();
        _w_map_label.clear();
        for(const auto& d : *_pInfoKQ)
        {
            if (d->high > ctx.val_h_max()){
                ctx.set_val_h_max(d->high);
            }
            if (d->low < ctx.val_h_min()){
                ctx.set_val_h_min(d->low);
            }
            ctx.set_val_w_max(n);
            _label_map_w[d->_date] = n;
            _w_map_label[n] = d->_date;
            n++;
        }

        setCtx(ctx);
    }

    void paint_infoKQ(void){
        if (!_pInfoKQ || !_pInfoKQ->size())
            return;

        QList<logicBarData_t> bars;
        
        for(const auto& d : *_pInfoKQ)
        {
            logicBarData_t bar;
            bar.seq = label_w_to_val_w(d->_date);
            bar.O = d->open;
            bar.C = d->close;
            bar.H = d->high;
            bar.L = d->low;

            if (!bars.size()){
                bar.lastC = bar.O;
            }else{
                bar.lastC = bars.back().C;
            }
            bars.push_back(std::move(bar));
        }
        
        KlogicBarGroup_t* barGroup = new KlogicBarGroup_t(this);
        barGroup->setColor(_colorpalette->positive_boxes[0], _colorpalette->negtive_boxes[0]);
        // barGroup->setType(KlogicBar_t::barType_t::BAR_JPN);
        barGroup->setLineWidth(2);
        barGroup->setVal(bars);
        barGroup->mkGroupItems();
        barGroup->setZValue(BAR_Z);
        this->addItem(barGroup);
    }
    
    void paint_MAmap(void){
    }

};

} // namespace QT
} // namespace S4


