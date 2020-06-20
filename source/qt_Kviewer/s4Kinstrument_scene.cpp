#include "qt_Kviewer/s4Kinstrument_scene.h"
#include <QGraphicsLineItem>

namespace S4 {
namespace QT {



Kinstrument_scene::Kinstrument_scene(QWidget* parent):
    QGraphicsScene(parent)
{
    _colorpalette = std::make_shared<qt_colorpalette_t>();
    drawBK();
	drawTest();
}

//Kinstrument_scene::void cursorPosition(QPointF);


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
	qreal x_max = 1000;// width();
	qreal y_max = 1000;// height();
	setSceneRect(0, 0, x_max - 1, y_max - 1);

	QPen pen = QPen(_colorpalette->positive_boxes[0].body, 1.0/*this param Sets the pen width to the given width in pixels with integer precision.*/);

	//V
	for (qreal x = 0; x < x_max; x += 100) {
		QGraphicsLineItem* line = new QGraphicsLineItem(x, 0, x, y_max - 1);
		line->setPen(pen);
		line->setZValue(100);
		addItem(line);
	}

	pen = QPen(_colorpalette->negtive_boxes[0].body, 1.0/*this param Sets the pen width to the given width in pixels with integer precision.*/);
	//H
	for (qreal y = 0; y < y_max; y += 100) {
		QGraphicsLineItem* line = new QGraphicsLineItem(0, y, x_max - 1, y);
		line->setPen(pen);
		line->setZValue(100);
		addItem(line);
	}
	for (qreal x = 0; x < x_max; x += 100) {
		for (qreal y = 0; y < y_max; y += 100) {

			QString txt;
			txt.sprintf("%0.0f,%0.0f", x, y);
			QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem;
			text->setText(txt);
			text->setPos(x, y);
			text->setBrush(_colorpalette->labels[1].front);
			text->setZValue(100);
			addItem(text);

			QGraphicsRectItem* box = new QGraphicsRectItem;
			box->setRect(text->boundingRect());
			box->setPen(QPen(Qt::NoPen));
			box->setPos(x, y);
			box->setBrush(_colorpalette->labels[1].back);
			text->setZValue(99);
			addItem(box);
		}
	}

	setSceneRect(-x_max, -y_max, x_max*3 - 1, y_max*3 - 1);

}

}
}
