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
    explicit Kinstrument_Kline_tab(QWidget *parent = nullptr);

    void setInstrument(std::shared_ptr<data_panel_t> data_panel);

protected:
    std::shared_ptr<data_panel_t> _data_panel;
    timeMode_t _timeMode = tUNKNOWN;
};


} // namespace QT
} // namespace S4
