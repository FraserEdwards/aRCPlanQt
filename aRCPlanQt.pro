#-------------------------------------------------
#
# Project created by QtCreator 2014-03-26T13:48:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = aRCPlanQt
TEMPLATE = app
CONFIG-= app_bundle

SOURCES += main.cpp\
    Backfill.cpp \
    BeamModel.cpp \
    ConfigFile.cpp \
    Constants.cpp \
    Control.cpp \
    Creep.cpp \
    Decompression.cpp \
    FDprofile.cpp \
    Filepath.cpp \
    FracMech.cpp \
    Geometry.cpp \
    Interface.cpp \
    Log.cpp \
    Material.cpp \
    OutflowProcess.cpp \
    Parameters.cpp \
    Simulation.cpp \
    Solution.cpp \
    SymDoubleMatrix.cpp \
    TestSetup.cpp \
    guimain.cpp \
    qcustomplot.cpp


HEADERS  += \
    BeamModel.h \
    ConfigFile.h \
    Constants.h \
    Control.h \
    Creep.h \
    Decompression.h \
    FDprofile.h \
    Filepath.h \
    FracMech.h \
    Geometry.h \
    Interface.h \
    Log.h \
    Material.h \
    OutflowProcess.h \
    Parameters.h \
    Simulation.h \
    Solution.h \
    SymDoubleMatrix.h \
    TestSetup.h \
    guimain.h \
    qcustomplot.h \
    Backfill.h


FORMS    += \
    guimain.ui

OTHER_FILES += \
    README.md \
    aRCPlan.dSYM \
    caseInputData.txt

RESOURCES +=
