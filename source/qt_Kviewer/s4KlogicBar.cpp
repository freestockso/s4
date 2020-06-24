#include "qt_Kviewer/s4KlogicBar.h"
#include "qt_Kviewer/s4Kinstrument_scene.h"

namespace S4{
namespace QT{

void KlogicBar_t::mkGroupItems(void)
{
    if(!_scene) return;

    qreal x = _scene->val_w_to_x(_value.seq);
    qreal w = (_scene->getCtx().val_w_pxl() - _line_width) * 0.8;
	_x_min  = x - w / 2;
	_x_max  = x + w / 2;
    _y_o = _scene->val_h_to_y(_value.O);
    _y_h = _scene->val_h_to_y(_value.H);
    _y_l = _scene->val_h_to_y(_value.L);
    _y_c = _scene->val_h_to_y(_value.C);

    QPen* pen;
    QPen* pen_skin;
	QBrush* brush;
	qreal y_oc_max, y_oc_min;
    y_oc_max = std::max(_y_c, _y_o);
    y_oc_min = std::min(_y_c, _y_o);
	if(_value.C>=_value.lastC){ //rise
		pen = new QPen(_color_positive.body, _line_width, Qt::SolidLine , Qt::FlatCap, Qt::MiterJoin);
		brush = new QBrush(_color_positive.body, Qt::SolidPattern);
        pen_skin = new QPen(_color_positive.skin, _line_width, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
	}else{
		pen = new QPen(_color_negtive.body, _line_width, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
		brush = new QBrush(_color_negtive.body, Qt::SolidPattern);
        pen_skin = new QPen(_color_negtive.skin, _line_width, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    }

    //up-donw, go through body
    QGraphicsLineItem* uline = new QGraphicsLineItem(x, _y_h, x, _y_l); // x/y in scene absolute coordinate 
    uline->setPen(*pen);
    uline->setZValue(0);
    addToGroup(uline);

    if (_type == BAR_JPN){  //Rect body
        QGraphicsRectItem* body = new QGraphicsRectItem(_x_min, y_oc_min, _x_max - _x_min, y_oc_max - y_oc_min);
        pen_skin->setWidth(1);
        pen->setCosmetic(true);
        body->setPen(*pen_skin);
        body->setBrush(*brush);
        body->setZValue(1);
        addToGroup(body);
    }else{  //BAR_USA       //
        QGraphicsLineItem* lline = new QGraphicsLineItem(_x_min, _y_o, x, _y_o); // x/y in scene absolute coordinate 
        // pen->setWidth(1);
        //pen->setJoinStyle(Qt::RoundJoin);
        pen->setCapStyle(Qt::RoundCap);

        lline->setPen(*pen);
        lline->setZValue(0);
        addToGroup(lline);

        QGraphicsLineItem* rline = new QGraphicsLineItem(_x_max, _y_c, x, _y_c); // x/y in scene absolute coordinate 
        rline->setPen(*pen);
        rline->setZValue(0);
        addToGroup(rline);
    }

}
    
void KlogicBar_t::showLabel()
{
    if (isSelected() && !_selected_label) {
        _selected_label = new KlogicLabel_t(_scene);
        _selected_label->setText("test");
        _selected_label->setColor(_value.C >= _value.lastC ? 
            color_pair_t{_color_positive.body, _color_negtive.body} : 
            color_pair_t{_color_negtive.body, _color_positive.body});
        _selected_label->setLogicPos(_value.seq, _value.L);
        _scene->addItem(_selected_label);
    }
    else if (!isSelected() && _selected_label) {
        _scene->removeItem(_selected_label);
        delete _selected_label;
        _selected_label = nullptr;
    }
}


///
void KlogicBarGroup_t::mkGroupItems(void)
{
    if(!_scene) return;

    for(const auto& v : _valueList){
        KlogicBar_t* bar = new KlogicBar_t(_scene);
        bar->setColor(_color_positive, _color_negtive);
        bar->setType(_type);
        bar->setLineWidth(_line_width);
        bar->setVal(v);
        bar->mkGroupItems();
        // _scene->addItem(bar);
        addToGroup(bar);
    }
}

} // namespace QT
} // namespace S4