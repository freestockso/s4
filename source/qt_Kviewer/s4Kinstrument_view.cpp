#include "qt_Kviewer/s4Kinstrument_view.h"
#include <QDebug>
#include <QGraphicsLineItem>
#include <QtCore/qmath.h>

namespace S4 {
namespace QT {

static const qreal zoom_rate = 1.08;
static const QPointF zoom_fix = { -10, -9 };

Kinstrument_view::Kinstrument_view(Kinstrument_scene*scene, QWidget *parent):
    QGraphicsView(scene, parent),
	_scene(scene)
{
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
	_scene_pos = QGraphicsView::mapToScene(_view_pos.x(), _view_pos.y());
	_scene_lu = QGraphicsView::mapToScene(0, 0);
	_scene_rd = QGraphicsView::mapToScene(width()-1, height()-1);

	paintCrosshair();
}

void Kinstrument_view::wheelEvent(QWheelEvent* event)
{
	//qDebug() << "Delta: " << event->angleDelta();
	_view_pos = event->pos();
	_scene_pos = QGraphicsView::mapToScene(_view_pos.x(), _view_pos.y());
	_scene_lu = QGraphicsView::mapToScene(0, 0);
	_scene_rd = QGraphicsView::mapToScene(width() - 1, height() - 1);

	int angle = event->angleDelta().y();

	if (angle < 0)
		zoomOut();
	else
		zoomIn();

	paintCrosshair();
}

void Kinstrument_view::zoomIn()
{
	//qDebug() << "ZoomIn()";

	if (_scene->items().isEmpty())
		return;

	setMouseTracking(false);
	QPointF scene_center = QGraphicsView::mapToScene(width() / 2, height() / 2);
	QPointF pre_pos_dlt = scene_center - _scene_pos;
	QPointF now_center = pre_pos_dlt / zoom_rate + _scene_pos;// +QPointF(this->transform().m11() * zoom_fix.x(), this->transform().m22() * zoom_fix.y());
	QPointF fix = QPointF(zoom_fix.x() / this->transform().m11(), zoom_fix.y() / this->transform().m22());	//unkown reson...
	now_center += fix;
	//qDebug() << "+";
	//qDebug() << "_scene_pos " << _scene_pos;
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
	QPointF pre_pos_dlt = scene_center - _scene_pos;
	QPointF now_center = pre_pos_dlt * zoom_rate + _scene_pos;
	QPointF fix = QPointF(zoom_fix.x() / this->transform().m11(), zoom_fix.y() / this->transform().m22());	//unkown reson...
	now_center += fix;
	//qDebug() << "-";
	//qDebug() << "_scene_pos " << _scene_pos;
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


void Kinstrument_view::paintCrosshair()
{
	if (_crossLine) {
		//_scene->destroyItemGroup(_crossLine);
		_scene->removeItem(_crossLine);				//从scene删掉元素（以及group），但没有释放内存
		//scene->destroyItemGroup(_crossLine);		//解包，包中元素打散回scene
		delete _crossLine;							//好像解决了内存泄露
	}

	QPointF XYscale = getXYscale();
	QPen xPen = QPen(_colorpalette->crosshair, 1.0 / XYscale.x()/*width*/, Qt::DashLine);
	QPen yPen = QPen(_colorpalette->crosshair, 1.0 / XYscale.y()/*width*/, Qt::DashLine);

	QList<QGraphicsItem*> cl;
	if (_scene_pos.y() >= _scene->sceneRect().y() && _scene_pos.y() < _scene->sceneRect().y()+_scene->height()) {
		QGraphicsLineItem* hline = new QGraphicsLineItem;
		hline->setLine(_scene_lu.x(), _scene_pos.y(), _scene_rd.x(), _scene_pos.y());
		hline->setPen(xPen);
		//hline->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIgnoresTransformations, true);
		//_crossLine->addToGroup(hline);
		cl.append(hline);
	}

	if (_scene_pos.x() >= _scene->sceneRect().x() && _scene_pos.x() < _scene->sceneRect().x()+_scene->width()) {
		QGraphicsLineItem* vline = new QGraphicsLineItem;
		vline->setLine(_scene_pos.x(), _scene_lu.y(), _scene_pos.x(), _scene_rd.y());
		vline->setPen(yPen);
		//vline->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIgnoresTransformations, true);
		//_crossLine->addToGroup(vline);
		cl.append(vline);
	}
	_crossLine = _scene->createItemGroup(cl);
	_crossLine->setZValue(100);

	QTransform T;
	T.scale(1.0 / transform().m11(), 1.0 / transform().m22());

	qreal val_h = _scene->y_to_val_h(_scene_pos.y());
	QString txt;
	txt.sprintf("%0.2f", val_h);
	QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem;
	text->setText(txt);
	text->setPos(_scene_pos.x(), _scene_pos.y());
	text->setBrush(_colorpalette->labels[1].front);
	text->setTransform(T);
	text->setZValue(100);
	_crossLine->addToGroup(text);

	QGraphicsRectItem* box = new QGraphicsRectItem;
	box->setRect(text->boundingRect());
	box->setPen(QPen(Qt::NoPen));
	box->setPos(_scene_pos.x(), _scene_pos.y());
	box->setBrush(_colorpalette->labels[1].back);
	box->setTransform(T);
	box->setZValue(99);
	_crossLine->addToGroup(box);

}

void Kinstrument_view::paintGrid()
{

}








}
}
