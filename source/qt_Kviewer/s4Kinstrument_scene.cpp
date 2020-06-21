#include "qt_Kviewer/s4Kinstrument_scene.h"
#include <QGraphicsLineItem>
#include <QtCore/qmath.h>
#include <QDebug>


namespace S4 {
namespace QT {

#define SCENE_Z 50

Kinstrument_scene::Kinstrument_scene(QWidget* parent):
    QGraphicsScene(parent)
{
    _colorpalette = std::make_shared<qt_colorpalette_t>();
    drawBK();
	drawTest();
}

void Kinstrument_scene::initSceneCanvas()
{
	//expand ctx
	_ctx.set_val_h_max( _ctx.val_h_max()*1.1);
	_ctx.set_val_h_min( _ctx.val_h_min()*0.9);
	_ctx.set_val_w_max( _ctx.val_w_max()+0.5);
	_ctx.set_val_w_min( _ctx.val_w_min()-0.5);

	qreal height = _ctx.val_h_10percent_pxl() * qLn(_ctx.val_h_max() / _ctx.val_h_min()) / qLn(1.1);

	qreal width = _ctx.val_w_max() - _ctx.val_w_min() + 10;	// 10 for margin
	width *= _ctx.val_w_pxl();
	
	setSceneRect(-_ctx.val_w_pxl() * 0.5, 0, width, height);

	_h_val_pxl = (_ctx.val_h_max() - _ctx.val_h_min()) / (this->height());

	_h_log_max = qLn(_ctx.val_h_max()) / qLn(1.1);
	_h_log_min = qLn(_ctx.val_h_min()) / qLn(1.1);
	_h_log_pxl = (_h_log_max - _h_log_min) / (this->height());

	_w_val_pxl = (_ctx.val_w_max() - _ctx.val_w_min()) / (this->width() - 1);
}

//Kinstrument_scene::void cursorPosition(QPointF);
qreal Kinstrument_scene::val_h_to_y(qreal val) const
{
	qreal y_o;
	if (!_isLogCoor) {
		y_o = height() - (val - _ctx.val_h_min()) / _h_val_pxl;	//
	}
	else {
		y_o = qLn(_ctx.val_h_max() / val) / qLn(1.1) / _h_log_pxl;
	}
	return y_o;
}

qreal Kinstrument_scene::y_to_val_h(qreal y) const
{
	if (!_isLogCoor) {
		return _ctx.val_h_max() - y * _h_val_pxl;
	}
	else
	{
		qreal log_coor = _h_log_max - y * _h_log_pxl;
		qreal ex = qExp(log_coor * qLn(1.1));
		return ex;
	}
}

qreal Kinstrument_scene::val_w_to_x(qreal val) const
{
	qreal x_o;
	x_o = (val - _ctx.val_w_min()) / _w_val_pxl + sceneRect().x();	//
	return x_o;
}

qreal Kinstrument_scene::x_to_val_w(qreal x) const
{
	return (x - sceneRect().x()) * _w_val_pxl + _ctx.val_w_min();
}
QString Kinstrument_scene::y_to_val_label(qreal y) const
{
	qreal val_h = y_to_val_h(y);
	QString txt;
	txt.sprintf("%0.2f", val_h);
	return txt;
}
QString Kinstrument_scene::x_to_val_label(qreal x) const
{
	int val_w = int(x_to_val_w(x) + 0.5);
	QString txt;
	txt.sprintf("%d", val_w);
	return txt;
}

void Kinstrument_scene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}

void Kinstrument_scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}

void Kinstrument_scene::drawBK()
{
	//this->setAutoFillBackground(true);
	//QPalette palette;
	//palette.setColor(QPalette::Background, _colorpalette->background);
	//this->setPalette(palette);
	//this->drawBackground(, this->sceneRect())
	QBrush brush(_colorpalette->background, Qt::SolidPattern);
	setBackgroundBrush(brush);
}

