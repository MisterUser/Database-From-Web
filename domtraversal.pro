QT       += webkitwidgets network widgets
FORMS     = window.ui
HEADERS   = window.h \
    innerwindow.h
SOURCES   = main.cpp \
            window.cpp \
    innerwindow.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/webkitwidgets/domtraversal
INSTALLS += target

