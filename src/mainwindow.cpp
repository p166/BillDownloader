#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QTextStream>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ScanDialog(this),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    categories = CategoriesSingleton::getInstance();
    categories->load();

    m_FakeDeviceID = m_Settings.value("User/DeviceID",QUuid::createUuid().toString()).toString();
    ui->lineEditUser->setText(m_Settings.value("User/Phone").toString());
    ui->lineEditPassword->setText(m_Settings.value("User/Password").toString());
    m_ScanDialog.setIsAppendToTable(m_Settings.value("User/isAppendTable", true).toBool());
    m_ScanDialog.setIsPacketImages(m_Settings.value("User/isPacketImages", true).toBool());

    qDebug() << "login:" << ui->lineEditUser->text();
    qDebug() << "pass:" << ui->lineEditPassword->text();

    wn_filter = new AutoFilter();

    model_recepeits = new ModelRecepeits(this);
    ui->tableView->setModel(model_recepeits);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL0_DATE,  150);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL1_NAME,  600);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL2_COUNT, 100);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL3_PRICE, 100);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL4_SUM,   100);

    delegate_lineedit = new LineEditDelegate(ui->tableView, categories->getList());
    ui->tableView->setItemDelegateForColumn(MR_COLUMNS::CL5_CATEGORY, delegate_lineedit);

    wn_progress = new DialogProgress(this);
    connect(wn_progress, SIGNAL(retry_reconize()), this, SLOT(retry_reconize()));

    req_manager.setAuth(ui->lineEditUser->text(), ui->lineEditPassword->text(), m_FakeDeviceID);
    req_manager.setModels(model_recepeits, &(m_ScanDialog.m_Model));
    connect(&req_manager, SIGNAL(req_total(int)), wn_progress, SLOT(setTotal(int)));
    connect(&req_manager, SIGNAL(req_reconized(bool)), wn_progress, SLOT(reconized(bool)));
    connect(&req_manager, SIGNAL(req_finished()), this, SLOT(updateCategoriesInTable()));

    wn_filters = new DialogFilters(this);

//    QImage image;
//    image.load("./XXX.jpg");
//    QFile qb("./img.data");
//    qb.open(QIODevice::WriteOnly);
//    qb.write((const char *) image.bits(), qint64(image.bytesPerLine()) * image.height());
//    qb.close();
}

void MainWindow::retry_reconize()
{
    m_ScanDialog.m_Model.clearErrors();
    req_manager.run();
}

MainWindow::~MainWindow()
{
    m_Settings.setValue("User/Phone", ui->lineEditUser->text());
    m_Settings.setValue("User/Password", ui->lineEditPassword->text());
    m_Settings.setValue("User/DeviceID", m_FakeDeviceID);
    m_Settings.setValue("User/isAppendTable", m_ScanDialog.isAppendToTable());
    m_Settings.setValue("User/isPacketImages", m_ScanDialog.isPacketImages());
    m_Settings.sync();


    delete wn_filter;
    delete wn_progress;
    delete wn_filters;
    delete model_recepeits;

    categories->save();

    delete ui;
}

void MainWindow::on_btClearTable_clicked()
{
    model_recepeits->vector.clear();
    model_recepeits->forceUpdate();
}

//TODO: экспорт для программы AbilityCash в формате xml
void MainWindow::on_btAbilityCashExport_clicked()
{
    QDateTime now = QDateTime::currentDateTime();
    QString ts = now.toString("yyyy-MM-dd_HH_mm");
    QString filename = QString("./%1_%2.xml").arg("ability_cash").arg(ts);
    AbilityCashExport e(&model_recepeits->vector);
    e.export_xml(filename);
    QMessageBox::information(0,tr("Экспорт завершен"),tr("Экспорт в формат AbilityCach завершен! \nЗаписан файл %1").arg(filename));
}

void MainWindow::on_btRequest_clicked()
{
    if (m_ScanDialog.exec()){
        req_manager.run();
    }
}

//автоматическое категорирование
void MainWindow::on_btFilter_clicked()
{
    const int index = ui->tableView->currentIndex().row();
    if (index < 0)
        return;

    if (wn_filter->showDialog(model_recepeits->vector.at(index).name)) {
        model_recepeits->vector[index].category = wn_filter->getCategory();
        model_recepeits->vector[index].filter = true;
        model_recepeits->forceUpdate();
        updateCategoriesInTable();
    }
}

void MainWindow::updateCategoriesInTable()
{
    for (int i=0;i<model_recepeits->vector.count(); i++) {
        if (model_recepeits->vector[i].category.isEmpty()) {
            S_FILTER f = wn_filter->findFilter(model_recepeits->vector.at(i).name);
            model_recepeits->vector[i].category = f.category;
            model_recepeits->vector[i].filter   = f.valid;
            categories->addCategory(f.category);
        }
    }
    model_recepeits->forceUpdate();
}

void MainWindow::on_btShowFilters_clicked()
{
    wn_filters->loadFilters(wn_filter);
    wn_filters->exec();
}

void MainWindow::on_btShowCategories_clicked()
{

}

void MainWindow::on_lineEditUser_textChanged(const QString &arg1)
{
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::black);
    palette.setColor(QPalette::Base,Qt::white);
    if (arg1.length()!=12) {
        palette.setColor(QPalette::Base,Qt::red);
    }
    ui->lineEditUser->setPalette(palette);
}

void MainWindow::on_lineEditPassword_textChanged(const QString &arg1)
{
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::black);
    palette.setColor(QPalette::Base,Qt::white);
    if (arg1.length()==0) {
        palette.setColor(QPalette::Base,Qt::red);
    }
    ui->lineEditPassword->setPalette(palette);
}

