/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qdeclarative.h>
#include "qstyleplugin.h"
#include "qstyleitem.h"
#include "qrangemodel.h"
#include "qtmenu.h"
#include "qtmenubar.h"
#include "qwindowitem.h"
#include "qdesktopitem.h"
#include "qwheelarea.h"
#include "qcursorarea.h"
#include "qtooltiparea.h"
#include "qtsplitterbase.h"
#include "qdeclarativelinearlayout.h"
#include <qdeclarativeextensionplugin.h>
#include "settings.h"

#include <qdeclarativeengine.h>
#include <qdeclarative.h>
#include <qdeclarativeitem.h>
#include <qdeclarativeimageprovider.h>
#include <qdeclarativeview.h>
#include <QApplication>
#include <QImage>

// Load icons from desktop theme
class DesktopIconProvider : public QDeclarativeImageProvider
{
public:
    DesktopIconProvider()
        : QDeclarativeImageProvider(QDeclarativeImageProvider::Pixmap)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
    {
        Q_UNUSED(requestedSize);
        Q_UNUSED(size);
        int pos = id.lastIndexOf('/');
        QString iconName = id.right(id.length() - pos);
        int width = requestedSize.width();
        return QIcon::fromTheme(iconName).pixmap(width);
    }
};


void StylePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<QStyleItem>(uri, 0, 1, "StyleItem");
    qmlRegisterType<QCursorArea>(uri, 0, 1, "CursorArea");
    qmlRegisterType<QTooltipArea>(uri, 0, 1, "TooltipArea");
    qmlRegisterType<QRangeModel>(uri, 0, 1, "RangeModel");
    qmlRegisterType<QWheelArea>(uri, 0, 1, "WheelArea");

    qmlRegisterType<QtMenu>(uri, 0, 1, "Menu");
    qmlRegisterType<QtMenuBar>(uri, 0, 1, "MenuBar");
    qmlRegisterType<QtMenuItem>(uri, 0, 1, "MenuItem");
    qmlRegisterType<QtMenuSeparator>(uri, 0, 1, "Separator");

    qmlRegisterType<QFileSystemModel>(uri, 0, 1, "FileSystemModel");
    qmlRegisterType<QtSplitterBase>(uri, 0, 1, "Splitter");
    qmlRegisterType<Settings>(uri, 0, 1, "Settings");
    qmlRegisterType<QWindowItem>("QtQuick", 0, 1, "Window");

    qmlRegisterUncreatableType<QtMenuBase>("uri", 0, 1, "NativeMenuBase", QLatin1String("Do not create objects of type NativeMenuBase"));
    qmlRegisterType<QDeclarativeRowLayout>(uri, 0, 1, "RowLayout");
    qmlRegisterType<QDeclarativeColumnLayout>(uri, 0, 1, "ColumnLayout");
    qmlRegisterUncreatableType<QDeclarativeLayout>(uri, 0, 1, "Layout",
                                                   QLatin1String("Do not create objects of type Layout"));
    qmlRegisterUncreatableType<QDesktopItem>("QtQuick",1,1,"Desktop", QLatin1String("Do not create objects of type Desktop"));
}

void StylePlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    engine->addImageProvider("desktoptheme", new DesktopIconProvider);
}

Q_EXPORT_PLUGIN2(styleplugin, StylePlugin);
