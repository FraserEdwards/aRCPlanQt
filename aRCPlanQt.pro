#-------------------------------------------------
#
# Project created by QtCreator 2014-03-26T13:48:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = aRCPlanQt
TEMPLATE = app
CONFIG-= app_lib

ICON = Test.icns

SOURCES += main.cpp\
    Backfill.cpp \
    BeamModel.cpp \
    ConfigFile.cpp \
    Constants.cpp \
    Creep.cpp \
    Decompression.cpp \
    FDprofile.cpp \
    FracMech.cpp \
    Log.cpp \
    OutflowProcess.cpp \
    Parameters.cpp \
    Simulation.cpp \
    Solution.cpp \
    SymDoubleMatrix.cpp \
    guimain.cpp \
    qcustomplot.cpp \
    File.cpp \
    about.cpp \
    dialog.cpp


HEADERS  += \
    BeamModel.h \
    ConfigFile.h \
    Constants.h \
    Creep.h \
    Decompression.h \
    FDprofile.h \
    FracMech.h \
    Log.h \
    OutflowProcess.h \
    Parameters.h \
    Simulation.h \
    Solution.h \
    SymDoubleMatrix.h \
    guimain.h \
    qcustomplot.h \
    Backfill.h \
    File.h \
    about.h \
    dialog.h


FORMS    += \
    guimain.ui \
    about.ui \
    dialog.ui

OTHER_FILES += \
    README.md \
    aRCPlan.dSYM

RESOURCES +=
