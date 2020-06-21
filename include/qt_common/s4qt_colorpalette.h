#pragma once

#include <QColor>
#include <vector>

namespace S4{

//psitive color box index    
#define S4_K_RISE_CN 0
#define S4_K_OPEN_CN 1


//negtive color box index    
#define S4_K_FALL_CN 0
#define S4_K_CLOSE_CN 1



struct color_pair_t
{
    QColor back;
    QColor front;
};

struct color_box_t
{
    QColor body;
    QColor skin;
};

class qt_colorpalette_t
{
public:
    QColor background = QColor("#FFFFE0");
    QColor crosshair = Qt::red;
    color_pair_t grid = { QColor("#FF80FF"), QColor("#000000") };   //line, text
    std::vector<color_box_t> positive_boxes = {
        {QColor("#FF0020"), QColor("#FF0030")},
        {QColor("#FF8F80"), QColor("#FF8F80")}
    };
    std::vector<color_box_t> negtive_boxes = {
        {QColor("#2000FF"), QColor("#2020FF")},
        {QColor("#8080FF"), QColor("#8080FF")}
    };
    std::vector<QColor> front_crv = {
        QColor("#4080AF"),
        QColor("#FF80FF"),
        QColor("#80c0FF")
    };
    std::vector<color_pair_t> labels = {
        {Qt::darkBlue, Qt::white},
        {Qt::darkGray, Qt::red},
        {Qt::darkGreen, Qt::white},
    };
};



} // namespace S4
