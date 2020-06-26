#pragma once
#include "qt_common/s4qt_data_if.h"
#include <QTransform>

namespace S4{
namespace QT{

class view_event
{
public:
    enum type_t{
        on_transform_change = 0,
        on_scene_mouse_change,
        on_scene_center_change,
        on_label_mouse_change,
        on_label_center_change
    };

public:
    explicit view_event(type_t type):
        _type(type)
    {}

    virtual ~view_event(){}

    inline type_t type(void) const{
        return _type;
    }

	inline void setTimeMode(timeMode_t t) {
		_timeMode = t;
	}

	inline timeMode_t timeMode(void) const {
		return _timeMode;
	}

protected:
    type_t _type;
	timeMode_t _timeMode = timeMode_t::tUNKNOWN;
};


class view_event_transform_change : public view_event
{
public:
    view_event_transform_change(const QTransform& T, bool c):
        view_event(on_transform_change),
        _T(T),
		_combine(c)
    {}

    const QTransform& transform() const
    {
        return _T;
    }

    const bool combine() const
    {
        return _combine;
    }

protected:
    const QTransform _T;
    bool _combine;
};




}
}