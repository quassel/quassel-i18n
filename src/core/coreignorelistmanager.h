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

#include "ignorelistmanager.h"

class CoreSession;
struct RawMessage;

class CoreIgnoreListManager : public IgnoreListManager
{
    Q_OBJECT

public:
    explicit CoreIgnoreListManager(CoreSession* parent);

    StrictnessType match(const RawMessage& rawMsg, const QString& networkName);

public slots:
    inline void requestToggleIgnoreRule(const QString& ignoreRule) override { toggleIgnoreRule(ignoreRule); }
    inline void requestRemoveIgnoreListItem(const QString& ignoreRule) override { removeIgnoreListItem(ignoreRule); }
    inline void requestAddIgnoreListItem(
        int type, const QString& ignoreRule, bool isRegEx, int strictness, int scope, const QString& scopeRule, bool isActive) override
    {
        addIgnoreListItem(type, ignoreRule, isRegEx, strictness, scope, scopeRule, isActive);
    }

private slots:
    void save() const;

    // private:
    //  void loadDefaults();
};
