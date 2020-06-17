#include "db_sqlite_viewer/sqlviewer.h"
#include "ui_sqlviewer.h"
#include "common/s4conf.h"
#include <QMessageBox>
#include <QStyleFactory>
#include <QSplitter>

#include "history/s4_history_data.h"

namespace S4{

#define HISTORY_ORDER_TREE_ROOT "history-orders"

SqlViewer::SqlViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SqlViewer)
{
    ui->setupUi(this);

    connect(ui->actionOpen,&QAction::triggered,this,&SqlViewer::onOpen);
    connect(ui->dbTree,&QTreeView::doubleClicked,this,&SqlViewer::openTableTab);
//    Subclassing is needed for mouse events
//    connect(ui->tabWidget,&QTabWidget::mousePressEvent,this,&tabClickHandler);
    connect(ui->tabWidget,&QTabWidget::tabCloseRequested,this,&SqlViewer::tabCloseRequestHandler);
    ui->statusbar->showMessage("Use \"Ctrl + O\" to open S4 configure json file.");
}

SqlViewer::~SqlViewer()
{
    delete dbHandler;
    delete ui;
}

void SqlViewer::onOpen()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open S4 configure json"), "../json_template", tr("Json files (*.json)"));

    if(!Utils::fileCanBeOpened(path)){
        QMessageBox::warning(NULL, "warning", "file is not readable!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    if (!glb_conf::pInstance()->load(path.toStdString()))
    {
        QMessageBox::warning(NULL, "warning", "file format error!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    ui->statusbar->showMessage(path);
    onLoadConf();
}

void SqlViewer::onLoadConf(void)
{
    //
    onOpenDBs();
}

void SqlViewer::onOpenDBs(void)
{
    _dbTree_model = new QStandardItemModel(this);
    _dbTree_model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("数据库"));
    onOpenDB_orders();
    ui->dbTree->setModel(_dbTree_model);
    ui->dbTree->setStyle(QStyleFactory::create("windows"));
}

void SqlViewer::onOpenDB_orders(void)
{

    glb_conf_t::db_t db = glb_conf::pInstance()->db();
    std::filesystem::path db_root_path = db.root;
    std::filesystem::path db_history_path = db_root_path / db.history_order;
    _pHistory_db = std::make_shared<sqlite::DB_t>(db_history_path.string());

    std::vector < std::string> history_tables = _pHistory_db->get_table_list();

    QStandardItem* orderRoot = new QStandardItem;
    orderRoot->setText(QStringLiteral(HISTORY_ORDER_TREE_ROOT));
    for (auto& tbl : history_tables) {
        QStandardItem* child = new QStandardItem;
        child->setText(tbl.c_str());
        orderRoot->appendRow(child);
    }
    _dbTree_model->appendRow(orderRoot);

}




void SqlViewer::openTableTab_orders(const std::string& table_name)
{
    S4::sqlite::s4_history_t_dbTbl history_tbl;
    //std::string condition = " WHERE mktCodeStr = '" + stkName + "'";
    //if (stgName.size()) {
    //    condition += " AND stgName = '" + stgName + "'";
    //}
    std::vector<struct s4_history_t> history_data;
    _pHistory_db->read_table<S4::sqlite::s4_history_t_dbTbl::data_t>(&history_tbl, table_name, history_data);
    std::vector<std::string> col_name = _pHistory_db->get_colum_list(table_name);

    orderModel* model = new orderModel(this);
    model->setTitle(col_name);
    for (auto& order : history_data) {
        model->append(order);
    }

    if(tabAlreadyExists(table_name.c_str())){
        QWidget *tab = tableMap.find(table_name.c_str()).value();
        int i = ui->tabWidget->indexOf(tab);
        ui->tabWidget->setCurrentIndex(i);
    }
    else{
        QTableView* tv = new QTableView(this);
        tableMap.insert(table_name.c_str(),tv);
        //QSqlQueryModel *model = dbHandler->getTableData(table_name.c_str());
        tv->setModel(model);
        int i = ui->tabWidget->addTab(tv, table_name.c_str());
        ui->tabWidget->setCurrentIndex(i);
    }
}



void SqlViewer::openTableTab(const QModelIndex &index){
    QString str;
    str += QStringLiteral("当前选中：%1\nrow:%2,column:%3\n").arg(index.data().toString())
        .arg(index.row()).arg(index.column());
    str += QStringLiteral("父级：%1\n").arg(index.parent().data().toString());
    ui->statusbar->showMessage(str);

    if (index.parent().data().toString() == QStringLiteral(HISTORY_ORDER_TREE_ROOT) && _pHistory_db) {
        std::string table_name = index.data().toString().toStdString();
        openTableTab_orders(table_name);
    }

    //const QString tabName = index.data(Qt::DisplayRole).toString();
    //if(tabAlreadyExists(tabName)){
    //    QWidget *tab = tableMap.find(tabName).value();
    //    int i = ui->tabWidget->indexOf(tab);
    //    ui->tabWidget->setCurrentIndex(i);
    //}
    //else{
    //    QTableView* tv = new QTableView(this);
    //    tableMap.insert(tabName,tv);
    //    QSqlQueryModel *model = dbHandler->getTableData(tabName);
    //    tv->setModel(model);


    //    int i = ui->tabWidget->addTab(tv,tabName);
    //    ui->tabWidget->setCurrentIndex(i);
    //}

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
    //ui->dbTree->setFlow(QListView::Flow::TopToBottom);
    ui->dbTree->setModel(model);

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

}