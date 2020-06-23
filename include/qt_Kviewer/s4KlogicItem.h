#pragma once

#include <QPen>
#include <QBrush>
#include <QGraphicsItem>
#include <QSet>
#include <QDebug>
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


class KlogicItemGroup_t : public QObject,public QGraphicsItemGroup
{
	Q_INTERFACES(QGraphicsItemGroup)
public:
    explicit KlogicItemGroup_t(Kinstrument_scene *scene):
        _scene(scene)
    {
    }

    virtual ~KlogicItemGroup_t(){
    }

    virtual void remove(void) {
        //int n = 0;
        //qDebug() << _items.size();
        for(QSet<QGraphicsItem*>::iterator i = _items.begin(); i != _items.end(); ++i){
            if(*i)
                _scene->removeItem(*i);
        //    qDebug() << "test" << n++;
        }
        _items.clear();
    }
    
    inline virtual void setLogicPos(qreal w, qreal h)
    {
        qreal x = _scene->val_w_to_x(w);
        qreal y = _scene->val_h_to_y(h);
        QGraphicsItemGroup::setPos(x, y);
    }
    
    virtual void mkGroupItems() = 0;

    virtual void addToGroup(QGraphicsItem *item)
    {
        _scene->addItem(item);
        _items.insert(item);
    }

    virtual void removeFromGroup(QGraphicsItem *item)
    {
        _scene->removeItem(item);
        for(QSet<QGraphicsItem*>::iterator i = _items.begin(); i != _items.end(); ++i){
            if (*i == item){
                _items.erase(i);
                return;
            }
        }
    }

    virtual void setZValue(qreal z){
        for(QSet<QGraphicsItem*>::iterator i = _items.begin(); i != _items.end(); ++i){
            (*i)->setZValue(z);
        }
    }

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
    QSet<QGraphicsItem*> _items;
};

}//QT
}//S4
