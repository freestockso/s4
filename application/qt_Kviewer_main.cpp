
#include "data/s4thread_data_if.h"
#include "common/s4logger.h"
#include "common/s4conf.h"
#include "qt_Kviewer/s4Kviewer.h"

#include <QApplication>
#include <QTranslator>
#include <QStyle>

CREATE_LOCAL_LOGGER("QT-view")

int main(int argc, char *argv[])
{
	S4::glb_conf::pInstance()->load("../json_template/glb_conf_ctx_t.json");//for debug

	QApplication app(argc, argv);
    LCL_INFO("ScrollBar w={:}", app.style()->pixelMetric(QStyle::PM_ScrollBarExtent));

    //QTranslator translator;
    //translator.load("myI18N_zh_CN.qm");
    //app.installTranslator(&translator);

    S4::QT::s4Kviewer v;
    v.show();
    

    return app.exec();
}
