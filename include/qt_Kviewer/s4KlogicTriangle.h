#pragma once

#include "qt_Kviewer/s4KlogicItem.h"

namespace S4{
namespace QT{
    

class KlogicTriangle_t : public KlogicItem_t
{
public:
	enum dirMode_t {
		Tri_LF = 0,
		Tri_RT,
		Tri_UP,
		Tri_DN
	};
public:
    explicit KlogicTriangle_t(Kinstrument_scene *scene):
        KlogicItem_t(scene)
    {
    }

    void setDirect(dirMode_t dir)
    {
        _dir = dir;
    }

    void setAlpha(int alpha)
    {
        _alpha = alpha;
    }

    void setValue(qreal peak_val_w, qreal peak_val_h, qreal radial_index=1.0, qreal axial_index=1.0)
    {
        _val_w = peak_val_w;
        _val_h = peak_val_h;
        _radial_index = radial_index;
        _axial_index = axial_index;
    }
    
    void setColor(const color_box_t& color_box)
    {
        _color_box = color_box;
    }

    virtual void mkGroupItems();

private:
    color_box_t _color_box;
    dirMode_t _dir = dirMode_t::Tri_UP;
    qreal _val_w;
    qreal _val_h;
    qreal _radial_index=1.0;
    qreal _axial_index=1.0;
    int _alpha = 75;
};



} // namespace QT
} // namespace S4
