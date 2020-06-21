#pragma once

#include <QPen>
#include <QBrush>
#include <QGraphicsItem>
#include "qt_common/s4qt_colorpalette.h"

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
        this->addToGroup(text);
        this->addToGroup(box);
    }

    void setText(const QString& txt)
    {
        text->setText(txt);
        box->setRect(text->boundingRect());
        box->setPen(QPen(Qt::NoPen));
    }
    void setPose(qreal ax, qreal ay)
    {
    	text->setPos(ax, ay);
        box->setPos(ax, ay);
    }
    void setColor(const color_pair_t& color_pair)
    {
        text->setBrush(color_pair.front);
        box->setBrush(color_pair.back);
    }
    void setTransform(const QTransform& matrix)
    {
        text->setTransform(matrix);
        box->setTransform(matrix);
    }
    void setZValue(qreal z)
    {
        text->setZValue(z);
        box->setZValue(z-1);
    }

    QRectF boundingRect() const
    {
        return text->boundingRect();
    }

private:
    QGraphicsSimpleTextItem* text;
    QGraphicsRectItem* box;
};



    
} // namespace QT
} // namespace S4