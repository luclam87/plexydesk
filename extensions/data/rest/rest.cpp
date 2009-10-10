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
#include "rest.h"
#include <desktopwidget.h>
#include <plexyconfig.h>
#include <QNetworkAccessManager>

#define POST 0
#define GET 1

class RestData::Private
{
    public:
        Private() {}
        ~Private() {}
        QNetworkAccessManager * manager;
        QString user;
        QString pass;
};

RestData::RestData(QObject * object):d(new Private)
{
}

void  RestData::init()
{
   d->manager = new QNetworkAccessManager(this);
   connect(d->manager, SIGNAL(finished(QNetworkReply*)),
           this, SLOT(replyFinished(QNetworkReply*)));
   connect(d->manager, SIGNAL(authenticationRequired (QNetworkReply *, QAuthenticator *)), this,
          SLOT(handleAuth(QNetworkReply *, QAuthenticator *))); 

}

RestData::~RestData()
{
    delete d;
}

void RestData::pushData(QVariantMap& param)
{
    if (!d->manager) {
        init();
    }

    QUrl url = param["url"].toUrl();
    int type = param["type"].toInt();
    QString par = param["params"].toString();
    d->user = param["user"].toString();
    d->pass = param["pass"].toString();

    if (type == GET) {
       d->manager->get(QNetworkRequest(url)); 
    } else if (type == POST) {
        d->manager->post(QNetworkRequest(url), par.toAscii());
    }
    //TODO 
    //handle errors
}

void RestData::replyFinished(QNetworkReply* reply)
{
     QVariantMap response;
     response["data"] = QVariant(reply->readAll());
     Q_EMIT data(response);
}

void RestData::handleAuth(QNetworkReply * r, QAuthenticator * auth)
{
    qDebug() << Q_FUNC_INFO ;

    auth->setUser(d->user);
    auth->setPassword(d->pass);
}
