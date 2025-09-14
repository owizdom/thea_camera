QT += core widgets

CONFIG += c++17

TARGET = thea_camera
TEMPLATE = app

SOURCES += \
    src/gui/main.cpp \
    src/gui/mainwindow.cpp

HEADERS += \
    src/gui/mainwindow.h

FORMS += \
    mainwindow.ui

# OpenCV configuration
INCLUDEPATH += /opt/homebrew/include/opencv4
LIBS += -L/opt/homebrew/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lopencv_highgui

# macOS specific
macx {
    LIBS += -framework Foundation -framework CoreVideo -framework CoreMedia -framework AVFoundation
}