void Kinstrument_scene::drawTest()
{
	qreal v_m = 1;
	qreal v_M = 20;
	qreal w_m = 0;
	qreal w_M = 100;
	ctx_t test_ctx(
		v_m,
		v_M,
		w_m,
		w_M
	);
	setCtx(test_ctx);

	QPen pen = QPen(_colorpalette->positive_boxes[0].body, 1.0/*this param Sets the pen width to the given width in pixels with integer precision.*/);

	qreal x_w_min = val_w_to_x(w_m);
	qreal x_w_max = val_w_to_x(w_M);
	qreal y_v_min = height();//val_h_to_y(v_m);
	qreal y_v_max = 0;//val_h_to_y(v_M);
	//V
	for (qreal v = v_m; v < v_M*1.1; v *=1.1) {
		qreal y = val_h_to_y(v);
		QGraphicsLineItem* line = new QGraphicsLineItem(x_w_min, y, x_w_max, y);
		line->setPen(pen);
		line->setZValue(SCENE_Z);
		addItem(line);

		QString txt;
		txt.sprintf("%0.2f", v);
		QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem;
		text->setText(txt);
		text->setPos(x_w_min, y);
		text->setBrush(_colorpalette->labels[1].front);
		text->setZValue(SCENE_Z);
		addItem(text);

		QGraphicsRectItem* box = new QGraphicsRectItem;
		box->setRect(text->boundingRect());
		box->setPen(QPen(Qt::NoPen));
		box->setPos(x_w_min, y);
		box->setBrush(_colorpalette->labels[1].back);
		text->setZValue(SCENE_Z-1);
		addItem(box);
	}

	pen = QPen(_colorpalette->negtive_boxes[0].body, 1.0/*this param Sets the pen width to the given width in pixels with integer precision.*/);
	//H
	for (qreal w = w_m; w < w_M + 1; w += 1) {
		qreal x = val_w_to_x(w);
		QGraphicsLineItem* line = new QGraphicsLineItem(x, y_v_max, x, y_v_min);
		line->setPen(pen);
		line->setZValue(SCENE_Z);
		addItem(line);

		QString txt;
		txt.sprintf("%0.0f", w);
		QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem;
		text->setText(txt);
		text->setPos(x, y_v_max);
		text->setBrush(_colorpalette->labels[1].front);
		text->setZValue(SCENE_Z);
		addItem(text);

		QGraphicsRectItem* box = new QGraphicsRectItem;
		box->setRect(text->boundingRect());
		box->setPen(QPen(Qt::NoPen));
		box->setPos(x, y_v_max);
		box->setBrush(_colorpalette->labels[1].back);
		text->setZValue(SCENE_Z-1);
		addItem(box);
	}
	//for (qreal x = 0; x < x_max; x += 100) {
	//	for (qreal y = 0; y < y_max; y += 100) {
	//		QString txt;
	//		txt.sprintf("%0.0f,%0.0f", x, y);
	//		QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem;
	//		text->setText(txt);
	//		text->setPos(x, y);
	//		text->setBrush(_colorpalette->labels[1].front);
	//		text->setZValue(100);
	//		addItem(text);

	//		QGraphicsRectItem* box = new QGraphicsRectItem;
	//		box->setRect(text->boundingRect());
	//		box->setPen(QPen(Qt::NoPen));
	//		box->setPos(x, y);
	//		box->setBrush(_colorpalette->labels[1].back);
	//		text->setZValue(99);
	//		addItem(box);
	//	}
	//}

	qDebug() << "---------";
	qDebug() << x_w_min << x_w_max;
	qDebug() << y_v_min << y_v_max;
	qDebug() << sceneRect();
	qDebug() << v_m << sceneRect().y() + sceneRect().height() << val_h_to_y(v_m) << y_to_val_h(val_h_to_y(v_m));
	qDebug() << v_M << sceneRect().y() << val_h_to_y(v_M) << y_to_val_h(val_h_to_y(v_M));
	qDebug() << w_m << sceneRect().x() << val_w_to_x(w_m) << x_to_val_w(val_w_to_x(w_m));
	qDebug() << w_M << sceneRect().x() + sceneRect().width() << val_w_to_x(w_M) << x_to_val_w(val_w_to_x(w_M));
}

}
}
