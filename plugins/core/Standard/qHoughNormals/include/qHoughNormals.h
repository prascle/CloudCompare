//##########################################################################
//#                                                                        #
//#                   CLOUDCOMPARE PLUGIN: qHoughNormals                   #
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

#ifndef QHOUGH_NORMALS_PLUGIN_HEADER
#define QHOUGH_NORMALS_PLUGIN_HEADER

#include "qHoughNormalsExport.h"
#include "ccStdPluginInterface.h"

//! Wrapper to the 'normals_Hough' library (https://github.com/aboulch/normals_Hough)
/** "Deep Learning for Robust Normal Estimation in Unstructured Point Clouds"
	by Alexandre Boulch and Renaud Marlet, Symposium of Geometry Processing 2016, Computer Graphics Forum
**/
class qHoughNormals : public QObject, public ccStdPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( ccPluginInterface ccStdPluginInterface )
	
	Q_PLUGIN_METADATA( IID "cccorp.cloudcompare.plugin.qHoughNormals" FILE "../info.json" )

public:

	//! Default constructor
	explicit qHoughNormals(QObject* parent = nullptr);

	virtual ~qHoughNormals() = default;

	//inherited from ccStdPluginInterface
	virtual void onNewSelection(const ccHObject::Container& selectedEntities) override;
	virtual QList<QAction *> getActions() override;

protected:

	//! Slot called when associated ation is triggered
	void doAction();

protected:

	//! Associated action
	QAction* m_action;
};

void QHoughNormals_PLUGIN_LIB_API computeHoughNormalsPy(ccPointCloud* cloud,
                                                        int           K             = 100,
                                                        int           T             = 1000,
                                                        int           n_phi         = 15,
                                                        int           n_rot         = 5,
                                                        bool          use_density   = false,
                                                        float         tol_angle_rad = 0.79f,
                                                        int           k_density     = 5);

#endif //QHOUGH_NORMALS_PLUGIN_HEADER
