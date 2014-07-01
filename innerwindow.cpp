#include "innerwindow.h"


InnerWindow::InnerWindow(const QUrl &url, QSqlDatabase * openDataBase, QWidget *parent) :
    QMainWindow(parent)
{
    secondTimeRound = false;
    //outputFileStream = outputFS;
    setupUi(this);
    setUrl(url);

    sql_db = *openDataBase;
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
        //*outputFileStream << "-------------------------------------- "<< "\n";
        //*outputFileStream << div11.toPlainText();
        QString betriebAngaben(div11.toPlainText());
        parseAngaben(betriebAngaben);


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

        //outputFileStream->flush();
    }
    emit parsingFinished(this);
    //return;
}

void InnerWindow::writeToDataBase(QString betrieb_Name, QString betrieb_Adresse, QString betrieb_PLZ, QString betrieb_StadtOrt, QString betrieb_Telefon, QString betrieb_Homepage, QString betrieb_Email, QString betrieb_Gewerk)
{
    QString mysql_command = QString("INSERT INTO Angaben VALUES('%1', '%2','%3','%4','%5','%6','%7','%8');")
                                    .arg(betrieb_Name).arg(betrieb_Adresse).arg(betrieb_PLZ).arg(betrieb_StadtOrt)
                                    .arg(betrieb_Telefon).arg(betrieb_Homepage).arg(betrieb_Email).arg(betrieb_Gewerk);

    sql_db.exec(mysql_command);

    /*
     * if(sql_db.lastError() == QSqlError::ErrorType::NoError)
    {
        return true;
    }
    else return false;


    //sql_db.exec("INSERT INTO Angaben VALUES('Ive Got Worms', 'Dingbanger Weg','43212','Aspen','076012341234','www.foo.com','reachme@foo.com','handwerke');");
    //sql_db.exec("DELETE FROM Angaben where name='Ive Got Worms';");
     */
}

void InnerWindow::parseAngaben(QString betriebAngabenIn)
{
    QStringList angabenListe = betriebAngabenIn.split("\n", QString::SkipEmptyParts);
    QString betrieb_Gewerk      = angabenListe.at(angabenListe.size() - 1);
    if(betrieb_Gewerk.contains("Elektrotechnik")
     ||betrieb_Gewerk.contains("Installateur")
     ||betrieb_Gewerk.contains("Heizungsbau") )
    {
        QString betrieb_Name        = angabenListe.at(0).trimmed().toLocal8Bit().constData();
        QString betrieb_Adresse     = angabenListe.at(1).trimmed().toLocal8Bit().constData();
        QStringList plz_und_ort     = angabenListe.at(2).split(" ", QString::SkipEmptyParts);
        QString betrieb_PLZ         = plz_und_ort.at(0).trimmed().toLocal8Bit().constData();
        QString betrieb_StadtOrt    = plz_und_ort.at(1).trimmed().toLocal8Bit().constData();
        QString betrieb_Telefon     = "";
        QString betrieb_Homepage    = "";
        QString betrieb_Email       = "";


        for(int i = 4; i<angabenListe.size();i++)
        {
            if(angabenListe.at(i).contains("Telefon"))
            {
                 betrieb_Telefon = angabenListe.at(i).section(':',-1,-1).remove(QChar(' ')).remove(QChar('-')).trimmed().toLocal8Bit().constData();
            }
            if(angabenListe.at(i).contains("Homepage"))
            {
                 betrieb_Homepage = angabenListe.at(i).section(':',-1,-1).trimmed().toLocal8Bit().constData();
            }
            if(angabenListe.at(i).contains("E-Mail"))
            {
                 betrieb_Email = angabenListe.at(i).section(':',-1,-1).trimmed().toLocal8Bit().constData();
            }
        }

        writeToDataBase(betrieb_Name, betrieb_Adresse, betrieb_PLZ, betrieb_StadtOrt, betrieb_Telefon, betrieb_Homepage, betrieb_Email, betrieb_Gewerk);
    }
}
