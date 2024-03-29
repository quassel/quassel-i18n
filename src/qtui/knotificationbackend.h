/***************************************************************************
 *   Copyright (C) 2005-2022 by the Quassel Project                        *
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

#pragma once

#include <QPointer>

#include "abstractnotificationbackend.h"
#include "settingspage.h"
#include "systemtray.h"

class KNotification;
class KNotifyConfigWidget;

class KNotificationBackend : public AbstractNotificationBackend
{
    Q_OBJECT

public:
    KNotificationBackend(QObject* parent = nullptr);

    void notify(const Notification&) override;
    void close(uint notificationId) override;
    SettingsPage* createConfigWidget() const override;

private slots:
    void notificationActivated();
    void notificationActivated(SystemTray::ActivationReason);
    void notificationActivated(uint notificationId);

private:
    class ConfigWidget;

    void removeNotificationById(uint id);
    void updateToolTip();

    QList<QPair<uint, QPointer<KNotification>>> _notifications;
};

class KNotificationBackend::ConfigWidget : public SettingsPage
{
    Q_OBJECT

public:
    ConfigWidget(QWidget* parent = nullptr);

    void save() override;
    void load() override;

private slots:
    void widgetChanged(bool);

private:
    KNotifyConfigWidget* _widget;
};
