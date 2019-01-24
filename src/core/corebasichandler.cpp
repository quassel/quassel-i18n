/***************************************************************************
 *   Copyright (C) 2005-2019 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "corebasichandler.h"

#include "util.h"

CoreBasicHandler::CoreBasicHandler(CoreNetwork* parent)
    : BasicHandler(parent)
    , _network(parent)
{
    connect(this, &CoreBasicHandler::displayMsg, network(), &CoreNetwork::onDisplayMsg);
    connect(this, &CoreBasicHandler::putRawLine, network(), &CoreNetwork::putRawLine);
    connect(this,
            selectOverload<const QString&, const QList<QByteArray>&, const QByteArray&, bool>(&CoreBasicHandler::putCmd),
            network(),
            selectOverload<const QString&, const QList<QByteArray>&, const QByteArray&, bool>(&CoreNetwork::putCmd));
    connect(this,
            selectOverload<const QString&, const QList<QList<QByteArray>>&, const QByteArray&, bool>(&CoreBasicHandler::putCmd),
            network(),
            selectOverload<const QString&, const QList<QList<QByteArray>>&, const QByteArray&, bool>(&CoreNetwork::putCmd));
}

QString CoreBasicHandler::serverDecode(const QByteArray& string)
{
    return network()->serverDecode(string);
}

QStringList CoreBasicHandler::serverDecode(const QList<QByteArray>& stringlist)
{
    QStringList list;
    foreach (QByteArray s, stringlist)
        list << network()->serverDecode(s);
    return list;
}

QString CoreBasicHandler::channelDecode(const QString& bufferName, const QByteArray& string)
{
    return network()->channelDecode(bufferName, string);
}

QStringList CoreBasicHandler::channelDecode(const QString& bufferName, const QList<QByteArray>& stringlist)
{
    QStringList list;
    foreach (QByteArray s, stringlist)
        list << network()->channelDecode(bufferName, s);
    return list;
}

QString CoreBasicHandler::userDecode(const QString& userNick, const QByteArray& string)
{
    return network()->userDecode(userNick, string);
}

QStringList CoreBasicHandler::userDecode(const QString& userNick, const QList<QByteArray>& stringlist)
{
    QStringList list;
    foreach (QByteArray s, stringlist)
        list << network()->userDecode(userNick, s);
    return list;
}

/*** ***/

QByteArray CoreBasicHandler::serverEncode(const QString& string)
{
    return network()->serverEncode(string);
}

QList<QByteArray> CoreBasicHandler::serverEncode(const QStringList& stringlist)
{
    QList<QByteArray> list;
    foreach (QString s, stringlist)
        list << network()->serverEncode(s);
    return list;
}

QByteArray CoreBasicHandler::channelEncode(const QString& bufferName, const QString& string)
{
    return network()->channelEncode(bufferName, string);
}

QList<QByteArray> CoreBasicHandler::channelEncode(const QString& bufferName, const QStringList& stringlist)
{
    QList<QByteArray> list;
    foreach (QString s, stringlist)
        list << network()->channelEncode(bufferName, s);
    return list;
}

QByteArray CoreBasicHandler::userEncode(const QString& userNick, const QString& string)
{
    return network()->userEncode(userNick, string);
}

QList<QByteArray> CoreBasicHandler::userEncode(const QString& userNick, const QStringList& stringlist)
{
    QList<QByteArray> list;
    foreach (QString s, stringlist)
        list << network()->userEncode(userNick, s);
    return list;
}

// ====================
//  protected:
// ====================
BufferInfo::Type CoreBasicHandler::typeByTarget(const QString& target) const
{
    if (target.isEmpty())
        return BufferInfo::StatusBuffer;

    if (network()->isChannelName(target))
        return BufferInfo::ChannelBuffer;

    return BufferInfo::QueryBuffer;
}

void CoreBasicHandler::putCmd(const QString& cmd, const QByteArray& param, const QByteArray& prefix, const bool prepend)
{
    QList<QByteArray> list;
    list << param;
    emit putCmd(cmd, list, prefix, prepend);
}
