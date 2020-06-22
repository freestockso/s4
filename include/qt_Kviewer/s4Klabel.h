#pragma once

#include <QPen>
#include <QBrush>
#include <QGraphicsItem>
#include "qt_common/s4qt_colorpalette.h"
#include "qt_Kviewer/s4KlogicItem.h"

namespace S4{
namespace QT{
    
class Klabel_t : public QObject,public QGraphicsItemGroup
{
	Q_INTERFACES(QGraphicsItemGroup)
public:
    explicit Klabel_t(QObject *parent = 0)
    {
        text = new QGraphicsSimpleTextItem;
        box = new QGraphicsRectItem;
        text->setPos(0, 0);
        box->setPos(0, 0);
        text->setZValue(1);
        box->setZValue(0);
        this->addToGroup(text);
        this->addToGroup(box);
    }

    void setText(const QString& txt)
    {
        text->setText(txt);
        box->setRect(text->boundingRect());
        box->setPen(QPen(Qt::NoPen));
    }

    void setColor(const color_pair_t& color_pair)
    {
        text->setBrush(color_pair.front);
        box->setBrush(color_pair.back);
    }

    inline QRectF boundingRect() const
    {
        return text->boundingRect();
    }

private:
    QGraphicsSimpleTextItem* text;
    QGraphicsRectItem* box;
};


class KlogicLabel_t : public KlogicItem_t
{
public:
    explicit KlogicLabel_t(Kinstrument_scene *scene):
        KlogicItem_t(scene)
    {
        text = new QGraphicsSimpleTextItem;
        box = new QGraphicsRectItem;
        text->setPos(0, 0);
        box->setPos(0, 0);
        text->setZValue(1);
        box->setZValue(0);
        addToGroup(text);
        addToGroup(box);
    }

    void setText(const QString& txt)
    {
        text->setText(txt);
        box->setRect(text->boundingRect());
        box->setPen(QPen(Qt::NoPen));
    }
    
    void setColor(const color_pair_t& color_pair)
    {
        text->setBrush(color_pair.front);
        box->setBrush(color_pair.back);
    }

    QRectF boundingRect() const
    {
        return text->boundingRect();
    }

    virtual void mkGroupItems() {};

private:
    QGraphicsSimpleTextItem* text;
    QGraphicsRectItem* box;
};


    
} // namespace QT
} // namespace S4