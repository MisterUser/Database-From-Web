#include "innerwindow.h"

InnerWindow::InnerWindow(const QUrl &url, QTextStream * outputFS, QWidget *parent) :
    QMainWindow(parent)
{
    secondTimeRound = false;
    outputFileStream = outputFS;
    setupUi(this);
    setUrl(url);

}

void InnerWindow::setUrl(const QUrl &url)
{
    webView->setUrl(url);
    secondTimeRound = true;
}

void InnerWindow::on_webView_loadFinished()
{
    treeWidget->clear();

    if(secondTimeRound)
    {
        QWebFrame *frame = webView->page()->mainFrame();
        QWebElement document = frame->documentElement();
        get_biz_info(document);
    }
}


void InnerWindow::get_biz_info(const QWebElement &mainDOC)
{
    QWebElement head = mainDOC.firstChild(); //html

    QWebElement body = head.nextSibling();   //body

    if(body.tagName().compare("BODY") == 0)
    {
        QWebElement div1 = body.firstChild();        //div

        QWebElement div2 = div1.firstChild();               //div
        div2 = div2.nextSibling();                          //div
        div2 = div2.nextSibling();                          //div
        div2 = div2.nextSibling();                          //div

        QWebElement div3 = div2.firstChild();                   //div
        QWebElement div4 = div3.firstChild();                       //div
        QWebElement div5 = div4.firstChild();                           //div
        div5 = div5.nextSibling();                                      //div
        QWebElement div6 = div5.firstChild();                               //div
        div6 =div6.nextSibling();                                           //div
        div6 =div6.nextSibling();                                           //div
        div6 =div6.nextSibling();                                           //div

        QWebElement div7 = div6.firstChild();                                   //div
        QWebElement div8 = div7.firstChild();                                       //script
        div8 = div8.nextSibling();                                                  //table
        QWebElement div9 = div8.firstChild();                                           //form
        div9 = div9.nextSibling();                                                      //tbody
        QWebElement div10 = div9.firstChild();                                              //tr
        div10 = div10.nextSibling();                                                        //tr

        QWebElement div11 = div10.firstChild();                                                 //td
        *outputFileStream << "-------------------------------------- "<< "\n";
        *outputFileStream << div11.toPlainText();
        /*
        QWebElement div12 = div11.firstChild();                                                     //span


        // *outputFileStream << "Betrieb: " << div12.tagName() << "\n";
        div12 = div12.nextSibling();                                                                        //br
        div12 = div12.nextSibling();                                                                        //string
        // *outputFileStream << "Addresse: " << div12.toPlainText() << "\n";
        div12 = div12.nextSibling();                                                                        //br
        div12 = div12.nextSibling();                                                                        //string
        // *outputFileStream << "PLZ und ORT: " << div12.toPlainText() << "\n";
        div12 = div12.nextSibling();                                                                        //br
        div12 = div12.nextSibling();                                                                        //br
        div12 = div12.nextSibling();                                                                        //span
        div12 = div12.nextSibling();                                                                        //br
        QWebElement innerTable = div12.firstChild();                                                //table
        QWebElement innerTableBody = innerTable.firstChild();                                           //tbody
        QWebElement tr_tag = innerTableBody.firstChild();                                                   //tr
        QWebElement td_tag = tr_tag.firstChild();                                                               //td
        td_tag.nextSibling();                                                                                   //td
        // *outputFileStream << "Telefon: " << td_tag.toPlainText() << "\n";
        tr_tag.nextSibling();                                                                               //tr
        td_tag = tr_tag.firstChild();                                                                           //td
        td_tag.nextSibling();                                                                                   //td
        QWebElement a_link = td_tag.firstChild();                                                                   //a
        // *outputFileStream << "Homepage: " << a_link.toPlainText() << "\n";
        tr_tag.nextSibling();                                                                               //tr
        td_tag = tr_tag.firstChild();                                                                           //td
        td_tag.nextSibling();                                                                                   //td
        a_link = td_tag.firstChild();                                                                               //a
        // *outputFileStream << "E-mail: " << a_link.toPlainText() << "\n";
        div12 = div12.nextSibling();                                                                        //br
        div12 = div12.nextSibling();                                                                        //span
        div12 = div12.nextSibling();                                                                        //br
        div12 = div12.nextSibling();                                                                        //string
        // *outputFileStream << "Gewerk: " << div12.toPlainText() << "\n";
        */

        outputFileStream->flush();
    }
    emit parsingFinished(this);
    //return;
}

