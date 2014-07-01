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

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QWebElement>
#include <QtWidgets>
#include <QtWebKitWidgets>
#include <QMutex>
#include <QtSql>
#include <QDebug>
#include "innerwindow.h"

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
QT_END_NAMESPACE

//! [Window class definition]
#include "ui_window.h"

class Window : public QMainWindow, private Ui::Window
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();
    void setUrl(const QUrl &url);

//signals:
    //void _startParse(QUrl);
public slots:
    void on_webView_loadFinished();
    void on_parse_finished(InnerWindow* innerWin);

private:
    void examineChildElements(const QWebElement &parentElement,
                              QTreeWidgetItem *treeRoot);
    //QFile * outputFile;
    //QTextStream * outputFileStream;
    QLabel * label_for_besucht;
    int besuchtCount;

    QSqlDatabase sql_db;

    //Functions
    void parse_page(QString page_URL);


};
//! [Window class definition]

#endif
