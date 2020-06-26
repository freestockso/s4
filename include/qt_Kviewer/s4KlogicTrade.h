#pragma once

#include "qt_Kviewer/s4KlogicItem.h"

namespace S4{
namespace QT{
    
	
class KlogicTrade_t : public KlogicItemGroup_t
{
public:
    explicit KlogicTrade_t(Kinstrument_scene *scene):
        KlogicItemGroup_t(scene)
    {
    }

    ~KlogicTrade_t(){
    }

    inline void setLineWidth(int width) { _line_width = width; }

    void setVal(const QList<logicBarData_t>& pointList)
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
