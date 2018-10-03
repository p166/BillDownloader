#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogscanreceipt.h"
#include "dialogcopytext.h"
#include <QSettings>
#include "cnetclient.h"
#include <QNetworkAccessManager>
#include <QCompleter>

#include "export/abilitycash/abilitycashexport.h"
#include "utils.h"
#include "autofilter.h"
#include "modelreceipts.h"
#include "requestlist.h"
#include "dialogprogress.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:




    struct sSavedItem{
        QString name;
        QString newName;
        QString category;
        float countFactor;
        QString countType;
    };

    struct sCSVItem{
        QString text;
        int price;
    };

    QCompleter          m_NewNameAutoComplete;
    QNetworkAccessManager m_NAM;
    QSettings           m_Settings;
    DialogScanReceipt      m_ScanDialog;
    DialogCopyText      m_CopyTextDialog;
    QVector<sItem>      m_Items;
    bool                m_DateTimeAvaialble;
    QDateTime           m_ReceiptDateTime;
    QStringList         m_Categories;
    QMap<QString,sSavedItem> m_SavedItems;
    QString             m_FakeDeviceID;

private:
    void loadItems();
    void saveItems();
    void loadCategories();
    void saveCategories();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

private slots:
    void on_btClearTable_clicked();
    void on_btAbilityCashExport_clicked();
    void on_btRequest_clicked();
    void on_btFilter_clicked();
    void updateCategoriesInTable();

private:
    Ui::MainWindow *ui;
    AutoFilter *filter;
    ModelRecepeits *model_recepeits;
    RequestList req_list;
    DialogProgress *progress;
};

#endif // MAINWINDOW_H
