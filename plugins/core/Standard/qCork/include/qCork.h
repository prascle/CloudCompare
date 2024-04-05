//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: qCork                       #
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
//#                  COPYRIGHT: Daniel Girardeau-Montaut                   #
//#                                                                        #
//##########################################################################

#ifndef Q_CORK_PLUGIN_HEADER
#define Q_CORK_PLUGIN_HEADER

//Qt
#include <QObject>

#include "ccStdPluginInterface.h"
#include "qCorkExport.h"
#include <ccMesh.h>

class QAction;

//! Mes Boolean Operations (CSG) plugin
/** This plugin is based on Cork: https://github.com/gilbo/cork
	Required implementation is CC's dedicated fork: https://github.com/cloudcompare/cork
**/
class QCORK_PLUGIN_LIB_API qCork : public QObject, public ccStdPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( ccPluginInterface ccStdPluginInterface )

	Q_PLUGIN_METADATA( IID "cccorp.cloudcompare.plugin.qCork" FILE "../info.json" )

public:

	//! Default constructor
	explicit qCork(QObject* parent = nullptr);

	//inherited from ccStdPluginInterface
	virtual void onNewSelection(const ccHObject::Container& selectedEntities);
	virtual QList<QAction *> getActions() override;

    enum CSG_OPERATION { UNION, INTERSECT, DIFF, SYM_DIFF };
	static ccMesh* compute(ccMesh* meshA, ccMesh* meshB, CSG_OPERATION operation);

protected:

	//! Starts main action
	void doAction();

protected:

	//! Associated action
	QAction* m_action;
};

#endif //Q_CORK_PLUGIN_HEADER
