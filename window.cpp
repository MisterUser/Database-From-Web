/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/



#include "window.h"

//! [Window constructor]
Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    /*
    outputFile = new QFile("/home/knoll/workspace/domtraversal/log/Betrieb.log");
    outputFile->open(QIODevice::WriteOnly | QIODevice::Text);
    outputFileStream = new QTextStream(outputFile);
    *outputFileStream << "=======Habib's List=======\n\n";
    outputFileStream->flush();
    */

    label_for_besucht = dockWidget->findChild<QLabel*>("label_for_besucht");
    besuchtCount = 0;


    sql_db = QSqlDatabase::addDatabase("QMYSQL");
    sql_db.setHostName("localhost");
    sql_db.setDatabaseName("Dortmund_Betrieb");

    if(sql_db.open())
    {
        qDebug() << "Database open";
    }
    else
    {
        qDebug() << "Error = " << sql_db.lastError();
    }




}
//! [Window constructor]

Window::~Window()
{
    //outputFile->close();
    //delete outputFile;
    //delete outputFileStream;
    sql_db.close();
}

//! [set URL]
void Window::setUrl(const QUrl &url)
{    
    webView->setUrl(url);
}
//! [set URL]
    
//! [begin document inspection]
void Window::on_webView_loadFinished()
{

    QWebFrame *frame = webView->page()->mainFrame();
    QWebElement document = frame->documentElement();

    examineChildElements(document, treeWidget->invisibleRootItem());
}
//! [begin document inspection]

//! [traverse document]
void Window::examineChildElements(const QWebElement &parentElement,
                                  QTreeWidgetItem *treeRoot) //was parentItem
{
    QWebElement element = parentElement.firstChild();
    while (!element.isNull()) {


        if(element.tagName().compare("A") == 0)
        {
            if(element.attribute("href").contains("betrieb"))
            {
                QTreeWidgetItem *item = new QTreeWidgetItem();
                item->setText(0, element.toPlainText());
                treeRoot->addChild(item);
                parse_page(element.attribute("href"));

            }
            if(element.toPlainText().contains("weiter"))
            {
                QString JS = element.attribute("href");
                QThread::msleep(100);
                element.evaluateJavaScript(JS);
            }
        }

        //subtrees
        examineChildElements(element, treeRoot);

        //siblings (on same level)
        element = element.nextSibling();
    }
}
//! [traverse document]

void Window::parse_page(QString page_URL)
{
    page_URL.prepend("http://www.hwk-do.de/");
    InnerWindow * innerWin = new InnerWindow(QUrl(page_URL), &sql_db ,NULL);
    connect(innerWin, SIGNAL(parsingFinished(InnerWindow*)), this, SLOT(on_parse_finished(InnerWindow*)));
    return;
}


void Window::on_parse_finished(InnerWindow* innerWin)
{
    innerWin->deleteLater();
    //*outputFileStream << "---------------"<<besuchtCount<<"------------------ "<< "\n\n";
    label_for_besucht->setText("Besucht: " + QString::number(++besuchtCount));
    return;
}


