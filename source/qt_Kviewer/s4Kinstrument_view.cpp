#include "qt_Kviewer/s4Kinstrument_view.h"
#include <QDebug>
#include <QGraphicsLineItem>

namespace S4 {
namespace QT {

static const qreal zoom_rate = 1.08;
static const QPointF zoom_fix = { -10, -9 };

Kinstrument_view::Kinstrument_view(QGraphicsScene *scene, QWidget *parent):
    QGraphicsView(scene, parent),
	_scene(scene)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    _colorpalette = std::make_shared<qt_colorpalette_t>();

	this->setMouseTracking(true);

}

//Kinstrument_view::void cursorPosition(QPointF);


void Kinstrument_view::mousePressEvent(QMouseEvent* event)
{
}

void Kinstrument_view::mouseMoveEvent(QMouseEvent* event)
{
	_view_pos = event->pos();
	_scene_pos = QGraphicsView::mapToScene(_view_pos.x(), _view_pos.y());

	paintCrosshair();
}

void Kinstrument_view::wheelEvent(QWheelEvent* event)
{
	//qDebug() << "Delta: " << event->angleDelta();

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
void Kinstrument_view::paintCrosshair()
{
	if (_crossLine) {
		//_scene->destroyItemGroup(_crossLine);
		_scene->removeItem(_crossLine);				//从scene删掉元素（以及group），但没有释放内存
		//scene->destroyItemGroup(_crossLine);		//解包，包中元素打散回scene
		delete _crossLine;							//好像解决了内存泄露
	}

	QTransform T;// = antiTransformY();
	qreal xscale = transform().m11();
	qreal yscale = transform().m22();
	if (xscale < 0)xscale = -xscale;
	if (yscale < 0)yscale = -yscale;
	QPen xPen = QPen(_colorpalette->crosshair, 1.0 / yscale/*width*/, Qt::DashLine);
	QPen yPen = QPen(_colorpalette->crosshair, 1.0 / xscale/*width*/, Qt::DashLine);

	QList<QGraphicsItem*> cl;
	if (_scene_pos.y() >= _scene->sceneRect().y() && _scene_pos.y() < _scene->sceneRect().y()+_scene->height()) {
		QGraphicsLineItem* hline = new QGraphicsLineItem;
		hline->setLine(_scene->sceneRect().x(), _scene_pos.y(), _scene->sceneRect().x()+_scene->width(), _scene_pos.y());
		hline->setPen(xPen);
		//hline->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIgnoresTransformations, true);
		//_crossLine->addToGroup(hline);
		cl.append(hline);
	}

	if (_scene_pos.x() >= _scene->sceneRect().x() && _scene_pos.x() < _scene->sceneRect().x()+_scene->width()) {
		QGraphicsLineItem* vline = new QGraphicsLineItem;
		vline->setLine(_scene_pos.x(), _scene->sceneRect().y(), _scene_pos.x(), _scene->sceneRect().y()+_scene->height());
		vline->setPen(yPen);
		//vline->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIgnoresTransformations, true);
		//_crossLine->addToGroup(vline);
		cl.append(vline);
	}
	_crossLine = _scene->createItemGroup(cl);
}










}
}
