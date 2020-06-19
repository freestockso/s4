#include "qt_sqlite_viewer/sqlviewer.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    S4::SqlViewer w;
    w.show();

    return a.exec();
}
