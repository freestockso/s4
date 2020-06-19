#include "qt_Kviewer/s4Kinstrument_scene.h"

namespace S4 {
namespace QT {



Kinstrument_scene::Kinstrument_scene(QWidget* parent):
    QGraphicsScene(parent)
{
    _colorpalette = std::make_shared<qt_colorpalette_t>();
    drawBK();
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

}
}
