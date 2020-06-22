#pragma once

#include <QPen>
#include <QBrush>
#include <QGraphicsItem>
#include "qt_common/s4qt_colorpalette.h"
#include "qt_Kviewer/s4Kinstrument_scene.h"

namespace S4{
namespace QT{

class Kinstrument_scene;

class KlogicItem_t : public QObject,public QGraphicsItemGroup
{
	Q_INTERFACES(QGraphicsItemGroup)
public:
    explicit KlogicItem_t(Kinstrument_scene *scene):
        _scene(scene)
    {
    }

    virtual ~KlogicItem_t(){
    }
    
    inline virtual void setLogicPos(qreal w, qreal h)
    {
        qreal x = _scene->val_w_to_x(w);
        qreal y = _scene->val_h_to_y(h);
        QGraphicsItemGroup::setPos(x, y);
    }
    
    virtual void mkGroupItems() = 0;

    // void setScene(Kinstrument_scene *scene){
    //     _scene = scene;
    // }
protected:
    // avoid set pos by scene-coordinate directly
    inline void setX(qreal x) { QGraphicsItemGroup::setX(x); };
    inline void setY(qreal y) { QGraphicsItemGroup::setY(y); };
    inline void setPos(const QPointF &pos) { QGraphicsItemGroup::setPos(pos); };
    inline void setPos(qreal x, qreal y) { QGraphicsItemGroup::setPos(x, y); };
    inline void moveBy(qreal dx, qreal dy) { setPos(pos().x() + dx, pos().y() + dy); }
    
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE
    {
        QGraphicsItemGroup::mousePressEvent(event);
    }
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE
    {
        QGraphicsItemGroup::mouseReleaseEvent(event);
    }
protected:
    Kinstrument_scene *_scene;
};

}//QT
}//S4
