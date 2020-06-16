#include "db_sqlite_viewer/sqlviewer.h"
#include "ui_sqlviewer.h"

SqlViewer::SqlViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SqlViewer)
{
    ui->setupUi(this);

    connect(ui->actionOpen,&QAction::triggered,this,&SqlViewer::connectDbDialog);
    connect(ui->listView,&QListView::clicked,this,&SqlViewer::openTableTab);
//    Subclassing is needed for mouse events
//    connect(ui->tabWidget,&QTabWidget::mousePressEvent,this,&tabClickHandler);
    connect(ui->tabWidget,&QTabWidget::tabCloseRequested,this,&SqlViewer::tabCloseRequestHandler);
}

SqlViewer::~SqlViewer()
{
    delete dbHandler;
    delete ui;
}


void SqlViewer::openTableTab(const QModelIndex &index){
    const QString tabName = index.data(Qt::DisplayRole).toString();
    if(tabAlreadyExists(tabName)){
        QWidget *tab = tableMap.find(tabName).value();
        int i = ui->tabWidget->indexOf(tab);
        ui->tabWidget->setCurrentIndex(i);
    }
    else{
        QTableView* tv = new QTableView(this);
        tableMap.insert(tabName,tv);
        QSqlQueryModel *model = dbHandler->getTableData(tabName);
        tv->setModel(model);


        int i = ui->tabWidget->addTab(tv,tabName);
        ui->tabWidget->setCurrentIndex(i);
    }
}

void SqlViewer::connectDbDialog()
{
    connectionDialog = new DbConnectDialog(this);

    connect(connectionDialog,&QDialog::accepted,this,&SqlViewer::onConnectionDialogAccepted);
    connect(connectionDialog,&QDialog::rejected,this,&SqlViewer::onConnectionDialogRejected);

    connectionDialog->show();
}

void SqlViewer::onConnectionDialogAccepted()
{
    if(dbHandler){
        delete dbHandler;
    }
    this->dbHandler = connectionDialog->getDBHandler();

    for (int i = ui->tabWidget->count() - 1; i >= 0; --i) {
       tabCloseRequestHandler(i);
    }

    QAbstractListModel *model = new TableList(dbHandler->getTables());
    ui->listView->setFlow(QListView::Flow::TopToBottom);
    ui->listView->setModel(model);

    delete connectionDialog;
}

void SqlViewer::onConnectionDialogRejected()
{
    delete connectionDialog;
}

bool SqlViewer::tabAlreadyExists(const QString &tabName) const
{
    if(tableMap.size() == 0) return false;

    auto it = tableMap.find(tabName);

    return it != tableMap.end();
}

void SqlViewer::tabCloseRequestHandler(int index)
{
    const QString tabName = ui->tabWidget->tabText(index);
    ui->tabWidget->removeTab(index);

    auto it = tableMap.find(tabName);
    if(it != tableMap.end()){
        delete it.value();
        tableMap.remove(tabName);
    }
}
