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

ICON = Images/Test.icns

SOURCES += Source/main.cpp\
    Source/about.cpp \
    Source/Backfill.cpp \
    Source/BeamModel.cpp \
    Source/ConfigFile.cpp \
    Source/Constants.cpp \
    Source/Creep.cpp \
    Source/Decompression.cpp \
    Source/dialog.cpp \
    Source/FDprofile.cpp \
    Source/File.cpp \
    Source/FracMech.cpp \
    Source/guimain.cpp \
    Source/OutflowProcess.cpp \
    Source/Parameters.cpp \
    Source/qcustomplot.cpp \
    Source/Simulation.cpp \
    Source/Solution.cpp \
    Source/SymDoubleMatrix.cpp

HEADERS  += \
    Source/about.h \
    Source/Backfill.h \
    Source/BeamModel.h \
    Source/ConfigFile.h \
    Source/Constants.h \
    Source/Creep.h \
    Source/Decompression.h \
    Source/dialog.h \
    Source/FDprofile.h \
    Source/File.h \
    Source/FracMech.h \
    Source/guimain.h \
    Source/OutflowProcess.h \
    Source/Parameters.h \
    Source/qcustomplot.h \
    Source/Simulation.h \
    Source/Solution.h \
    Source/SymDoubleMatrix.h


FORMS    += \
    Source/guimain.ui \
    Source/about.ui \
    Source/dialog.ui

OTHER_FILES += \
    README.md \
    aRCPlan.dSYM

RESOURCES +=
