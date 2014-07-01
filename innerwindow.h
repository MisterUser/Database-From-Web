#ifndef INNERWINDOW_H
#define INNERWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QWebElement>
#include <QtWidgets>
#include <QtWebKitWidgets>
#include <QMutex>
#include <QtSql>

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
QT_END_NAMESPACE
#include "ui_window.h"

class InnerWindow : public QMainWindow, private Ui::Window
{
    Q_OBJECT
public:
    InnerWindow(const QUrl &url, QSqlDatabase *openDataBase, QWidget *parent = 0);
    void setUrl(const QUrl &url);

signals:
    void parsingFinished(InnerWindow*);
public slots:
    void on_webView_loadFinished();

private:

    //QTextStream * outputFileStream;
    bool secondTimeRound;
    QSqlDatabase sql_db;


    //Functions
    void get_biz_info(const QWebElement &mainDOC);
    void writeToDataBase(QString betrieb_Name, QString betrieb_Adresse, QString betrieb_PLZ, QString betrieb_StadtOrt, QString betrieb_Telefon, QString betrieb_Homepage, QString betrieb_Email, QString betrieb_Gewerk);
    void parseAngaben(QString betriebAngabenIn);

};

#endif // INNERWINDOW_H
