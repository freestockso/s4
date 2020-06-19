#pragma once

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
    QGraphicsView* _K_view;
    // vol/indicator tab
    QTabWidget* _indicator_tab;
    // cyc/... tab
    QTabWidget* _cyc_tab;
    // basic tab
    QTabWidget* _basic_tab;

};


} // namespace QT
} // namespace S4
