
#include <QApplication>
#include <QTranslator>
#include "data/s4thread_data_if.h"
#include "common/s4logger.h"
#include "common/s4conf.h"
#include "qt_Kviewer/s4Kviewer.h"

CREATE_LOCAL_LOGGER("QT-view")

int main(int argc, char *argv[])
{
	S4::glb_conf::pInstance()->load("../json_template/glb_conf_ctx_t.json");

	QApplication app(argc, argv);

    //QTranslator translator;
    //translator.load("myI18N_zh_CN.qm");
    //app.installTranslator(&translator);

    S4::QT::s4Kviewer v;
    v.show();

    return app.exec();
}
