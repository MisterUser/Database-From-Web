#ifndef INNERWINDOW_H
#define INNERWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QWebElement>
#include <QtWidgets>
#include <QtWebKitWidgets>
#include <QMutex>

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
QT_END_NAMESPACE
#include "ui_window.h"

class InnerWindow : public QMainWindow, private Ui::Window
{
    Q_OBJECT
public:
    InnerWindow(const QUrl &url, QTextStream * outputFS, QWidget *parent = 0);
    void setUrl(const QUrl &url);

signals:
    void parsingFinished(InnerWindow*);
public slots:
    void on_webView_loadFinished();

private:
    void get_biz_info(const QWebElement &mainDOC);
    QTextStream * outputFileStream;
    bool secondTimeRound;
};

#endif // INNERWINDOW_H
