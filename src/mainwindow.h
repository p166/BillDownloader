#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogscanreceipt.h"
#include "dialogcopytext.h"
#include <QSettings>
#include "cnetclient.h"
#include <QNetworkAccessManager>
#include <QCompleter>
#include <QBitmap>
#include <QFileDialog>

#include "export/abilitycash/abilitycashexport.h"
#include "utils.h"
#include "autofilter.h"
#include "modelreceipts.h"
#include "requestmanager.h"
#include "dialogprogress.h"
#include "dialogfilters.h"
#include "categoriessingleton.h"
#include "delegate_lineedit.h"



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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void retry_reconize();
private slots:
    void on_btClearTable_clicked();
    void on_btAbilityCashExport_clicked();
    void on_btRequest_clicked();
    void on_btFilter_clicked();
    void on_btShowFilters_clicked();
    void on_btShowCategories_clicked();
    void on_lineEditUser_textChanged(const QString &arg1);
    void updateCategoriesInTable();

    void on_lineEditPassword_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    AutoFilter *wn_filter;
    DialogFilters *wn_filters;
    ModelRecepeits *model_recepeits;
    RequestManager req_manager;
    DialogProgress *wn_progress;
    CategoriesSingleton *categories;
    LineEditDelegate *delegate_lineedit;
};

#endif // MAINWINDOW_H
