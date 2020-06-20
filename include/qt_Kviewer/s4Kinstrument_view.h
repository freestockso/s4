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

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

protected:
	QGraphicsScene* _scene;
    std::shared_ptr<qt_colorpalette_t> _colorpalette;
    
    QPointF _scene_pos;
    QPointF _view_pos;

protected:
    void zoomIn();
    void zoomOut();

    QGraphicsItemGroup* _crossLine = nullptr;
    void paintCrosshair();
};

}
}
