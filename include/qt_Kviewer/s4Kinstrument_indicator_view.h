#pragma once

#include "qt_Kviewer/s4Kinstrument_view.h"
#include "qt_Kviewer/s4Kinstrument_indicator_scene.h"
#include "qt_common/s4qt_data_if.h"


namespace S4{
namespace QT{
    
class Kinstrument_indicator_view : public Kinstrument_view
{
public:
    Kinstrument_indicator_view(Kinstrument_indicator_scene *scene, QWidget *parent = 0);


    void paint(void);

    


public slots:
    //virtual void onScaleChanged(qreal x_scale, qreal y_scale) override;
    virtual void onLabelCenterChanged(qreal label_x, qreal label_y) override;
	virtual void onSetTransform(const QTransform&, bool) override;

};

} // namespace QT
} // namespace S4


