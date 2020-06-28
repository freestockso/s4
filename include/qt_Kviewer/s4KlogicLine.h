#pragma once

#include "qt_Kviewer/s4KlogicItem.h"


namespace S4{
namespace QT{

//signal Bar for one day or one week and so on...
class KlogicLine_t : public KlogicItem_t
{
public:
public:
    explicit KlogicLine_t(Kinstrument_scene *scene):
        KlogicItem_t(scene)
    {
    }

    ~KlogicLine_t(){
    }

    inline void setValue(qreal val_w_0, qreal val_h_0, qreal val_w_1, qreal val_h_1)
    {
        _val_w_0 = val_w_0;
        _val_h_0 = val_h_0;
		_val_w_1 = val_w_1;
		_val_h_1 = val_h_1;
    }

    inline void setLineWidth(int width) { _line_width = width; }

    inline void setColor(const QColor& c)
    {
        _color = c;
    }

    inline void setLineStyle(Qt::PenStyle s){
        _line_style = s;
    }

    inline void setAutoExp(bool autoExp){
        _auto_expend_horizontal = autoExp;
    }

    virtual void mkGroupItems() override
    {
        qreal x0 = _scene->val_w_to_x(_val_w_0);
        qreal y0 = _scene->val_h_to_y(_val_h_0);
        qreal x1 = _scene->val_w_to_x(_val_w_1);
        qreal y1 = _scene->val_h_to_y(_val_h_1);

        if (_val_h_0 == _val_h_1 && _auto_expend_horizontal){//horizontal line
            if (x0 <= x1){
                x0 -= _scene->getCtx().val_w_pxl() / 2;
                x1 += _scene->getCtx().val_w_pxl() / 2;
            }else{
                x0 += _scene->getCtx().val_w_pxl() / 2;
                x1 -= _scene->getCtx().val_w_pxl() / 2;
            }
        }

        QGraphicsLineItem* pLine = new QGraphicsLineItem(x0, y0, x1, y1);
        if (_line_width > 0){
            QPen pen(_color, _line_width, _line_style, Qt::RoundCap, Qt::MiterJoin);
            pLine->setPen(pen);
        }else{
            QPen pen(_color, 1, _line_style, Qt::RoundCap, Qt::MiterJoin);
            pen.setCosmetic(true);
            pLine->setPen(pen);
        }
        
        addToGroup(pLine);
    }
private:
    qreal _val_w_0;
    qreal _val_h_0;
    qreal _val_w_1;
    qreal _val_h_1;

    bool _auto_expend_horizontal = true;

    QColor _color;
    int _line_width = 1;
    Qt::PenStyle _line_style = Qt::PenStyle::SolidLine;

    qreal _x_max, _x_min;   //in scene
	qreal _y_top, _y_btm;
private:

};


    
} // namespace QT
} // namespace S4