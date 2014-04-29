/********************************************************************************
** Form generated from reading UI file 'guimain.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIMAIN_H
#define UI_GUIMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_guimain
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_8;
    QCustomPlot *Resultsplot;
    QPushButton *Save;
    QGridLayout *gridLayout;
    QLabel *label_23;
    QLabel *label_22;
    QTabWidget *tabs;
    QWidget *tab;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_5;
    QLabel *PipeID;
    QLabel *Density;
    QLineEdit *density;
    QLabel *DynamicModulus;
    QLineEdit *dynamicmodulus;
    QLabel *DDynamicModulus;
    QLineEdit *deltadynamicmodulus;
    QLabel *Creepmodulus;
    QLineEdit *creepmodulus;
    QLabel *Poissonratio;
    QLineEdit *dynpoissonratio;
    QComboBox *materialname;
    QWidget *tab_2;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_4;
    QLabel *PipeID_2;
    QLabel *PipeID_5;
    QLineEdit *outsidediameter;
    QLabel *PipeID_6;
    QLineEdit *sdr;
    QLabel *PipeID_7;
    QLineEdit *groovedepth;
    QLabel *PipeID_8;
    QLineEdit *relativediameter;
    QComboBox *pipename;
    QWidget *tab_3;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_3;
    QLabel *label_12;
    QCheckBox *fs;
    QLabel *label_13;
    QCheckBox *s4;
    QLabel *label_11;
    QLabel *PipeID_9;
    QLineEdit *testtemperature;
    QLabel *PipeID_10;
    QLineEdit *initialpressure;
    QLabel *PipeID_11;
    QLineEdit *backfilldepth;
    QLabel *PipeID_12;
    QLineEdit *backfilldensity;
    QLabel *PipeID_13;
    QLineEdit *solidfraction;
    QLabel *PipeID_14;
    QLineEdit *waterfraction;
    QCheckBox *backfill;
    QWidget *tab_4;
    QWidget *layoutWidget4;
    QGridLayout *gridLayout_2;
    QLabel *label_14;
    QLabel *PipeID_15;
    QLineEdit *initiallength;
    QLabel *PipeID_16;
    QLineEdit *crackspeed;
    QLabel *PipeID_17;
    QLineEdit *fdnumber;
    QCheckBox *fixedlength;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *path;
    QGridLayout *gridLayout_6;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_8;
    QLineEdit *from;
    QLabel *label_9;
    QLineEdit *to;
    QLabel *label_10;
    QLineEdit *noofpoints;
    QLabel *label_7;
    QComboBox *parameter;
    QCheckBox *singlemode;
    QCheckBox *rangemode;
    QPushButton *Runbutton;
    QTextEdit *Information;
    QCustomPlot *Resultsplot_2;
    QTableWidget *Resultstable;
    QMenuBar *menubar;
    QMenu *menuARCPlan;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *guimain)
    {
        if (guimain->objectName().isEmpty())
            guimain->setObjectName(QStringLiteral("guimain"));
        guimain->resize(1452, 755);
        centralwidget = new QWidget(guimain);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 1431, 948));
        gridLayout_8 = new QGridLayout(layoutWidget);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setSizeConstraint(QLayout::SetNoConstraint);
        gridLayout_8->setVerticalSpacing(10);
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        Resultsplot = new QCustomPlot(layoutWidget);
        Resultsplot->setObjectName(QStringLiteral("Resultsplot"));
        Resultsplot->setMinimumSize(QSize(465, 300));

        gridLayout_8->addWidget(Resultsplot, 1, 2, 1, 1);

        Save = new QPushButton(layoutWidget);
        Save->setObjectName(QStringLiteral("Save"));

        gridLayout_8->addWidget(Save, 3, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(-1, -1, -1, 0);
        label_23 = new QLabel(layoutWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_23, 0, 1, 1, 1);

        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_22, 0, 2, 1, 1);


        gridLayout_8->addLayout(gridLayout, 0, 0, 1, 3);

        tabs = new QTabWidget(layoutWidget);
        tabs->setObjectName(QStringLiteral("tabs"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(12, 12, 388, 178));
        gridLayout_5 = new QGridLayout(layoutWidget1);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        PipeID = new QLabel(layoutWidget1);
        PipeID->setObjectName(QStringLiteral("PipeID"));

        gridLayout_5->addWidget(PipeID, 0, 0, 1, 1);

        Density = new QLabel(layoutWidget1);
        Density->setObjectName(QStringLiteral("Density"));

        gridLayout_5->addWidget(Density, 1, 0, 1, 1);

        density = new QLineEdit(layoutWidget1);
        density->setObjectName(QStringLiteral("density"));

        gridLayout_5->addWidget(density, 1, 1, 1, 1);

        DynamicModulus = new QLabel(layoutWidget1);
        DynamicModulus->setObjectName(QStringLiteral("DynamicModulus"));

        gridLayout_5->addWidget(DynamicModulus, 2, 0, 1, 1);

        dynamicmodulus = new QLineEdit(layoutWidget1);
        dynamicmodulus->setObjectName(QStringLiteral("dynamicmodulus"));

        gridLayout_5->addWidget(dynamicmodulus, 2, 1, 1, 1);

        DDynamicModulus = new QLabel(layoutWidget1);
        DDynamicModulus->setObjectName(QStringLiteral("DDynamicModulus"));

        gridLayout_5->addWidget(DDynamicModulus, 3, 0, 1, 1);

        deltadynamicmodulus = new QLineEdit(layoutWidget1);
        deltadynamicmodulus->setObjectName(QStringLiteral("deltadynamicmodulus"));

        gridLayout_5->addWidget(deltadynamicmodulus, 3, 1, 1, 1);

        Creepmodulus = new QLabel(layoutWidget1);
        Creepmodulus->setObjectName(QStringLiteral("Creepmodulus"));

        gridLayout_5->addWidget(Creepmodulus, 4, 0, 1, 1);

        creepmodulus = new QLineEdit(layoutWidget1);
        creepmodulus->setObjectName(QStringLiteral("creepmodulus"));

        gridLayout_5->addWidget(creepmodulus, 4, 1, 1, 1);

        Poissonratio = new QLabel(layoutWidget1);
        Poissonratio->setObjectName(QStringLiteral("Poissonratio"));

        gridLayout_5->addWidget(Poissonratio, 5, 0, 1, 1);

        dynpoissonratio = new QLineEdit(layoutWidget1);
        dynpoissonratio->setObjectName(QStringLiteral("dynpoissonratio"));

        gridLayout_5->addWidget(dynpoissonratio, 5, 1, 1, 1);

        materialname = new QComboBox(layoutWidget1);
        materialname->setObjectName(QStringLiteral("materialname"));

        gridLayout_5->addWidget(materialname, 0, 1, 1, 1);

        tabs->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget2 = new QWidget(tab_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(12, 12, 436, 147));
        gridLayout_4 = new QGridLayout(layoutWidget2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        PipeID_2 = new QLabel(layoutWidget2);
        PipeID_2->setObjectName(QStringLiteral("PipeID_2"));

        gridLayout_4->addWidget(PipeID_2, 0, 0, 1, 1);

        PipeID_5 = new QLabel(layoutWidget2);
        PipeID_5->setObjectName(QStringLiteral("PipeID_5"));

        gridLayout_4->addWidget(PipeID_5, 1, 0, 1, 1);

        outsidediameter = new QLineEdit(layoutWidget2);
        outsidediameter->setObjectName(QStringLiteral("outsidediameter"));

        gridLayout_4->addWidget(outsidediameter, 1, 1, 1, 1);

        PipeID_6 = new QLabel(layoutWidget2);
        PipeID_6->setObjectName(QStringLiteral("PipeID_6"));

        gridLayout_4->addWidget(PipeID_6, 2, 0, 1, 1);

        sdr = new QLineEdit(layoutWidget2);
        sdr->setObjectName(QStringLiteral("sdr"));

        gridLayout_4->addWidget(sdr, 2, 1, 1, 1);

        PipeID_7 = new QLabel(layoutWidget2);
        PipeID_7->setObjectName(QStringLiteral("PipeID_7"));

        gridLayout_4->addWidget(PipeID_7, 3, 0, 1, 1);

        groovedepth = new QLineEdit(layoutWidget2);
        groovedepth->setObjectName(QStringLiteral("groovedepth"));

        gridLayout_4->addWidget(groovedepth, 3, 1, 1, 1);

        PipeID_8 = new QLabel(layoutWidget2);
        PipeID_8->setObjectName(QStringLiteral("PipeID_8"));

        gridLayout_4->addWidget(PipeID_8, 4, 0, 1, 1);

        relativediameter = new QLineEdit(layoutWidget2);
        relativediameter->setObjectName(QStringLiteral("relativediameter"));

        gridLayout_4->addWidget(relativediameter, 4, 1, 1, 1);

        pipename = new QComboBox(layoutWidget2);
        pipename->setObjectName(QStringLiteral("pipename"));

        gridLayout_4->addWidget(pipename, 0, 1, 1, 1);

        tabs->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        layoutWidget3 = new QWidget(tab_3);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(11, 12, 453, 232));
        gridLayout_3 = new QGridLayout(layoutWidget3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_3->addWidget(label_12, 0, 0, 1, 2);

        fs = new QCheckBox(layoutWidget3);
        fs->setObjectName(QStringLiteral("fs"));

        gridLayout_3->addWidget(fs, 0, 2, 1, 1);

        label_13 = new QLabel(layoutWidget3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_3->addWidget(label_13, 0, 3, 1, 1);

        s4 = new QCheckBox(layoutWidget3);
        s4->setObjectName(QStringLiteral("s4"));

        gridLayout_3->addWidget(s4, 0, 4, 1, 1);

        label_11 = new QLabel(layoutWidget3);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_3->addWidget(label_11, 1, 0, 1, 1);

        PipeID_9 = new QLabel(layoutWidget3);
        PipeID_9->setObjectName(QStringLiteral("PipeID_9"));

        gridLayout_3->addWidget(PipeID_9, 2, 0, 1, 2);

        testtemperature = new QLineEdit(layoutWidget3);
        testtemperature->setObjectName(QStringLiteral("testtemperature"));

        gridLayout_3->addWidget(testtemperature, 2, 3, 1, 2);

        PipeID_10 = new QLabel(layoutWidget3);
        PipeID_10->setObjectName(QStringLiteral("PipeID_10"));

        gridLayout_3->addWidget(PipeID_10, 3, 0, 1, 2);

        initialpressure = new QLineEdit(layoutWidget3);
        initialpressure->setObjectName(QStringLiteral("initialpressure"));

        gridLayout_3->addWidget(initialpressure, 3, 3, 1, 2);

        PipeID_11 = new QLabel(layoutWidget3);
        PipeID_11->setObjectName(QStringLiteral("PipeID_11"));

        gridLayout_3->addWidget(PipeID_11, 4, 0, 1, 2);

        backfilldepth = new QLineEdit(layoutWidget3);
        backfilldepth->setObjectName(QStringLiteral("backfilldepth"));

        gridLayout_3->addWidget(backfilldepth, 4, 3, 1, 2);

        PipeID_12 = new QLabel(layoutWidget3);
        PipeID_12->setObjectName(QStringLiteral("PipeID_12"));

        gridLayout_3->addWidget(PipeID_12, 5, 0, 1, 2);

        backfilldensity = new QLineEdit(layoutWidget3);
        backfilldensity->setObjectName(QStringLiteral("backfilldensity"));

        gridLayout_3->addWidget(backfilldensity, 5, 3, 1, 2);

        PipeID_13 = new QLabel(layoutWidget3);
        PipeID_13->setObjectName(QStringLiteral("PipeID_13"));

        gridLayout_3->addWidget(PipeID_13, 6, 0, 1, 3);

        solidfraction = new QLineEdit(layoutWidget3);
        solidfraction->setObjectName(QStringLiteral("solidfraction"));

        gridLayout_3->addWidget(solidfraction, 6, 3, 1, 2);

        PipeID_14 = new QLabel(layoutWidget3);
        PipeID_14->setObjectName(QStringLiteral("PipeID_14"));

        gridLayout_3->addWidget(PipeID_14, 7, 0, 1, 3);

        waterfraction = new QLineEdit(layoutWidget3);
        waterfraction->setObjectName(QStringLiteral("waterfraction"));

        gridLayout_3->addWidget(waterfraction, 7, 3, 1, 2);

        backfill = new QCheckBox(layoutWidget3);
        backfill->setObjectName(QStringLiteral("backfill"));

        gridLayout_3->addWidget(backfill, 1, 2, 1, 1);

        tabs->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        layoutWidget4 = new QWidget(tab_4);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(11, 12, 401, 301));
        gridLayout_2 = new QGridLayout(layoutWidget4);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget4);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 0, 0, 1, 1);

        PipeID_15 = new QLabel(layoutWidget4);
        PipeID_15->setObjectName(QStringLiteral("PipeID_15"));

        gridLayout_2->addWidget(PipeID_15, 1, 0, 1, 1);

        initiallength = new QLineEdit(layoutWidget4);
        initiallength->setObjectName(QStringLiteral("initiallength"));

        gridLayout_2->addWidget(initiallength, 1, 2, 1, 1);

        PipeID_16 = new QLabel(layoutWidget4);
        PipeID_16->setObjectName(QStringLiteral("PipeID_16"));

        gridLayout_2->addWidget(PipeID_16, 2, 0, 1, 1);

        crackspeed = new QLineEdit(layoutWidget4);
        crackspeed->setObjectName(QStringLiteral("crackspeed"));

        gridLayout_2->addWidget(crackspeed, 2, 2, 1, 1);

        PipeID_17 = new QLabel(layoutWidget4);
        PipeID_17->setObjectName(QStringLiteral("PipeID_17"));

        gridLayout_2->addWidget(PipeID_17, 3, 0, 1, 2);

        fdnumber = new QLineEdit(layoutWidget4);
        fdnumber->setObjectName(QStringLiteral("fdnumber"));

        gridLayout_2->addWidget(fdnumber, 3, 2, 1, 1);

        fixedlength = new QCheckBox(layoutWidget4);
        fixedlength->setObjectName(QStringLiteral("fixedlength"));

        gridLayout_2->addWidget(fixedlength, 0, 2, 1, 1);

        tabs->addTab(tab_4, QString());

        gridLayout_8->addWidget(tabs, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        path = new QLineEdit(layoutWidget);
        path->setObjectName(QStringLiteral("path"));

        horizontalLayout->addWidget(path);


        gridLayout_8->addLayout(horizontalLayout, 3, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setHorizontalSpacing(0);
        gridLayout_6->setContentsMargins(100, -1, 100, -1);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_6->addWidget(label_2, 0, 0, 1, 2);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_6->addWidget(label, 1, 0, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_8, 5, 0, 1, 1);

        from = new QLineEdit(layoutWidget);
        from->setObjectName(QStringLiteral("from"));

        gridLayout_6->addWidget(from, 5, 3, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_9, 6, 0, 1, 1);

        to = new QLineEdit(layoutWidget);
        to->setObjectName(QStringLiteral("to"));

        gridLayout_6->addWidget(to, 6, 3, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_6->addWidget(label_10, 7, 0, 1, 3);

        noofpoints = new QLineEdit(layoutWidget);
        noofpoints->setObjectName(QStringLiteral("noofpoints"));

        gridLayout_6->addWidget(noofpoints, 7, 3, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_6->addWidget(label_7, 2, 0, 1, 1);

        parameter = new QComboBox(layoutWidget);
        parameter->setObjectName(QStringLiteral("parameter"));
        parameter->setFrame(true);

        gridLayout_6->addWidget(parameter, 2, 3, 1, 1);

        singlemode = new QCheckBox(layoutWidget);
        singlemode->setObjectName(QStringLiteral("singlemode"));

        gridLayout_6->addWidget(singlemode, 0, 3, 1, 1);

        rangemode = new QCheckBox(layoutWidget);
        rangemode->setObjectName(QStringLiteral("rangemode"));

        gridLayout_6->addWidget(rangemode, 1, 3, 1, 1);


        gridLayout_8->addLayout(gridLayout_6, 4, 0, 1, 1);

        Runbutton = new QPushButton(layoutWidget);
        Runbutton->setObjectName(QStringLiteral("Runbutton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Runbutton->sizePolicy().hasHeightForWidth());
        Runbutton->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(Runbutton, 6, 1, 1, 2);

        Information = new QTextEdit(layoutWidget);
        Information->setObjectName(QStringLiteral("Information"));

        gridLayout_8->addWidget(Information, 6, 0, 1, 1);

        Resultsplot_2 = new QCustomPlot(layoutWidget);
        Resultsplot_2->setObjectName(QStringLiteral("Resultsplot_2"));
        Resultsplot_2->setMinimumSize(QSize(465, 300));

        gridLayout_8->addWidget(Resultsplot_2, 1, 1, 1, 1);

        Resultstable = new QTableWidget(layoutWidget);
        Resultstable->setObjectName(QStringLiteral("Resultstable"));

        gridLayout_8->addWidget(Resultstable, 4, 1, 1, 2);

        guimain->setCentralWidget(centralwidget);
        menubar = new QMenuBar(guimain);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1452, 22));
        menuARCPlan = new QMenu(menubar);
        menuARCPlan->setObjectName(QStringLiteral("menuARCPlan"));
        guimain->setMenuBar(menubar);
        statusBar = new QStatusBar(guimain);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        guimain->setStatusBar(statusBar);

        menubar->addAction(menuARCPlan->menuAction());

        retranslateUi(guimain);

        tabs->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(guimain);
    } // setupUi

    void retranslateUi(QMainWindow *guimain)
    {
        guimain->setWindowTitle(QApplication::translate("guimain", "MainWindow", 0));
        Save->setText(QApplication::translate("guimain", "Save Results", 0));
        label_23->setText(QApplication::translate("guimain", "Results", 0));
        label_22->setText(QApplication::translate("guimain", "Crack Profiles", 0));
        PipeID->setText(QApplication::translate("guimain", "Name/ID:", 0));
        Density->setText(QApplication::translate("guimain", "Density:", 0));
        DynamicModulus->setText(QApplication::translate("guimain", "Dynamic Modulus at 0\302\260C:", 0));
        DDynamicModulus->setText(QApplication::translate("guimain", "Increase in dynamic modulus at 0\302\260C:", 0));
        Creepmodulus->setText(QApplication::translate("guimain", "Creep modulus at room temperature:", 0));
        Poissonratio->setText(QApplication::translate("guimain", "Dynamic poisson ratio:", 0));
        tabs->setTabText(tabs->indexOf(tab), QApplication::translate("guimain", "Pipe Material", 0));
        PipeID_2->setText(QApplication::translate("guimain", "Pipe name/ID:", 0));
        PipeID_5->setText(QApplication::translate("guimain", "Outside pipe diameter:", 0));
        PipeID_6->setText(QApplication::translate("guimain", "SDR (Pipe diameter/ Wall thickness): ", 0));
        PipeID_7->setText(QApplication::translate("guimain", "Internal or external sidegroove depth: ", 0));
        PipeID_8->setText(QApplication::translate("guimain", "Relative diameter after residual strain creep: ", 0));
        tabs->setTabText(tabs->indexOf(tab_2), QApplication::translate("guimain", "Pipe Geometry", 0));
        label_12->setText(QApplication::translate("guimain", "FS with prior decompression:", 0));
        fs->setText(QString());
        label_13->setText(QApplication::translate("guimain", "S4:", 0));
        s4->setText(QString());
        label_11->setText(QApplication::translate("guimain", "Backfill", 0));
        PipeID_9->setText(QApplication::translate("guimain", "Test temperature", 0));
        PipeID_10->setText(QApplication::translate("guimain", "Initial Test Pressure: ", 0));
        PipeID_11->setText(QApplication::translate("guimain", "Backfill Depth:", 0));
        PipeID_12->setText(QApplication::translate("guimain", "Backfill Density: ", 0));
        PipeID_13->setText(QApplication::translate("guimain", "Volumetric fraction of rigid solids within pipe:", 0));
        PipeID_14->setText(QApplication::translate("guimain", "Volumetric fraction of water within pipe:", 0));
        backfill->setText(QString());
        tabs->setTabText(tabs->indexOf(tab_3), QApplication::translate("guimain", "Test Setup", 0));
        label_14->setText(QApplication::translate("guimain", "Outflow model:", 0));
        PipeID_15->setText(QApplication::translate("guimain", "Initial Outflow length: ", 0));
        PipeID_16->setText(QApplication::translate("guimain", "Crack speed:", 0));
        PipeID_17->setText(QApplication::translate("guimain", "Number of FD elements: ", 0));
        fixedlength->setText(QString());
        tabs->setTabText(tabs->indexOf(tab_4), QApplication::translate("guimain", "Control", 0));
        label_3->setText(QApplication::translate("guimain", "Save results to:", 0));
        label_2->setText(QApplication::translate("guimain", "Single Shot:", 0));
        label->setText(QApplication::translate("guimain", "Range:", 0));
        label_8->setText(QApplication::translate("guimain", "From:", 0));
        label_9->setText(QApplication::translate("guimain", "To:", 0));
        label_10->setText(QApplication::translate("guimain", "No. of Points:", 0));
        label_7->setText(QApplication::translate("guimain", "Parameter:", 0));
        singlemode->setText(QString());
        rangemode->setText(QString());
        Runbutton->setText(QApplication::translate("guimain", "Run", 0));
        menuARCPlan->setTitle(QApplication::translate("guimain", "aRCPlan", 0));
    } // retranslateUi

};

namespace Ui {
    class guimain: public Ui_guimain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIMAIN_H
