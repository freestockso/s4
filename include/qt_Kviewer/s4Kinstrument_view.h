#pragma once

#include "qt_common/s4qt_colorpalette.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

namespace S4 {
namespace QT {


class Kinstrument_view : public QGraphicsView
{
    Q_OBJECT
public:
    Kinstrument_view(QGraphicsScene *scene, QWidget *parent = 0);

//signals:
//    void cursorPosition(QPointF);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

protected:
	QGraphicsScene* _scene;
    std::shared_ptr<qt_colorpalette_t> _colorpalette;
};

}
}
