#pragma once

#include "qt_common/s4qt_colorpalette.h"
#include "qt_Kviewer/s4Kinstrument_scene.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsItemGroup>

namespace S4 {
namespace QT {


class Kinstrument_view : public QGraphicsView
{
    Q_OBJECT
public:
    Kinstrument_view(Kinstrument_scene*scene, QWidget *parent = 0);

//signals:
//    void cursorPosition(QPointF);

    inline void setLogCoor(bool log)
    {
        _isLogCoor = log;
    }

    void setTransform(const QTransform& matrix, bool combine = false);
    void resetTransform();

    struct ctx_t
    {
        qreal sc_val_h_min = -1;    // h_min is at bottum, but y=0 is at top
        qreal sc_val_h_max = -1;
        qreal sc_val_w_min = -1;    // w_min at x=0
        qreal sc_val_w_max = -1;
    };

    void setCtx(const ctx_t& ctx)
    {
        _ctx = ctx;
        paintGridLines();
    }

    inline void setGridGap(qreal gap_h, qreal gap_w) {
        _grid_h_gap = gap_h;
        _grid_w_gap = gap_w;
    }

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);


protected:
    Kinstrument_scene* _scene;
    std::shared_ptr<qt_colorpalette_t> _colorpalette;
    
    QGraphicsItem* _mouse_item;

    QPointF _scene_mouse;
    QPointF _scene_lu;
    QPointF _scene_rd;

    QPointF _view_pos;

    QTransform _antiT;
    QPointF _XYantiScale;

    bool _isLogCoor = true;
    qreal _grid_h_gap = 0.2;  //10%
    qreal _grid_w_gap = 20;
    ctx_t _ctx;
protected:
    qreal val_to_sceneh(qreal val);
    qreal sceneh_to_val(qreal val);

    void setCtx_test();

    void rebuildGroup(QGraphicsItemGroup*& pGroup) {
        if (pGroup) {
            _scene->removeItem(pGroup);				//从scene删掉元素（以及group），但没有释放内存
            delete pGroup;							//好像解决了内存泄露
        }
        pGroup = _scene->createItemGroup(QList<QGraphicsItem*>{});
    }

    void zoomIn();
    void zoomOut();

    void grabTransInfo();
    QPointF getXYscale();

    QGraphicsItemGroup* _crossLine = nullptr;
    void paintCrosshair();
    QGraphicsItemGroup* _gridLines = nullptr;
    void paintGridLines();
    QGraphicsItemGroup* _gridLabels = nullptr;
    void paintGridLabels();

    //paint map from view-position to scen-position
    void paintLabel(QGraphicsItemGroup*& pGroup, const QPointF& view_pos, const QString& txt, const color_pair_t& color_pair, int zV,
        bool onLeft = true, int shift = 20, bool auto_fit = true);

};

}
}
