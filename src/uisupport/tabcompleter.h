/***************************************************************************
 *   Copyright (C) 2005/06 by the Quassel Project                          *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _TABCOMPLETER_H_
#define _TABCOMPLETER_H_

#include <QObject>
#include <QStringList>
#include <QPointer>

class InputLine;
class IrcUser;

class TabCompleter : public QObject {
  Q_OBJECT
  
public:
  TabCompleter(InputLine *inputLine_);
  
  void reset();
  void complete();

  virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
  void ircUserJoinedOrParted(IrcUser *ircUser);
  
private:
  QPointer<InputLine> inputLine;
  bool enabled;
  QString nickSuffix;

  QStringList completionList;
  // QStringList completionTemplates;
  
  QStringList::Iterator nextCompletion;
  int lastCompletionLength;
  
  void buildCompletionList();
  
};

#endif
