#pragma once

#include "qt_Kviewer/s4Kinstrument_view.h"
#include "qt_Kviewer/s4Kinstrument_scene.h"

#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QTabWidget>


namespace S4{
namespace QT{
    

class Kinstrument: public QWidget
{
    Q_OBJECT
public:
    explicit Kinstrument(QWidget *parent = nullptr);

private:
    // K_view
    QTabWidget* _K_tab;
    // vol/indicator tab
    QTabWidget* _indicator_tab;
    // cyc/... tab
    QTabWidget* _cyc_tab;
    // basic tab
    QTabWidget* _basic_tab;

};


} // namespace QT
} // namespace S4
