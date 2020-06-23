
#include "qt_Kviewer/s4KlogicTriangle.h"

namespace S4{
namespace QT{
    

void KlogicTriangle_t::mkGroupItems()
{
    if (!_scene)
        return;

    qreal peak_x = _scene->val_w_to_x(_val_w);
    qreal peak_y = _scene->val_h_to_y(_val_h);
    qreal radial_len = _scene->getCtx().val_w_pxl();
    qreal axial_len = radial_len / 2;
    radial_len *= _radial_index;
    axial_len *= _axial_index;

	qreal x1 = peak_x, y1 = peak_y, x2 = peak_x, y2 = peak_y;
    
	switch (_dir)
	{
	case KlogicTriangle_t::Tri_LF: // <--|
		x1 = peak_x + radial_len;
		y1 = peak_y - axial_len / 2;
		x2 = x1;
		y2 = y1 + axial_len;
		break;
	case KlogicTriangle_t::Tri_RT:  // |-->
		x1 = peak_x - radial_len;
		y1 = peak_y - axial_len / 2;
		x2 = x1;
		y2 = y1 + axial_len;
		break;
	case KlogicTriangle_t::Tri_UP:  // ^
		x1 = peak_x - axial_len / 2;
		y1 = peak_y + radial_len;
		x2 = x1 + axial_len;
		y2 = y1;
		break;
	case KlogicTriangle_t::Tri_DN:  // v
		x1 = peak_x - axial_len / 2;
		y1 = peak_y - radial_len;
		x2 = x1 + axial_len;
		y2 = y1;
		break;
	default:
		break;
	}

    QGraphicsPolygonItem* triangle = new QGraphicsPolygonItem();
    QPolygonF trianglePoints;
    trianglePoints.append(QPointF(peak_x, peak_y));
    trianglePoints.append(QPointF(x1, y1));
    trianglePoints.append(QPointF(x2, y2));
    triangle->setPolygon(trianglePoints);

    QPen pen(_color_box.skin, 1, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
	_color_box.body.setAlpha(_alpha);
    QBrush brush(_color_box.body, Qt::SolidPattern);
    
    triangle->setPen(pen);
    triangle->setBrush(brush);
    addToGroup(triangle);
}


} // namespace QT
} // namespace S4
