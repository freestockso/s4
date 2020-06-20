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

    struct ctx_t {
        qreal h_min;    // h_min is at bottum, but y=0 is at top
        qreal h_max;
        qreal w_min;    // w_min at x=0
        qreal w_max;
    };

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
