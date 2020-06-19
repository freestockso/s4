#include "qt_sqlite_viewer/ddwidget.h"
#include "ui_ddwidget.h"

DDwidget::DDwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DDwidget)
{
    ui->setupUi(this);
}

DDwidget::~DDwidget()
{
    delete ui;
}


void DDwidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain")){
        qDebug() << "dragEnterEvent";
        event->acceptProposedAction();
    }
}

void DDwidget::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        QStringList pathList;
        QList<QUrl> urlList = mimeData->urls();

        QString dbPath = urlList.first().toLocalFile();

        if(Utils::fileCanBeOpened(dbPath)){
            emit filePathRecived(dbPath);
        }
    }
}

void DDwidget::mousePressEvent(QMouseEvent *)
{
    qDebug() << "mousePressEvent";
    QString dbPath = QFileDialog::getOpenFileName(nullptr,tr("Open file"), "/home", tr("Any files (*)"));


    if(Utils::fileCanBeOpened(dbPath)){
        ui->label->setText(dbPath);
        emit filePathRecived(dbPath);
    }
}

