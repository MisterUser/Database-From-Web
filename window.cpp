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
    outputFile = new QFile("/home/knoll/workspace/domtraversal/log/Betrieb.log");
    outputFile->open(QIODevice::WriteOnly | QIODevice::Text);
    outputFileStream = new QTextStream(outputFile);
    *outputFileStream << "=======Habib's List=======\n\n";
    outputFileStream->flush();
}
//! [Window constructor]

Window::~Window()
{
    outputFile->close();
    delete outputFile;
    delete outputFileStream;
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
    treeWidget->clear();

    QWebFrame *frame = webView->page()->mainFrame();
    QWebElement document = frame->documentElement();

    examineChildElements(document, treeWidget->invisibleRootItem());
}
//! [begin document inspection]

//! [traverse document]
void Window::examineChildElements(const QWebElement &parentElement,
                                  QTreeWidgetItem *parentItem)
{
    QWebElement element = parentElement.firstChild();
    while (!element.isNull()) {

        QTreeWidgetItem *item = new QTreeWidgetItem();
        if(element.tagName().compare("A") == 0)
        {
            if(element.attribute("href").contains("betrieb"))
            {
                *outputFileStream << "Betrieb: " << element.toPlainText() << "\n";
                outputFileStream->flush();
                parse_page(element.attribute("href"));
            }
            //QTreeWidgetItem *linkItem2 = new QTreeWidgetItem();
            //linkItem2->setText(0,element.attribute("href"));
            //item->addChild(linkItem2);

        }
        item->setText(0, element.tagName());

        parentItem->addChild(item);

        //subtrees
        examineChildElements(element, item);

        //siblings (on same level)
        element = element.nextSibling();
    }
}
//! [traverse document]





void Window::parse_page(QString page_URL)
{
    //outputFileStream << outString;
    setURL(page_URL);
    QWebFrame *frameInner = webView->page()->mainFrame();
    QWebElement documentBetrieb = frameInner->documentElement();

    get_biz_info(documentBetrieb);

    webView->back();
    return;
}

void Window::get_biz_info(const QWebElement &mainDOC)
{
    QWebElement element = mainDOC.firstChild(); //head
    element.nextSibling();                        //body
    QWebElement div1 = element.firstChild();        //div
    QWebElement div2 = div1.firstChild();               //div
    div2.nextSibling();                                 //div
    div2.nextSibling();                                 //div
    div2.nextSibling();                                 //div
    QWebElement div3 = div2.firstChild();                   //div
    QWebElement div4 = div3.firstChild();                       //div
    QWebElement div5 = div4.firstChild();                           //div
    div5.nextSibling();                                             //div
    QWebElement div6 = div5.firstChild();                               //div
    div6.nextSibling();                                                 //div
    div6.nextSibling();                                                 //div
    div6.nextSibling();                                                 //div
    QWebElement div7 = div6.firstChild();                                   //div
    QWebElement div8 = div7.firstChild();                                       //script
    div8.nextSibling();                                                         //table
    QWebElement div9 = div8.firstChild();                                           //form
    div9.nextSibling();                                                             //tbody
    QWebElement div10 = div9.firstChild();                                              //tr
    div10.nextSibling();                                                                //tr
    QWebElement div11 = div10.firstChild();                                                 //td
    QWebElement div12 = div11.firstChild();                                                     //span

    *outputFileStream << "-------------------------------------- "<< "\n";
    *outputFileStream << "Betrieb: " << div12.toPlainText() << "\n";
    div12.nextSibling();                                                                        //br
    div12.nextSibling();                                                                        //string
    *outputFileStream << "Addresse: " << div12.toPlainText() << "\n";
    div12.nextSibling();                                                                        //br
    div12.nextSibling();                                                                        //string
    *outputFileStream << "PLZ und ORT: " << div12.toPlainText() << "\n";
    div12.nextSibling();                                                                        //br
    div12.nextSibling();                                                                        //br
    div12.nextSibling();                                                                        //span
    div12.nextSibling();                                                                        //br
    QWebElement innerTable = div12.firstChild();                                                //table
    QWebElement innerTableBody = innerTable.firstChild();                                           //tbody
    QWebElement tr_tag = innerTableBody.firstChild();                                                   //tr
    QWebElement td_tag = tr_tag.firstChild();                                                               //td
    td_tag.nextSibling();                                                                                   //td
    *outputFileStream << "Telefon: " << td_tag.toPlainText() << "\n";
    tr_tag.nextSibling();                                                                               //tr
    td_tag = tr_tag.firstChild();                                                                           //td
    td_tag.nextSibling();                                                                                   //td
    QWebElement a_link = td_tag.firstChild();                                                                   //a
    *outputFileStream << "Homepage: " << a_link.toPlainText() << "\n";
    tr_tag.nextSibling();                                                                               //tr
    td_tag = tr_tag.firstChild();                                                                           //td
    td_tag.nextSibling();                                                                                   //td
    QWebElement a_link = td_tag.firstChild();                                                                   //a
    *outputFileStream << "E-mail: " << a_link.toPlainText() << "\n";
    div12.nextSibling();                                                                        //br
    div12.nextSibling();                                                                        //span
    div12.nextSibling();                                                                        //br
    div12.nextSibling();                                                                        //string
    *outputFileStream << "Gewerk: " << div12.toPlainText() << "\n";
    *outputFileStream << "-------------------------------------- "<< "\n\n";
    outputFileStream->flush();
    return;
}

