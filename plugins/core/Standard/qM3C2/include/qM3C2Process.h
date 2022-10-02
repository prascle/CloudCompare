//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: qM3C2                       #
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
//#            COPYRIGHT: UNIVERSITE EUROPEENNE DE BRETAGNE                #
//#                                                                        #
//##########################################################################

#ifndef Q_M3C2_PROCESS_HEADER
#define Q_M3C2_PROCESS_HEADER

//Local
#include <qM3C2Export.h>
#include "qM3C2Dialog.h"

#include <ccPointCloud.h>
#include <ccNormalVectors.h>
#include <ccOctree.h>
#include <ccOctreeProxy.h>
#include <ccHObjectCaster.h>
#include <ccProgressDialog.h>
#include <ccScalarField.h>

class ccMainAppInterface;

//! M3C2 process
/** See "Accurate 3D comparison of complex topography with terrestrial laser scanner:
	application to the Rangitikei canyon (N-Z)", Lague, D., Brodu, N. and Leroux, J.,
	2013, ISPRS journal of Photogrammmetry and Remote Sensing
**/

// Precision maps (See "3D uncertainty-based topographic change detection with SfM photogrammetry: precision maps for ground control and directly georeferenced surveys" by James et al.)
struct QM3C2_PLUGIN_LIB_API PrecisionMaps
{
    PrecisionMaps() : sX(nullptr), sY(nullptr), sZ(nullptr), scale(1.0) {}
    bool valid() const { return (sX != nullptr && sY != nullptr && sZ != nullptr); }
    CCCoreLib::ScalarField *sX, *sY, *sZ;
    double scale;
};

// Structure for parallel call to ComputeM3C2DistForPoint
struct QM3C2_PLUGIN_LIB_API M3C2Params
{
    //input data
    ccPointCloud* outputCloud = nullptr;
    ccPointCloud* corePoints = nullptr;
    NormsIndexesTableType* coreNormals = nullptr;

    //main options
    PointCoordinateType projectionRadius = 0;
    PointCoordinateType projectionDepth = 0;
    bool updateNormal = false;
    bool exportNormal = false;
    bool useMedian = false;
    bool computeConfidence = false;
    bool progressiveSearch = false;
    bool onlyPositiveSearch = false;
    unsigned minPoints4Stats = 3;
    double registrationRms = 0;

    //export
    qM3C2Dialog::ExportOptions exportOption;
    bool keepOriginalCloud = false;

    //octrees
    ccOctree::Shared cloud1Octree;
    unsigned char level1 = 0;
    ccOctree::Shared cloud2Octree;
    unsigned char level2 = 0;

    //scalar fields
    ccScalarField* m3c2DistSF = nullptr;        //M3C2 distance
    ccScalarField* distUncertaintySF = nullptr; //distance uncertainty
    ccScalarField* sigChangeSF = nullptr;       //significant change
    ccScalarField* stdDevCloud1SF = nullptr;    //standard deviation information for cloud #1
    ccScalarField* stdDevCloud2SF = nullptr;    //standard deviation information for cloud #2
    ccScalarField* densityCloud1SF = nullptr;   //export point density at projection scale for cloud #1
    ccScalarField* densityCloud2SF = nullptr;   //export point density at projection scale for cloud #2

    //precision maps
    PrecisionMaps cloud1PM, cloud2PM;
    bool usePrecisionMaps = false;

    //progress notification
    CCCoreLib::NormalizedProgress* nProgress = nullptr;
    bool processCanceled = false;
    bool processFailed = false;
};

class QM3C2_PLUGIN_LIB_API qM3C2Process
{
public:
    static bool getM3C2Params(double& normalScale,
                              double& projectionScale,
                              qM3C2Normals::ComputationMode& normMode,
                              double& samplingDist,
                              ccScalarField*& normalScaleSF,
                              int& maxThreadCount,
                              bool allowDialogs,
                              const qM3C2Dialog& dlg,
                              QString& errorMessage,
                              QWidget* parentWidget);
	
	static bool Compute(const qM3C2Dialog& dlg,
						QString& errorMessage,
						ccPointCloud*& outputCloud,
						bool allowDialogs,
						QWidget* parentWidget = nullptr,
						ccMainAppInterface* app = nullptr);

	static void ComputeM3C2DistForPoint(unsigned index);

	static M3C2Params s_M3C2Params;
};

#endif //Q_M3C2_PROCESS_HEADER
