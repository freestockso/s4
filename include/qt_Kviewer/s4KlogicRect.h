#pragma once

#include "qt_Kviewer/s4KlogicItem.h"


namespace S4{
namespace QT{

//grow in vertical
struct logicRectData_h_t
{
    qreal seq;      //logic-value-w: date-sequence in scene
    qreal val_top;  //logic-value-h: volumn in scene, in logic v_top > v_btm, in scene y_top < y_btm
    qreal val_btm;  //
    bool positive;
};

//signal Bar for one day or one week and so on...
class KlogicRect_h_t : public KlogicItem_t
{
public:
public:
    explicit KlogicRect_h_t(Kinstrument_scene *scene):
        KlogicItem_t(scene)
    {
    }

    ~KlogicRect_h_t(){
    }

    void setVal(const logicRectData_h_t& pointList)
    {
        _value = pointList;
    }

    void setColor(const color_box_t& color_positive, const color_box_t& color_negtive)
    {
        _color_positive = color_positive;
        _color_negtive = color_negtive;
    }

    virtual void mkGroupItems();
private:
    logicRectData_h_t _value;
    color_box_t _color_positive;
    color_box_t _color_negtive;

    qreal _x_max, _x_min;   //in scene
	qreal _y_top, _y_btm;
private:

};

class KlogicRectGroup_h_t : public KlogicItemGroup_t
{
public:
    explicit KlogicRectGroup_h_t(Kinstrument_scene *scene):
        KlogicItemGroup_t(scene)
    {
    }

    ~KlogicRectGroup_h_t(){
    }

    void setVal(const QList<logicRectData_h_t>& pointList)
    {
        _valueList = pointList;
    }

    void setColor(const color_box_t& color_positive, const color_box_t& color_negtive)
    {
        _color_positive = color_positive;
        _color_negtive = color_negtive;
    }

    virtual void mkGroupItems();
private:
    QList<logicRectData_h_t> _valueList;
    color_box_t _color_positive;
    color_box_t _color_negtive;
    int _line_width = 1;
};

//grow in horizontal
struct logicRectData_w_t
{
    qreal val_h;   //logic-value-h: price
    qreal val_h_scope;
    qreal val_lf;  //logic-value-w
    qreal val_rt;  //
    bool positive;
};

//signal Bar for one day or one week and so on...
class KlogicRect_w_t : public KlogicItem_t
{
public:
public:
    explicit KlogicRect_w_t(Kinstrument_scene *scene):
        KlogicItem_t(scene)
    {
    }

    ~KlogicRect_w_t(){
    }

    void setVal(const logicRectData_w_t& pointList)
    {
        _value = pointList;
    }

    void setColor(const color_box_t& color_positive, const color_box_t& color_negtive)
    {
        _color_positive = color_positive;
        _color_negtive = color_negtive;
    }

    virtual void mkGroupItems();
private:
    logicRectData_w_t _value;
    color_box_t _color_positive;
    color_box_t _color_negtive;

    qreal _x_max, _x_min;   //in scene
	qreal _y_top, _y_btm;
private:

};

class KlogicRectGroup_w_t : public KlogicItemGroup_t
{
public:
    explicit KlogicRectGroup_w_t(Kinstrument_scene *scene):
        KlogicItemGroup_t(scene)
    {
    }

    ~KlogicRectGroup_w_t(){
    }

    void setVal(const QList<logicRectData_w_t>& pointList)
    {
        _valueList = pointList;
    }

    void setColor(const color_box_t& color_positive, const color_box_t& color_negtive)
    {
        _color_positive = color_positive;
        _color_negtive = color_negtive;
    }

    virtual void mkGroupItems();
private:
    QList<logicRectData_w_t> _valueList;
    color_box_t _color_positive;
    color_box_t _color_negtive;
    int _line_width = 1;
};

    
} // namespace QT
} // namespace S4