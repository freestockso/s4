#include "qt_Kviewer/s4Kinstument.h"
#include <QGridLayout>

namespace S4{
namespace QT{
    
Kinstrument_wid::Kinstrument_wid(QWidget *parent = nullptr) :
    QWidget(parent)
{
    _K_view = new QGraphicsView(this);
    _indicator_tab = new QTabWidget(this);
    _cyc_tab = new QTabWidget(this);
    _basic_tab = new QTabWidget(this);
    
	//网格分割
	QGridLayout *pLayout = new QGridLayout();
	pLayout->addWidget(_K_view, 0, 0, 3, 6);	
	pLayout->addWidget(_indicator_tab, 3, 0, 1, 6);
	pLayout->addWidget(_cyc_tab, 0, 6, 3, 1);
	pLayout->addWidget(_basic_tab, 3, 6, 1, 1);

	pLayout->setRowStretch(0, 4);			//
	pLayout->setRowStretch(3, 1);			//
	pLayout->setColumnStretch(0, 4);			//0列的拉伸系数
	pLayout->setColumnStretch(6, 2);			//6列的拉伸系数 (0=不拉伸)

	setLayout(pLayout);
}

} // namespace QT
} // namespace S4
