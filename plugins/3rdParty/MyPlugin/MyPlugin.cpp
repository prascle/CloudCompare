//##########################################################################
//#                                                                        #
//#                CLOUDCOMPARE PLUGIN: MyPlugin                      #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                             COPYRIGHT: XXX                             #
//#                                                                        #
//##########################################################################

// First:
//	Replace all occurrences of 'MyPlugin' by your own plugin class name in this file.
//	This includes the resource path to info.json in the constructor.

// Second:
//	Open MyPlugin.qrc, change the "prefix" and the icon filename for your plugin.
//	Change the name of the file to <yourPluginName>.qrc

// Third:
//	Open the info.json file and fill in the information about the plugin.
//	 "type" should be one of: "Standard", "GL", or "I/O" (required)
//	 "name" is the name of the plugin (required)
//	 "icon" is the Qt resource path to the plugin's icon (from the .qrc file)
//	 "description" is used as a tootip if the plugin has actions and is displayed in the plugin dialog
//	 "authors", "maintainers", and "references" show up in the plugin dialog as well

#include <QtGui>
#include <QInputDialog>
#include <QMainWindow>
#include <ccPointCloud.h>
#include <ccPolyline.h>
#include "Chaikin.cpp"
#include "qMyPluginCommands.h"

//ccPolyline* SmoothChaikin(const ccPolyline& inputPolyline, PointCoordinateType ratio, unsigned iterations);

#include "MyPlugin.h"

// Default constructor:
//	- pass the Qt resource path to the info.json file (from <yourPluginName>.qrc file) 
//  - constructor should mainly be used to initialize actions and other members
MyPlugin::MyPlugin( QObject *parent )
	: QObject( parent )
	, ccStdPluginInterface( ":/CC/plugin/MyPlugin/info.json" )
	, m_action( nullptr )
{
}

// This method should enable or disable your plugin actions
// depending on the currently selected entities ('selectedEntities').
void MyPlugin::onNewSelection( const ccHObject::Container &selectedEntities )
{
	if ( m_action == nullptr )
	{
		return;
	}
	
	// If you need to check for a specific type of object, you can use the methods
	// in ccHObjectCaster.h or loop and check the objects' classIDs like this:
	//
	//	for ( ccHObject *object : selectedEntities )
	//	{
	//		if ( object->getClassID() == CC_TYPES::VIEWPORT_2D_OBJECT )
	//		{
	//			// ... do something with the viewports
	//		}
	//	}
	
	// For example - only enable our action if something is selected.
	m_action->setEnabled( !selectedEntities.empty() );
}

// This method returns all the 'actions' your plugin can perform.
// getActions() will be called only once, when plugin is loaded.
QList<QAction *> MyPlugin::getActions()
{
	// default action (if it has not been already created, this is the moment to do it)
	if ( !m_action )
	{
		// Here we use the default plugin name, description, and icon,
		// but each action should have its own.
		m_action = new QAction( getName(), this );
		m_action->setToolTip( getDescription() );
		m_action->setIcon( getIcon() );
		
		// Connect appropriate signal
		connect( m_action, &QAction::triggered, this, &MyPlugin::doAction );
	}

	return { m_action };
}

// This is an example of an action's method called when the corresponding action
// is triggered (i.e. the corresponding icon or menu entry is clicked in CC's
// main interface). You can access most of CC's components (database,
// 3D views, console, etc.) via the 'm_app' variable (see the ccMainAppInterface
// class in ccMainAppInterface.h).
void MyPlugin::doAction()
{	
	if ( m_app == nullptr )
	{
		// m_app should have already been initialized by CC when plugin is loaded
		Q_ASSERT( false );
		
		return;
	}

	const ccHObject::Container& selectedEntities = getMainAppInterface()->getSelectedEntities();
	if (selectedEntities.size() != 1 || !selectedEntities.front()->isA(CC_TYPES::POLY_LINE))
		{
			return;
		}

		ccPolyline* polyline = ccHObjectCaster::ToPolyline(selectedEntities.front());
	if (nullptr == polyline)
	{
		assert(false);
		return;
	}
	bool ok = false;
	int iterationCount = QInputDialog::getInt(getMainAppInterface()->getMainWindow(),"Chaikin", "Iterations", 5, 1, 100, 1, &ok);
	if (!ok)
	{
		return;
	}
	ccPolyline* smoothPoly = SmoothChaikin(*polyline, 0.25, iterationCount);
	if (nullptr == smoothPoly)
	{
		ccLog::Error("algorithm failed");
		return;
	}
	
	getMainAppInterface()->addToDB(smoothPoly);

}

void MyPLugin::registerCommands(ccCommandInterface* cmd)
{
	cmd->registerCommand(ccCommandLineInterface::command::shared(new CommandCHAIKIN));
}




