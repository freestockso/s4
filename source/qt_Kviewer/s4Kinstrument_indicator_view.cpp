
#include "qt_Kviewer/s4Kinstrument_indicator_view.h"

namespace S4{
namespace QT{

Kinstrument_indicator_view::Kinstrument_indicator_view(Kinstrument_indicator_scene * scene, QWidget *parent):
    Kinstrument_view(scene, parent)
{
	//setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ctx_t ctx;
	ctx.sc_val_h_max = scene->getCtx().val_h_max();
	ctx.sc_val_h_min = scene->getCtx().val_h_min();
	ctx.sc_val_w_max = scene->getCtx().val_w_max();
	ctx.sc_val_w_min = scene->getCtx().val_w_min();
	setCtx(ctx);
	setGridGap_h(0.25);
}

void Kinstrument_indicator_view::paint(void){
    paintGridLines();
    //paintGridLabels();
    //onViewChange();
	//paintCrosshair();
	qDebug() << this->transform();
	qreal x_scale = 1;
	//qreal height = this->height();
	//qreal scene_h = _scene->sceneRect().height();
	qreal y_scale = 1;// scene_h / height;
	QTransform T;
	T.scale(x_scale, y_scale);
	Kinstrument_view::setTransform(T, false);
	qDebug() << this->transform();
}

void Kinstrument_indicator_view::onSetTransform(const QTransform& Ti, bool combine)
{
	QTransform T;
	qreal x_scale = Ti.m11();
	//qreal y_scale = this->height() / _scene->sceneRect().height();
	T.scale(x_scale, 1.0);
	Kinstrument_view::setTransform(T, combine);
}

//void Kinstrument_indicator_view::onScaleChanged(qreal x_scale, qreal y_scale)
//{
//	qreal _y_scale = height() / _scene->sceneRect().height();
//	scale(x_scale, _y_scale);
//	onViewChange();
//}

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


