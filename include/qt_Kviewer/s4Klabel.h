#pragma once

#include <QPen>
#include <QBrush>
#include <QGraphicsItemGroup>
#include "qt_common/s4qt_colorpalette.h"
#include "qt_Kviewer/s4KlogicItem.h"

namespace S4{
namespace QT{
    
class Klabel_t : public QObject,public QGraphicsItemGroup
{
	Q_INTERFACES(QGraphicsItemGroup)
public:
    explicit Klabel_t()
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
    }

    void setText(const QString& txt)
    {
        _text = txt;
    }
    
    void setColor(const color_pair_t& color_pair)
    {
        _color = color_pair;
    }

    void setAlpha(int alpha) {
        _alpha = alpha;
    }

    QRectF boundingRect() const
    {
        return text->boundingRect();
    }

	virtual void mkGroupItems() {
        _color.back.setAlpha(_alpha);
		text = new QGraphicsSimpleTextItem;
		box = new QGraphicsRectItem;
		text->setPos(0, 0);
		box->setPos(0, 0);
		text->setZValue(1);
		box->setZValue(0);
		text->setText(_text);
		box->setRect(text->boundingRect());
		box->setPen(QPen(Qt::NoPen));
		text->setBrush(_color.front);
		box->setBrush(_color.back);
		addToGroup(text);
		addToGroup(box);
    };

private:
    QGraphicsSimpleTextItem* text;
    QGraphicsRectItem* box;
    QString _text;
    color_pair_t _color;
    int _alpha = 255;
};


    
} // namespace QT
} // namespace S4
