#pragma once

#include "qt_Kviewer/s4Kinstrument_view.h"
#include "qt_common/s4qt_data_if.h"


namespace S4{
namespace QT{
    
class Kinstrument_Kline_view : public Kinstrument_view
{
public:
    Kinstrument_Kline_view(Kinstrument_scene*scene, QWidget *parent = 0);

    void setCtx(const std::shared_ptr<infKQ_t>& pInfoKQ);

    void paint(void);

};

} // namespace QT
} // namespace S4


