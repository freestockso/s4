#include "qt_Kviewer/s4Kinstrument_view.h"

namespace S4 {
namespace QT {



Kinstrument_view::Kinstrument_view(QGraphicsScene *scene, QWidget *parent):
    QGraphicsView(scene, parent),
	_scene(scene)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    _colorpalette = std::make_shared<qt_colorpalette_t>();

}

//Kinstrument_view::void cursorPosition(QPointF);


void Kinstrument_view::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}

void Kinstrument_view::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}


}
}
