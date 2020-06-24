#pragma once

#include "qt_Kviewer/s4Kinstrument_scene.h"
#include "qt_common/s4qt_data_if.h"


namespace S4{
namespace QT{

class Kinstrument_Kline_scene : public Kinstrument_scene
{
public:
    Kinstrument_Kline_scene(QWidget* parent = 0);

    void setInfoKQ(const std::shared_ptr<infKQ_t>& pInfoKQ);

    void setMAmap(const std::shared_ptr<std::map<int, std::shared_ptr<maQ_t>>>& pMAmap);


    void paint(void);

    //datetime_t or time_t -> date_seq
    virtual qreal label_w_to_val_w(uint64_t l) const override;

    virtual QString x_to_label_w(qreal x) const override;

    virtual QString y_to_label_h(qreal y) const override;
private:
    std::map<uint64_t, int> _label_map_w;
    std::map<int, uint64_t> _w_map_label;

    std::shared_ptr<infKQ_t> _pInfoKQ;
    std::shared_ptr<std::map<int, std::shared_ptr<maQ_t>>> _pMAmap;
    S4::timeMode_t _timeMode = timeMode_t::tUNKNOWN;
private:
    void calcCtx(void);

    void paint_infoKQ(void);
    
    void paint_MAmap(void);

    void paint_MA(int scope, const std::shared_ptr<maQ_t>& maQ);
};

} // namespace QT
} // namespace S4


