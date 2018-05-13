#-------------------------------------------------
#
# Project created by QtCreator 2010-11-07T16:51:06
#
#-------------------------------------------------

QT       += core gui network

TARGET = AstrologyToolkit
#TARGET = astroqt1
TEMPLATE = app

ICON = moon400.svg

SOURCES += main.cpp\
        mainwindow.cpp \
    cpp_core/astrodefs.cpp \
    hwqt/hwqwertyinput.cpp \
    hwqt/hwcomboinput.cpp \
    cpp_core/timezoneinfo.cpp \
    cpp_core/house_calc.cpp \
    cpp_core/geodata.cpp \
    astrochart.cpp \
    hwqt/qhwsearchselector.cpp \
    hwqt/qhwstackedframe.cpp \
    qhwchartview.cpp \
    #cpp_core/hwxfilereader.cpp \
    cpp_core/mytest.c \
    mychartinput.cpp \
    mylistselect.cpp \
    qhwastrochartview.cpp \
    hwqt/qhwdatechooser.cpp \
    hwqt/qhwtimechooser.cpp \
    infoframe.cpp \
    qhwastroscene.cpp \
    mychartopendialog.cpp \
    hwqt/qhwlistwidget.cpp \
    hwqt/qhwlistselect.cpp \
    downloaddialog.cpp \
    mychartopenwindow.cpp \
    hwqt/qhwlatlongchooser.cpp

HEADERS  += mainwindow.h \
    cpp_core/astrodefs.h \
    hwqt/hwqwertyinput.h \
    hwqt/hwcomboinput.h \
    cpp_core/timezoneinfo.h \
    cpp_core/house_calc.h \
    cpp_core/geodata.h \
    astrochart.h \
    hwqt/qhwsearchselector.h \
    hwqt/qhwstackedframe.h \
    qhwchartview.h \
    #cpp_core/hwxfilereader.h \
    mychartinput.h \
    mylistselect.h \
    qhwastrochartview.h \
    cpp_core/timezonedefaults.h \
    hwqt/qhwdatechooser.h \
    hwqt/qhwtimechooser.h \
    infoframe.h \
    qhwastroscene.h \
    mychartopendialog.h \
    hwqt/qhwlistwidget.h \
    hwqt/qhwlistselect.h \
    downloaddialog.h \
    mychartopenwindow.h \
    hwqt/qhwlatlongchooser.h

FORMS    += mainwindow.ui \
    hwqt/hwqwertyinput.ui \
    hwqt/hwcomboinput.ui \
    hwqt/qhwsearchselector.ui \
    qhwchartview.ui \
    mylistselect.ui \
    hwqt/qhwdatechooser.ui \
    hwqt/qhwtimechooser.ui \
    infoframe.ui \
    mychartopendialog.ui \
    hwqt/qhwlatlongchooser.ui

CONFIG += mobility
MOBILITY += location

VERSION = 1.0.1

symbian {
    # Adding vendor name as per http://developer.symbian.org/wiki/Deploying_a_Qt_Application
    vendorinfo = \
    "%{\"Leaping Light c/o Roy Andre Gundersen\"}"\
    ":\"Leaping Light c/o Roy Andre Gundersen\"

    # Remove all the existing platform dependencies
    default_deployment.pkg_prerules -= pkg_platform_dependencies

    supported_platforms = \
    "; supports S60 5th edition and sym3 and sym4" \
    "[0x1028315F],0,0,0,{\"S60ProductID\"}" \
    "[0x20022e6d],0,0,0,{\"S60ProductID\"}" \
    "[0x20032de7],0,0,0,{\"S60ProductID\"}" \

    my_deployment.pkg_prerules += vendorinfo
    my_deployment.pkg_prerules += supported_platforms
    DEPLOYMENT += my_deployment

    # Test:
    # TARGET.UID3 = 0xe25501c1
    Release:
    TARGET.UID3 = 0x20042303
    TARGET.CAPABILITY += UserEnvironment NetworkServices Location ReadUserData
    # TARGET.CAPABILITY += WriteUserData
    # Need SwEvent to open a URL in an allready open WebBrowser:
    TARGET.CAPABILITY += SwEvent
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0xF00000 0x1F00000

    addFiles.sources = astrodata\ef2\*.ef2 astrodata\geodata\geodata.dat astrodata\tz\tzall.dat
    # addFiles.sources = astrodata\ef2\2010.ef2 astrodata\ef2\2011.ef2 astrodata\ef2\2012.ef2
    DEPLOYMENT += addFiles
}

RESOURCES += \
    astrodata.qrc \
    astrogfx.qrc \
    style.qrc \
    gfx.qrc

OTHER_FILES += \
    style/style.qss
