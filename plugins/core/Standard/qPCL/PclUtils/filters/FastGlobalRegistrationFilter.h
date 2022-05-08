#pragma once

//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: qPCL                        #
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
//#                    COPYRIGHT: CloudCompare project                     #
//#                                                                        #
//##########################################################################

#include "BaseFilter.h"

//! Filter based on "Q.-Y. Zhou, J. Park, and V. Koltun, Fast Global Registration, ECCV, 2016."
/** See https://github.com/isl-org/FastGlobalRegistration
**/
class FastGlobalRegistrationFilter : public BaseFilter
{
public:
	FastGlobalRegistrationFilter();
	~FastGlobalRegistrationFilter() override;

	//inherited from BaseFilter
	int compute() override;
    void setParameters(ccPointCloud* refCloud, std::vector<ccPointCloud*> alignClouds, double radius = 0);
    double getAutoRadius()
    {
        return m_featureRadius;
    }

protected:
	int getParametersFromDialog() override;
	bool checkSelected() const override;
	QString getErrorMessage(int errorCode) const override;

protected: // variables

	std::vector<ccPointCloud*> m_alignedClouds;
	ccPointCloud* m_referenceCloud;
	double m_featureRadius;
};
