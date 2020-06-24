
#include "qt_Kviewer/s4Kinstrument_indicator_view.h"

namespace S4{
namespace QT{

Kinstrument_indicator_view::Kinstrument_indicator_view(Kinstrument_scene*scene, QWidget *parent):
    Kinstrument_view(scene, parent)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Kinstrument_indicator_view::paint(void){
    paintGridLines();
    //paintGridLabels();
    //onViewChange();
    //paintCrosshair();
}

void Kinstrument_indicator_view::onScaleChanged(qreal x_scale, qreal y_scale)
{
	scale(x_scale, 1.0);
	onViewChange();
}

void Kinstrument_indicator_view::onLabelCenterChanged(qreal label_x, qreal label_y)
{
	if(!_scene)
		return;

	qreal x = _scene->label_w_to_x(label_x) + _zoom_pos_fix.x();
	qreal y = mapToScene(0, height()/2).y();
	centerOn(x, y);
	onViewChange();

	QPointF view_mouse_pos = mapFromScene(x, y);
	onMouseChange(view_mouse_pos);
}

} // namespace QT
} // namespace S4


