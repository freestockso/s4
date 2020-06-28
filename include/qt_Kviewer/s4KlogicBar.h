#pragma once

#include "qt_Kviewer/s4KlogicItem.h"
#include "qt_Kviewer/s4Klabel.h"


namespace S4{
namespace QT{

struct logicBarData_t
{
    qreal seq;    //logic-value-w: date-sequence in scene
    qreal O;        //logic-value-h: price in scene
    qreal C;
    qreal H;
    qreal L;
    qreal lastC;
};

//signal Bar for one day or one week and so on...
class KlogicBar_t : public KlogicItem_t
{
public:
    enum barType_t{
        BAR_JPN = 0,
        BAR_USA,
    };

public:
    explicit KlogicBar_t(Kinstrument_scene *scene):
        KlogicItem_t(scene)
    {
        setFlag(GraphicsItemFlag::ItemIsSelectable);
    }

    ~KlogicBar_t(){
    }

    inline void setType(barType_t t){
        _type = t;
    }

    inline void setLineWidth(int width) { _line_width = width; }

    void setValue(const logicBarData_t& pointList)
    {
        _value = pointList;
    }

    void setColor(const color_box_t& color_positive, const color_box_t& color_negtive)
    {
        _color_positive = color_positive;
        _color_negtive = color_negtive;
    }

    inline void setAlpha(int alpha)
    {
        _alpha = alpha;
    }

    virtual void mkGroupItems();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE
    {
        if (event->button() == Qt::LeftButton) {
            if (isSelected()) {
                setSelected(false);
            }
            else {
                setSelected(true);
            }
            showLabel();
        }
    }
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE
    {
        if (event->button() == Qt::LeftButton) {
        }
    }

    void showLabel();

private:
    barType_t _type = BAR_USA;

    logicBarData_t _value;
    color_box_t _color_positive;
    color_box_t _color_negtive;
    int _line_width = 1;
    int _alpha = 255;

    qreal _x_max, _x_min;   //in scene
	qreal _y_o, _y_h, _y_l, _y_c;

    KlogicLabel_t* _selected_label = nullptr;
private:

};

//not a itemGroup, but list of item, use for add/del items quickly.
class KlogicBarGroup_t : public KlogicItemGroup_t
{
public:
    explicit KlogicBarGroup_t(Kinstrument_scene *scene):
        KlogicItemGroup_t(scene)
    {
    }

    ~KlogicBarGroup_t(){
    }

    inline void setType(KlogicBar_t::barType_t t){
        _type = t;
    }

    inline void setLineWidth(int width) { _line_width = width; }

    void setValue(const QList<logicBarData_t>& pointList)
    {
        _valueList = pointList;
    }

    void setColor(const color_box_t& color_positive, const color_box_t& color_negtive)
    {
        _color_positive = color_positive;
        _color_negtive = color_negtive;
    }

    virtual void mkGroupItems() override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE
    {
        if (event->button() == Qt::LeftButton) {
            setSelected(true);
        }
        QGraphicsItemGroup::mousePressEvent(event);
    }
private:
    KlogicBar_t::barType_t _type = KlogicBar_t::barType_t::BAR_USA;

    QList<logicBarData_t> _valueList;
    color_box_t _color_positive;
    color_box_t _color_negtive;
    int _line_width = 1;
};


    
} // namespace QT
} // namespace S4