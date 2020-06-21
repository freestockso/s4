#pragma once

#include "qt_common/s4qt_colorpalette.h"
#include "qt_Kviewer/s4Kinstrument_scene.h"

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
    Kinstrument_view(Kinstrument_scene*scene, QWidget *parent = 0);

//signals:
//    void cursorPosition(QPointF);

    void setLogCoor(bool log)
    {
        _isLogCoor = log;
    }

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

protected:
    Kinstrument_scene* _scene;
    std::shared_ptr<qt_colorpalette_t> _colorpalette;
    
    QPointF _scene_pos;
    QPointF _scene_lu;
    QPointF _scene_rd;

    QPointF _view_pos;

    bool _isLogCoor = true;
protected:
    qreal val_to_sceneh(qreal val);
    qreal sceneh_to_val(qreal val);


    void zoomIn();
    void zoomOut();

    QPointF getXYscale();

    QGraphicsItemGroup* _crossLine = nullptr;
    void paintCrosshair();
    QGraphicsItemGroup* _grid = nullptr;
    void paintGrid();
};

}
}
