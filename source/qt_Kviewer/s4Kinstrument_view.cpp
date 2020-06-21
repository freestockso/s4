#include "qt_Kviewer/s4Kinstrument_view.h"
#include <QDebug>
#include <QGraphicsLineItem>
#include <QtCore/qmath.h>
#include "qt_Kviewer/s4K_label.h"

namespace S4 {
namespace QT {

static const qreal zoom_rate = 1.08;
static const QPointF zoom_fix = { -10, -9 };

Kinstrument_view::Kinstrument_view(Kinstrument_scene*scene, QWidget *parent):
    QGraphicsView(scene, parent),
	_scene(scene)
{
	//TODO: scrollBar not always On
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    _colorpalette = std::make_shared<qt_colorpalette_t>();

	this->setMouseTracking(true);

}

//Kinstrument_view::void cursorPosition(QPointF);

qreal Kinstrument_view::val_to_sceneh(qreal val)
{
	qreal y_o;
	if (!_isLogCoor) {
		qreal p_gap = _scene->height() / (_scene->getCtx().val_h_max() - _scene->getCtx().val_h_min());
		y_o = p_gap * (val - _scene->getCtx().val_h_min()) + _scene->sceneRect().y();
	}
	else {
		qreal p_max_h = qLn(_scene->getCtx().val_h_max() / _scene->getCtx().val_h_min()) / qLn(1.1);
		p_max_h = _scene->height() / p_max_h;
		y_o = qLn(val / _scene->getCtx().val_h_min()) / qLn(1.1) * p_max_h;
	}
	return y_o;
}

qreal Kinstrument_view::sceneh_to_val(qreal h)
{
	if (!_isLogCoor) {
		return (_scene->getCtx().val_h_max() - _scene->getCtx().val_h_min()) * h / _scene->height() + _scene->getCtx().val_h_min();
	}
	else
	{
		qreal coor = h * qLn(_scene->getCtx().val_h_max() / _scene->getCtx().val_h_min()) / _scene->height() / qLn(1.1);
		qreal ex = qExp(coor * qLn(1.1));
		return ex * _scene->getCtx().val_h_min();
	}
}

void Kinstrument_view::mousePressEvent(QMouseEvent* event)
{
}

void Kinstrument_view::mouseMoveEvent(QMouseEvent* event)
{
	_view_pos = event->pos();
	_scene_mouse = QGraphicsView::mapToScene(_view_pos.x(), _view_pos.y());

	//TODO: move to resize?
	qreal w = width();
	qreal h = height();
	_scene_lu = QGraphicsView::mapToScene(0, 0);
	_scene_rd = QGraphicsView::mapToScene(w - 1, h - 1);
	_scene_rd -= QPointF(17, 17);//scrollBar size

	paintCrosshair();
}

void Kinstrument_view::wheelEvent(QWheelEvent* event)
{
	//qDebug() << "Delta: " << event->angleDelta();
	_view_pos = event->pos();
	_scene_mouse = QGraphicsView::mapToScene(_view_pos.x(), _view_pos.y());

	int angle = event->angleDelta().y();

	if (angle < 0)
		zoomOut();
	else
		zoomIn();

	paintCrosshair();
}

void Kinstrument_view::grabTransInfo()
{

	_antiT.reset();
	_antiT.scale(1.0 / transform().m11(), 1.0 / transform().m22());

	_XYantiScale.setX(abs(_antiT.m11()));
	_XYantiScale.setY(abs(_antiT.m22()));
}


void Kinstrument_view::resetTransform()
{
	QGraphicsView::resetTransform();
	grabTransInfo();
}


void Kinstrument_view::setTransform(const QTransform& matrix, bool combine)
{
	QGraphicsView::setTransform(matrix, combine);
	grabTransInfo();
}



void Kinstrument_view::zoomIn()
{
	//qDebug() << "ZoomIn()";

	if (_scene->items().isEmpty())
		return;

	setMouseTracking(false);
	QPointF scene_center = QGraphicsView::mapToScene(width() / 2, height() / 2);
	QPointF pre_pos_dlt = scene_center - _scene_mouse;
	QPointF now_center = pre_pos_dlt / zoom_rate + _scene_mouse;// +QPointF(this->transform().m11() * zoom_fix.x(), this->transform().m22() * zoom_fix.y());
	QPointF fix = QPointF(zoom_fix.x() / this->transform().m11(), zoom_fix.y() / this->transform().m22());	//unkown reson...
	now_center += fix;
	//qDebug() << "+";
	//qDebug() << "_scene_mouse " << _scene_mouse;
	//qDebug() << "scene_center " << scene_center;
	//qDebug() << "pre_pos_dlt " << pre_pos_dlt;
	//qDebug() << "now_center " << now_center;
	//qDebug() << "pre_0 " << QGraphicsView::mapToScene(0, 0);

	QTransform T;
	T.scale(zoom_rate, zoom_rate);

	QTransform transform = this->transform();
	transform *= T;
	setTransform(transform);

	centerOn(now_center);
	//qDebug() << "now_0 " << QGraphicsView::mapToScene(0, 0);
	//qDebug() << "now_center " << QGraphicsView::mapToScene(width() / 2, height() / 2);
	//QPointF um = QGraphicsView::mapToScene(width() / 2, height() / 2) - now_center;
	//qDebug() << "unmatch = " << um;
	//qDebug() << "xs=" << this->transform().m11() << "  ys=" << this->transform().m22();
	//qDebug() << "unmatch * s = " << um.x() * this->transform().m11() << um.y() * this->transform().m22();
	//qDebug() << "---------------------------------";

	setMouseTracking(true);
	return;

}
void Kinstrument_view::zoomOut()
{
	// qDebug() << "ZoomOut()";

	if (_scene->items().isEmpty())
		return;

	setMouseTracking(false);
	QPointF scene_center = QGraphicsView::mapToScene(width() / 2, height() / 2);
	QPointF pre_pos_dlt = scene_center - _scene_mouse;
	QPointF now_center = pre_pos_dlt * zoom_rate + _scene_mouse;
	QPointF fix = QPointF(zoom_fix.x() / this->transform().m11(), zoom_fix.y() / this->transform().m22());	//unkown reson...
	now_center += fix;
	//qDebug() << "-";
	//qDebug() << "_scene_mouse " << _scene_mouse;
	//qDebug() << "scene_center " << scene_center;
	//qDebug() << "pre_pos_dlt " << pre_pos_dlt;
	//qDebug() << "now_center " << now_center;
	//qDebug() << "pre_0 " << QGraphicsView::mapToScene(0, 0);

	QTransform T;
	T.scale(1.0 / zoom_rate, 1.0 / zoom_rate);

	QTransform transform = this->transform();
	transform *= T;
	setTransform(transform);

	centerOn(now_center);
	//qDebug() << "now_0 " << QGraphicsView::mapToScene(0, 0);
	//qDebug() << "now_center " << QGraphicsView::mapToScene(width() / 2, height() / 2);
	//QPointF um = QGraphicsView::mapToScene(width() / 2, height() / 2) - now_center;
	//qDebug() << "unmatch = " << um;
	//qDebug() << "xs=" << this->transform().m11() << "  ys=" << this->transform().m22();
	//qDebug() << "unmatch * s = " << um.x() * this->transform().m11() << um.y() * this->transform().m22();
	//qDebug() << "---------------------------------";

	setMouseTracking(true);
	return;

}

QPointF Kinstrument_view::getXYscale()
{
	QTransform T;// = antiTransformY();
	qreal xscale = transform().m11();
	qreal yscale = transform().m22();
	if (xscale < 0)xscale = -xscale;
	if (yscale < 0)yscale = -yscale;
	return std::move(QPointF(xscale, yscale));
}

void Kinstrument_view::paintLabel(QGraphicsItemGroup*& pGroup, const QPointF& view_pos, const QString& txt, const color_pair_t& color_pair, int zV,
	bool onLeft, int shift)
{
	if ( !pGroup)
		pGroup = _scene->createItemGroup(QList<QGraphicsItem*>{});

	QPointF scene_pos = mapToScene(view_pos.x(), view_pos.y());
	//if (scene_pos.y() < 0)
	//	scene_pos.setY(0);
	//if (scene_pos.y() > _scene->height())
	//	scene_pos.setY(_scene->height());
	//if (scene_pos.x() < 0)
	//	scene_pos.setX(0);
	//if (scene_pos.x() > _scene->width())
	//	scene_pos.setX(_scene->width());

	qreal x = scene_pos.x();//_scene_pos.x();
	qreal y = scene_pos.y();

	qreal rx = getXYscale().x();//_antiT.m11();
	//qreal ry = _antiT.m22();
	Klabel_t* label_x = new Klabel_t;
	label_x->setText(txt);

	if (onLeft) {
		x -= (shift + label_x->boundingRect().width()) / rx;
	}
	else {
		x += shift / rx;
	}
	if (x < _scene_lu.x())
		x = _scene_lu.x();
	if (x >= _scene_rd.x() - label_x->boundingRect().width())
		x = _scene_rd.x() - label_x->boundingRect().width();
	//y += 20 / ry;
	if (view_pos.y() >= height() - label_x->boundingRect().height() - 17)
		y -= label_x->boundingRect().height();

	label_x->setTransform(_antiT);

	label_x->setColor(color_pair);
	label_x->setPos(x, y);
	label_x->setZValue(zV);
	pGroup->addToGroup(label_x);

}

void Kinstrument_view::paintCrosshair()
{
	if (_crossLine) {
		_scene->removeItem(_crossLine);				//从scene删掉元素（以及group），但没有释放内存
		delete _crossLine;							//好像解决了内存泄露
	}

	QPen xPen = QPen(_colorpalette->crosshair, _XYantiScale.x()/*width*/, Qt::DashLine);
	QPen yPen = QPen(_colorpalette->crosshair, _XYantiScale.y()/*width*/, Qt::DashLine);

	QList<QGraphicsItem*> cl;
	if (_scene_mouse.y() >= _scene->sceneRect().y() && _scene_mouse.y() < _scene->sceneRect().y()+_scene->height()) {
		QGraphicsLineItem* hline = new QGraphicsLineItem;
		hline->setLine(_scene_lu.x(), _scene_mouse.y(), _scene_rd.x(), _scene_mouse.y());
		hline->setPen(xPen);
		cl.append(hline);
	}

	if (_scene_mouse.x() >= _scene->sceneRect().x() && _scene_mouse.x() < _scene->sceneRect().x()+_scene->width()) {
		QGraphicsLineItem* vline = new QGraphicsLineItem;
		vline->setLine(_scene_mouse.x(), _scene_lu.y(), _scene_mouse.x(), _scene_rd.y());
		vline->setPen(yPen);
		cl.append(vline);
	}
	_crossLine = _scene->createItemGroup(cl);
	_crossLine->setZValue(100);

	{
		QString txt_y = _scene->y_to_val_label(_scene_mouse.y());
		paintLabel(_crossLine, _view_pos, txt_y, _colorpalette->labels[0], 100);
	}

	{
		QString txt_x = _scene->x_to_val_label(_scene_mouse.x());
		paintLabel(_crossLine, {_view_pos.x(), double(height()-40)}, txt_x, _colorpalette->labels[0], 100, false);
	}


}

void Kinstrument_view::paintGrid()
{

}








}
}
