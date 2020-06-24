#pragma once

#include "qt_Kviewer/s4Kinstrument_indicator_view.h"
#include "qt_Kviewer/s4Kinstrument_indicator_scene.h"
#include "qt_common/s4qt_data_if.h"

#include <QTabWidget>
#include <QKeyEvent>

namespace S4{
namespace QT{
    
class Kinstrument_indicator_tab: public QTabWidget
{
    Q_OBJECT
public:
    explicit Kinstrument_indicator_tab(QWidget *parent = nullptr);

    void setInstrument(std::shared_ptr<data_panel_t> data_panel);

public slots:
    void paint(Kinstrument_indicator_scene::ind_type type, timeMode_t timeMode);

protected:
    std::shared_ptr<data_panel_t> _data_panel;
    std::map<int, Kinstrument_indicator_scene::indCtx_t> _tab_ctx;
};


} // namespace QT
} // namespace S4
