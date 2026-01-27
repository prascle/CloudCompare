#pragma once

//##########################################################################
//#                                                                        #
//#                   CLOUDCOMPARE PLUGIN: qMeshBoolean                    #
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

#include "qMeshBooleanExport.h"

//Qt
#include <QObject>

#include "ccStdPluginInterface.h"

class QAction;

//libIGL
//#include <igl/all.h>
#include <igl/copyleft/cgal/mesh_boolean.h>

//! ligIGL mesh
struct IGLMesh
{
    Eigen::MatrixXd V; //!< Vertices
    Eigen::MatrixXi F; //!< Triangles
};

//! Supported CSG operations
enum CSG_OPERATION { UNION, INTERSECT, DIFF, SYM_DIFF };

//! Boolean operation parameters (for concurrent run)
struct BoolOpParameters
{
    CSG_OPERATION operation = CSG_OPERATION::UNION;
    IGLMesh* meshA = nullptr;
    IGLMesh* meshB = nullptr;
    IGLMesh output;
    QString nameA;
    QString nameB;
    ccMainAppInterface* app = nullptr;
};

bool ToIGLMesh(const ccMesh* in, IGLMesh& out, ccMainAppInterface* app = nullptr);
ccMesh* FromIGLMesh(const IGLMesh& in, ccMainAppInterface* app = nullptr);
bool DoPerformMeshBooleanOp();


//! Mesh Boolean Operations (CSG) plugin
/** This plugin is based on ligIGL: https://libigl.github.io/
**/
class qMeshBoolean : public QObject, public ccStdPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( ccPluginInterface ccStdPluginInterface )

	Q_PLUGIN_METADATA( IID "cccorp.cloudcompare.plugin.qMeshBoolean" FILE "../info.json" )

public:

	//! Default constructor
	explicit qMeshBoolean(QObject* parent = nullptr);

	//inherited from ccStdPluginInterface
	virtual void onNewSelection(const ccHObject::Container& selectedEntities);
	virtual QList<QAction *> getActions() override;

	static BoolOpParameters s_params;

protected:

	//! Starts main action
	void doAction();

protected:

	//! Associated action
	QAction* m_action;
};

QMESHBOOLEAN_PLUGIN_LIB_API ccMesh* computeMeshBoolean(ccMesh* meshA,
	ccMesh* meshB,
	CSG_OPERATION operation);
