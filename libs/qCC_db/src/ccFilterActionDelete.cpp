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

#include "ccFilterActionDelete.h"

#include <QApplication>
#include <QWidgetList>
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QEvent>

// on macos, <Fn> <Backspace> deletes the selected entities instead of the current character

filterActionDelete* filterActionDelete::instance =nullptr;

filterActionDelete* filterActionDelete::getFilterActionDelete()
{
	if (filterActionDelete::instance == nullptr)
	{
		filterActionDelete::instance = new filterActionDelete();
	}
	return filterActionDelete::instance;
}

filterActionDelete::filterActionDelete():
		m_mainApp(nullptr)
{
	QWidgetList topWidgets = QApplication::topLevelWidgets();
	for(QWidget* widget : topWidgets)
	{
		QString title = widget->windowTitle();
		if (title.startsWith("CloudCompare v"))
		{
			m_mainApp = widget;
		}
	}
}

void filterActionDelete::disableActionDelete()
{
	if (m_mainApp != nullptr)
	{
		disableADEvent myEvent = disableADEvent();
		m_mainApp->installEventFilter(m_mainApp);
		QApplication::sendEvent(m_mainApp, &myEvent);
	}
}

void filterActionDelete::enableActionDelete()
{
	if (m_mainApp != nullptr)
	{
		enableADEvent myEvent = enableADEvent();
		QApplication::sendEvent(m_mainApp, &myEvent);
	}
}
