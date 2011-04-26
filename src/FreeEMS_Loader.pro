TEMPLATE = app
TARGET = FreeEMS_Loader
QMAKE_CXXFLAGS *= -Wall
QMAKE_CXXFLAGS *= -Werror
    
CONFIG *= qt \
    warn_on \
    release \
    debug 
QT *= core \
    gui \
    xml \
    xmlpatterns \
    network \
    opengl
HEADERS += about.h \
    FreeEMS_LoaderThreads.h \
    FreeEMS_LoaderParsing.h \
    FreeEMS_LoaderComms.h \
    FreeEMS_LoaderSREC.h \
    freeems_LoaderRedirector.h \
    freeems_loader.h \
    FreeEMS_LoaderSREC.h \
    freeems_LoaderRedirector.h \
    freeems_loader_types.h \
    FreeEMS_LoaderComms.h \
    freeems_loader.h \
    freeems_loader.h \
    freeems_loader.h
SOURCES += about.cpp \
    FreeEMS_LoaderThreads.cpp \
    freeems_loader_types.cpp \
    FreeEMS_LoaderParsing.cpp \
    FreeEMS_LoaderSREC.cpp \
    FreeEMS_LoaderComms.cpp \
    freeems_loader.cpp \
    main.cpp
FORMS *= about.ui \
    freeems_loader.ui
RESOURCES += resource-root.qrc
# Cross compilation
win32-x-g++ {
	message("Crosscompiling on Unix to Windows")
	unix:INCLUDEPATH *= /opt/crossroot/boost/include/ 
	unix:LIBS *= -lboost_system-mt \
	   -L/opt/crossroot/boost/lib
	QMAKE_CXXFLAGS -= -Werror
}
mac {
# Straight Mac-OS (OS-X)
	message("Mac OS-X Build")
	unix:INCLUDEPATH *= /opt/local/include
	unix:LIBS *= -L/opt/local/lib -lboost_system-mt
} 
linux-g++ {
# Straight Linux 
	message("Linux Build")
	unix:INCLUDEPATH *= /usr/local/qserialport/include/QtSerialPort/
	unix:LIBS *= -lboost_system -lQtSerialPort
} 
win32 {
	message("Straight compile on windows (seank only)")
	win32:INCLUDEPATH *= $$quote(C:/boost/include/boost-1_45)
	win32:LIBS *= -LC:/boost/lib \
		-lboost_system-mgw44-mt-1_45 \
		-Lc:/mingw/lib \
		-lwsock32
}
