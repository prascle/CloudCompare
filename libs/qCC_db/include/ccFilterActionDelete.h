//##########################################################################
//#                                                                        #
//#                              CLOUDCOMPARE                              #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 or later of the License.      #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################

#pragma once

#include <QWidget>
#include <QEvent>

#define indexDAD 9723
#define indexEAD 9724

// on macos, <Fn> <Backspace> deletes the selected entities instead of the current character

class disableADEvent : public QEvent
{
public:
    static const QEvent::Type disableADEventType = static_cast<QEvent::Type>(QEvent::User + indexDAD);

    disableADEvent() : QEvent(disableADEventType) {}
};


class enableADEvent : public QEvent
{
public:
    static const QEvent::Type enableADEventType = static_cast<QEvent::Type>(QEvent::User + indexEAD);

    enableADEvent() : QEvent(enableADEventType) {}
};


class filterActionDelete
{
public:

	static filterActionDelete* getFilterActionDelete();

	void disableActionDelete();

	void enableActionDelete();

protected:
	filterActionDelete();

	static filterActionDelete* instance;

	QWidget* m_mainApp;
};
