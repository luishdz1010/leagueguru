# Add more folders to ship with the application, here
folder_01.source = qml/TeamComp
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
QMAKE_CXXFLAGS += -std=gnu++11 -Wall

QT += core gui network webkit declarative
TARGET = leagueguru
CONFIG += windows warn_on exceptions rtti resources
win32:RC_FILE += resources/icon.rc

LIBS += -lprotobuf

SOURCES += main.cpp \
    championselectcontroller.cpp \
    gamepacketinspector.cpp \
    processinjector.cpp \
    rtmpdecoder.cpp \
    amfreader.cpp \
    amfexternalizableobjectmap.cpp \
    basicexternalizablemessage.cpp \
    asyncexternalizablemessage.cpp \
    acknowledgeexternalizablemessage.cpp \
    debugamf.cpp \
    summonerstats.cpp \
    summonerstatsprovider.cpp \
    clientemulator.cpp \
    guruserver.cpp \
    guru/matchupinfo.pb.cc \
    guru/packet.pb.cc \
    guru/logincredentials.pb.cc \
    guru/matchupcreated.pb.cc \
    guru/bansuggestions.pb.cc \
    guru/participantstartspicking.pb.cc \
    guru/participantssuggestions.pb.cc \
    guru/participantspells.pb.cc \
    guru/participantrole.pb.cc \
    guru/participantchampion.pb.cc \
    guru/lockparticipant.pb.cc \
    guru/enemyroster.pb.cc \
    guru/championban.pb.cc \
    clientemulatorwindow.cpp \
    championdata.cpp \
    championfiltermodel.cpp \
    enums.cpp \
    rosterfiltermodel.cpp \
    suggestionsfildermodel.cpp \
    suggestionmodelpickfilter.cpp \
    qmlkeynavigationfix.cpp \
    processwatcher.cpp \
    dataupdater.cpp \
    filepaths.cpp \
    bootstrap.cpp \
    dataupdateview.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    championselectcontroller.h \
    enemyrostermodel.h \
    gamepacketinspector.h \
    processinjector.h \
    rtmpdecoder.h \
    amfreader.h \
    amfexternalizableobjectmap.h \
    basicexternalizablemessage.h \
    asyncexternalizablemessage.h \
    acknowledgeexternalizablemessage.h \
    debugamf.h \
    basicitemmodel.hpp \
    matchparticipantmodel.hpp \
    summonerstats.h \
    summonerstatsprovider.h \
    clientemulator.h \
    guruserver.h \
    guru/matchupinfo.pb.h \
    guru/packet.pb.h\
    guru/logincredentials.pb.h\
    guru/matchupcreated.pb.h\
    guru/bansuggestions.pb.h\
    guru/participantstartspicking.pb.h \
    guru/participantssuggestions.pb.h \
    guru/participantspells.pb.h \
    guru/participantrole.pb.h \
    guru/participantchampion.pb.h \
    guru/lockparticipant.pb.h \
    guru/enemyroster.pb.h \
    guru/championban.pb.h \
    clientemulatorwindow.h \
    participantsuggestionsmodel.h \
    bansuggestionsmodel.h \
    championdata.h \
    championfiltermodel.h \
    enums.h \
    participantrostermodel.hpp \
    rosterfiltermodel.h \
    suggestionsfildermodel.h \
    suggestionmodelpickfilter.h \
    qmlkeynavigationfix.h \
    processwatcher.h \
    dataupdater.h \
    filepaths.h \
    bootstrap.h \
    dataupdateview.h

RESOURCES += \
   resources/application.qrc

FORMS += \
    clientemulatorwindow.ui \
    dataupdateview.ui

include(qslog/QsLog.pri)
