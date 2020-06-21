#pragma once

#include "qt_common/s4qt_colorpalette.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

namespace S4 {
namespace QT {


class Kinstrument_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Kinstrument_scene(QWidget* parent = 0);

    class ctx_t {
    public:
        ctx_t(){}
        ctx_t(
            qreal val_h_min,
            qreal val_h_max,
            qreal val_w_min,
            qreal val_w_max,
            qreal val_h_10percent_pxl = 20,
            qreal val_w_pxl = 16
        ) :
            _val_h_min(val_h_min),
            _val_h_max(val_h_max),
            _val_w_min(val_w_min),
            _val_w_max(val_w_max),
            _val_h_10percent_pxl(val_h_10percent_pxl),
            _val_w_pxl(val_w_pxl)
        {
        }

        ctx_t(const ctx_t& i):
            _val_h_min(i.val_h_min()),
            _val_h_max(i.val_h_max()),
            _val_w_min(i.val_w_min()),
            _val_w_max(i.val_w_max()),
            _val_h_10percent_pxl(i.val_h_10percent_pxl()),
            _val_w_pxl(i.val_w_pxl())
        {}

        qreal val_h_min() const { return _val_h_min; }    // h_min is at bottum, but y=0 is at top
        qreal val_h_max() const { return _val_h_max; }
        qreal val_w_min() const { return _val_w_min; }    // w_min at x=0
        qreal val_w_max() const { return _val_w_max; }
        void set_val_h_min(qreal v) { _val_h_min = v; }    // h_min is at bottum, but y=0 is at top
        void set_val_h_max(qreal v) { _val_h_max = v; }
        void set_val_w_min(qreal v) { _val_w_min = v; }    // w_min at x=0
        void set_val_w_max(qreal v) { _val_w_max = v; }

        qreal val_h_10percent_pxl() const { return _val_h_10percent_pxl; }    //
        qreal val_w_pxl() const { return _val_w_pxl; }
        
    private:
        qreal _val_h_min = -1;    // h_min is at bottum, but y=0 is at top
        qreal _val_h_max = -1;
        qreal _val_w_min = -1;    // w_min at x=0
        qreal _val_w_max = -1;

        qreal _val_h_10percent_pxl = 20; //10% of (val_h_max - val_h_min) map to pixel
        qreal _val_w_pxl = 16;           //1 of val_w  map to pixel
    };

    void setCtx(ctx_t& ctx) {
        _ctx = ctx;
        initSceneCanvas();
    }

    const ctx_t& getCtx(void) const {
        return _ctx;
    }

    void setLogCoor(bool log)
    {
        _isLogCoor = log;
    }

    //h & w is logic value, as price & date_seq, origin at left-bottom
    //y & x is in scene-coordinate, origin at left-top
    virtual qreal val_h_to_y(qreal h) const;
    virtual qreal val_w_to_x(qreal w) const;
    virtual qreal y_to_val_h(qreal y) const;
    virtual qreal x_to_val_w(qreal x) const;

    //for label-mark
    virtual QString y_to_val_label(qreal y) const;
    virtual QString x_to_val_label(qreal x) const;
//signals:
//    void cursorPosition(QPointF);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    
protected:
    void initSceneCanvas();

    void drawBK();

    void drawTest();
protected:
    QPointF _pos;
    ctx_t _ctx;
    bool _isLogCoor = false;
    qreal _h_val_pxl = 1;
    qreal _h_val_pxl_base = 1;
    qreal _h_log_pxl = 1;
    qreal _h_log_max = 1;
    qreal _h_log_min = 1;
    qreal _w_val_pxl = 1;

    std::shared_ptr<qt_colorpalette_t> _colorpalette;
};

}
}
