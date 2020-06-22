#include "qt_Kviewer/s4KlogicRect.h"
#include "qt_Kviewer/s4Kinstrument_scene.h"


namespace S4{
namespace QT{

//grow in vertical
void KlogicRect_h_t::mkGroupItems(void)
{
    if(!_scene) return;

    qreal x = _scene->val_w_to_x(_value.seq);
	_x_min  = x - _scene->getCtx().val_w_pxl() * 0.8/2;
	_x_max  = x + _scene->getCtx().val_w_pxl() * 0.8/2;
    _y_top = _scene->val_h_to_y(_value.val_top);
    _y_btm = _scene->val_h_to_y(_value.val_btm);

	QBrush* brush;
	if(_value.positive){ //rise
		brush = new QBrush(_color_positive.body, Qt::SolidPattern);
	}else{
		brush = new QBrush(_color_negtive.body, Qt::SolidPattern);
	}

    QGraphicsRectItem* body = new QGraphicsRectItem(_x_min, _y_top, _x_max - _x_min, _y_btm - _y_top);
    body->setPen(QPen(Qt::NoPen));
    body->setBrush(*brush);
    body->setZValue(1);
    addToGroup(body);
}
    

void KlogicRectGroup_h_t::mkGroupItems(void)
{
    if(!_scene) return;

    for(const auto& v : _valueList){
        KlogicRect_h_t* rect = new KlogicRect_h_t(_scene);
        rect->setColor(_color_positive, _color_negtive);
        rect->setVal(v);
        rect->mkGroupItems();
        addToGroup(rect);
    }
}

//grow in horizontal
void KlogicRect_w_t::mkGroupItems(void)
{
    if(!_scene) return;

    //qreal y = _scene->val_h_to_y(_value.val_h);
    qreal y_min = _scene->val_h_to_y(_value.val_h + _value.val_h_scope / 2);
    qreal y_max = _scene->val_h_to_y(_value.val_h - _value.val_h_scope / 2);

	_x_min  = _scene->val_w_to_x(_value.val_lf);
	_x_max  = _scene->val_w_to_x(_value.val_rt);

	QBrush* brush;
	if(_value.positive){ //rise
		brush = new QBrush(_color_positive.body, Qt::SolidPattern);
	}else{
		brush = new QBrush(_color_negtive.body, Qt::SolidPattern);
	}

    QGraphicsRectItem* body = new QGraphicsRectItem(_x_min, y_min, _x_max - _x_min, y_max - y_min);
    body->setPen(QPen(Qt::NoPen));
    body->setBrush(*brush);
    body->setZValue(1);
    addToGroup(body);
}
    

void KlogicRectGroup_w_t::mkGroupItems(void)
{
    if(!_scene) return;

    for(const auto& v : _valueList){
        KlogicRect_w_t* rect = new KlogicRect_w_t(_scene);
        rect->setColor(_color_positive, _color_negtive);
        rect->setVal(v);
        rect->mkGroupItems();
        addToGroup(rect);
    }
}

} // namespace QT
} // namespace S4