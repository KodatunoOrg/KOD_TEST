# Preferences -> ビルドと実行 -> Default Build Properties -> Default build directory を
# ./build
# に変えておく

QT += core gui opengl
QT += widgets
QT += openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    SYS/ \
    UA/ \
    GUI/ \
    $$PWD/../Kernel/include/ \ # 各自の環境に合わせて変更
    ../boost

SOURCES += \
    GUI/QtMain.cpp \
    GUI/StdAfxQt.cpp \
    GUI/QtUserStatDialog.cpp \
    GUI/QtSweepSurfDialog.cpp \
    GUI/QtRotSurfDialog.cpp \
    GUI/QtNurbsSurfDialog.cpp \
    GUI/QtNurbsCurveDialog.cpp \
    GUI/QtMainWindow.cpp \
    GUI/QtDescribeView.cpp \
    GUI/QtConsole.cpp \
    Sys/Kodatuno_Main.cpp \
    Sys/Kodatuno_CMD.cpp \
    Sys/Command.cpp \
    UA/UserFunc.cpp \
    UA/SampleFunc2.cpp \
    UA/SampleFunc1.cpp \
    UA/SampleFunc3.cpp

HEADERS += \
    GUI/StdAfxQt.h \
    GUI/QtUserStatDialog.h \
    GUI/QtSweepSurfDialog.h \
    GUI/QtRotSurfDialog.h \
    GUI/QtNurbsSurfDialog.h \
    GUI/QtNurbsCurveDialog.h \
    GUI/QtMainWindow.h \
    GUI/QtDescribeView.h \
    GUI/QtConsole.h \
    Sys/Kodatuno.h \
    Sys/Command.h \
    UA/UserFunc.h \
    UA/SampleFunc.h

FORMS    += \
    GUI/QtUserStatDialog.ui \
    GUI/QtSweepSurfDialog.ui \
    GUI/QtRotSurfDialog.ui \
    GUI/QtNurbsSurfDialog.ui \
    GUI/QtNurbsCurveDialog.ui \
    GUI/QtMainWindow.ui

RESOURCES += \
    GUI/icons.qrc

TRANSLATIONS += \
    KOD_TEST_ja_JP.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# libKernel は OpenGL の前に定義しないとリンクエラーになる
LIBS += -L$$PWD/../Kernel/build/debug/ -llibKernel # 各自の環境に合わせて変更
LIBS += -lopengl32 -lglu32
