/*******************************************************************************
* This file is part of PlexyDesk.
*  Maintained by : Siraj Razick <siraj@kde.org>
*  Authored By  :
*
*  PlexyDesk is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  PlexyDesk is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with PlexyDesk. If not, see <http://www.gnu.org/licenses/lgpl.html>
*******************************************************************************/

#include <QDir>
#include <QPixmapCache>
#include <QDeclarativeContext>
#include "desktopview.h"

#include <QtDebug>

#include "desktopviewimpl.h"
#include <desktopwidget.h>
#include <plexyconfig.h>


DesktopViewPluginImpl::DesktopViewPluginImpl(QObject *object)
    : DesktopViewPlugin(object)
{
}

DesktopViewPluginImpl::~DesktopViewPluginImpl()
{
    qDeleteAll(mViewList.begin(), mViewList.end());
    mViewList.clear();
}

void  DesktopViewPluginImpl::setRect(const QRect &rect)
{
}

PlexyDesk::AbstractDesktopView  *DesktopViewPluginImpl::view(QGraphicsScene *scene)
{
    DesktopView *view = new DesktopView(scene);
    view->addWallpaperItem();
    view->setThemePack(PlexyDesk::Config::getInstance()->themepackName());
    view->registerPhotoDialog();
    mViewList.append(view);
    return view;
}
