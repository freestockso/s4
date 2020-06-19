#pragma once

#include "qt_common/s4qt_colorpalette.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

namespace S4 {
namespace QT {


class Kinstrument_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Kinstrument_scene(QWidget* parent = 0);

//signals:
//    void cursorPosition(QPointF);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    
protected:
    void drawBK();

    void drawTest();
protected:
    QPointF _pos;

    std::shared_ptr<qt_colorpalette_t> _colorpalette;
};

}
}
