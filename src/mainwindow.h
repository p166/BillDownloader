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

enum COLUMNS {COL_DATE, COL_NAME, COL_SHOT_NAME, COL_COUNT_IN, COL_COUNT, COL_EDIZM, COL_COST, COL_CATEGOTRY, COL_SUM_COUNT, COL_GAR, COL_TYPE_GAR};


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
    int getItemIndex(QString name);
private:
    bool parseReceipt(QByteArray jsonText);
    void reinitItems();
    void reinitTable();

    void loadItems();
    void saveItems();
    void loadCategories();
    void saveCategories();
    void sendRequest();
    void sendRequest(const QString fn, const QString fd, const QString fpd);
    QStringList generateCSV();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void imageDecoded();

private slots:

private slots:
    void replyFinished(QNetworkReply* reply);
    void onCountFactorValueChanged(double value);
    void onCountTypeValueChanged(QString value);
    void onCategoryValueChanged(QString value);
    void onNewNameValueChanged(QString value);
    void onWarrantyPeriodValueChanged(int value);
    void onWarrantyTypeValueChanged(int value);
    void on_btClearTable_clicked();
    void on_btAbilityCashExport_clicked();
    void on_btRequest_clicked();
    void on_btResult_clicked();

    void on_btFilter_clicked();

private:
    Ui::MainWindow *ui;
    AutoFilter *filter;
};

#endif // MAINWINDOW_H
