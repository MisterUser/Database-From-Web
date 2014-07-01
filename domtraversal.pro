QT       += webkitwidgets network widgets
QT       += sql
QTPLUGIN += qsqlmysql

FORMS     = window.ui
HEADERS   = window.h \
            innerwindow.h
SOURCES   = main.cpp \
            window.cpp \
            innerwindow.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/webkitwidgets/domtraversal
INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/qt5/plugins/sqldrivers/release/ -lqsqlmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/qt5/plugins/sqldrivers/debug/ -lqsqlmysql
else:unix: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/qt5/plugins/sqldrivers/ -lqsqlmysql

INCLUDEPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu/qt5/plugins/sqldrivers
INCLUDEPATH += /usr/include/mysql
LIBS        +=-L/usr/lib/mqsql
DEPENDPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu/qt5/plugins/sqldrivers
