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

    m_FakeDeviceID = m_Settings.value("User/DeviceID",QUuid::createUuid().toString()).toString();
    ui->lineEditUser->setText(m_Settings.value("User/Phone").toString());
    ui->lineEditPassword->setText(m_Settings.value("User/Password").toString());
    m_ScanDialog.setIsAppendToTable(m_Settings.value("User/isAppendTable", true).toBool());
    m_ScanDialog.setIsPacketImages(m_Settings.value("User/isPacketImages", true).toBool());

    qDebug() << "login:" << ui->lineEditUser->text();
    qDebug() << "pass:" << ui->lineEditPassword->text();

    filter = new AutoFilter();

    model_recepeits = new ModelRecepeits(this);
    ui->tableView->setModel(model_recepeits);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL0_DATE,  150);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL1_NAME,  600);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL2_COUNT, 100);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL3_PRICE, 100);
    ui->tableView->setColumnWidth(MR_COLUMNS::CL4_SUM,   100);

    req_list.setAuth(ui->lineEditUser->text(), ui->lineEditPassword->text(), m_FakeDeviceID);
    req_list.setModels(model_recepeits, &(m_ScanDialog.m_Model));
//    req_list.setAutoFilter(filter);

    progress = new DialogProgress(this);
    connect(&req_list, SIGNAL(req_total(int)), progress, SLOT(setTotal(int)));
    connect(&req_list, SIGNAL(req_reconized(bool)), progress, SLOT(reconized(bool)));
    connect(&req_list, SIGNAL(req_finished()), this, SLOT(updateCategoriesInTable()));

    loadItems();
    loadCategories();
}

MainWindow::~MainWindow()
{
    m_Settings.setValue("User/Phone", ui->lineEditUser->text());
    m_Settings.setValue("User/Password", ui->lineEditPassword->text());
    m_Settings.setValue("User/DeviceID", m_FakeDeviceID);
    m_Settings.setValue("User/isAppendTable", m_ScanDialog.isAppendToTable());
    m_Settings.setValue("User/isPacketImages", m_ScanDialog.isPacketImages());
    m_Settings.sync();

    saveCategories();

    delete filter;
    delete ui;
}

void MainWindow::loadCategories()
{
    QFile textFile("categories.txt");
    if (textFile.open(QIODevice::ReadOnly)){
        QTextStream textStream(&textFile);
        while (true)
        {
            QString line = textStream.readLine();
            if (line.isNull())
                break;
            else
                m_Categories.append(line);
        }
    }
    m_Categories.sort();
    m_Categories.insert(0,"");
}

void MainWindow::saveCategories()
{
    for (int i=0;i<m_Items.count(); i++) {
        m_Categories.append(m_Items.at(i).category);
    }
    m_Categories.sort();
    m_Categories.removeDuplicates();

    QFile textFile("categories.txt");
    if (textFile.open(QIODevice::WriteOnly)){
        QTextStream out(&textFile);
        foreach (auto cat, m_Categories) {
            out << cat << "\n";
        }
    }
    textFile.close();
}

void MainWindow::loadItems()
{
    QFile textFile("items.csv");
    if (textFile.open(QIODevice::ReadOnly)){
        m_SavedItems.clear();
        QTextStream textStream(&textFile);
        while (true)
        {
            QString line = textStream.readLine();
            if (line.isNull())
                break;
            else{
                QStringList row = line.split(";",QString::KeepEmptyParts);
                if (row.count()!=5)
                    break;
                else{
                    sSavedItem item;
                    item.name = row[0];
                    item.newName = row[1];
                    item.category = row[2];
                    item.countFactor = row[3].toFloat();
                    item.countType = row[4];
                    m_SavedItems.insert(item.name,item);
                }
            }
        }
    }
}

void MainWindow::saveItems()
{
    loadItems();//load actual items, update, and save.
    for (int i = 0; i<m_Items.count(); ++i){
        auto itemIt = m_SavedItems.find(m_Items[i].name);
        if (itemIt==m_SavedItems.end()){
            sSavedItem item;
            item.category = m_Items[i].category;
            item.countFactor = m_Items[i].countFactor;
            item.countType = m_Items[i].countType;
            item.newName = m_Items[i].newname;
            item.name = m_Items[i].name;
            m_SavedItems.insert(item.name,item);
        }
        else{
            itemIt.value().category = m_Items[i].category;
            itemIt.value().countFactor = m_Items[i].countFactor;
            itemIt.value().countType = m_Items[i].countType;
            itemIt.value().newName = m_Items[i].newname;
        }
    }

    QFile textFile("items.csv");
    if (textFile.open(QIODevice::WriteOnly)){
        auto it = m_SavedItems.begin();
        while (it!=m_SavedItems.end()){
            QString line = it.value().name + ";"+
                            it.value().newName + ";"+
                            it.value().category + ";"+
                            QString::number(it.value().countFactor) + ";"+
                            it.value().countType+"\n";
            textFile.write(line.toUtf8());
            ++it;
        }
    };
}

void MainWindow::on_btClearTable_clicked()
{
    model_recepeits->vector.clear();
    model_recepeits->forceUpdate();
}

//TODO: экспорт для программы AbilityCash в формате xml
void MainWindow::on_btAbilityCashExport_clicked()
{
    AbilityCashExport e(&model_recepeits->vector);
    e.export_xml("./ability_cash.xml");
    QMessageBox::information(0,tr("Экспорт завершен"),tr("Экспорт в формат AbilityCach завершен!"));
}

void MainWindow::on_btRequest_clicked()
{
    if (m_ScanDialog.exec()){
        req_list.run();
    }
}

//автоматическое категорирование
void MainWindow::on_btFilter_clicked()
{
    const int index = ui->tableView->currentIndex().row();
    if (index < 0)
        return;

    if (filter->showDialog(model_recepeits->vector.at(index).name)) {
        model_recepeits->vector[index].category = filter->getCategory();
        model_recepeits->vector[index].filter = true;
        model_recepeits->forceUpdate();
        updateCategoriesInTable();
    }
}

void MainWindow::updateCategoriesInTable()
{
    for (int i=0;i<model_recepeits->vector.count(); i++) {
        if (model_recepeits->vector[i].category.isEmpty()) {
            S_FILTER f = filter->findFilter(model_recepeits->vector.at(i).name);
            model_recepeits->vector[i].category = f.category;
            model_recepeits->vector[i].filter   = f.valid;
        }
    }
    model_recepeits->forceUpdate();
}
