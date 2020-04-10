#!/usr/bin/env python3

##########################################################################
#                                                                        #
#                               CCPAPI                                   #
#                                                                        #
#  This program is free software; you can redistribute it and/or modify  #
#  it under the terms of the GNU Library General Public License as       #
#  published by the Free Software Foundation; version 2 or later of the  #
#  License.                                                              #
#                                                                        #
#  This program is distributed in the hope that it will be useful,       #
#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
#  GNU General Public License for more details.                          #
#                                                                        #
#          Copyright 2020 Paul RASCLE www.openfields.fr                  #
#                                                                        #
##########################################################################

import sys
sys.path.append('/home/paul/projets/CloudCompare/install/lib/cloudcompare')
from PyQt5.QtWidgets import QApplication
app = QApplication(sys.argv)
import cloudCompare as cc
cc.CCLib.ScalarField.initNumpyApi() # to do once before dealing with numpy
cloud = cc.loadPointCloud("/home/paul/projets/CloudCompare/data/altiXYZ/RGEALTI_FXX_0845_6446_MNT_LAMB93_IGN69.xyz")
namecloud = cloud.getName()
print(namecloud)
g = cloud.computeGravityCenter()
print(g)
print("has scalar fields: %s"%cloud.hasScalarFields() )
cloud.scale(1.0, 1.0, 2.0, (0., 0., 0.) )
g = cloud.computeGravityCenter()
print(g)
cloud.scale(1, 1, 0.5 )
g = cloud.computeGravityCenter()
print(g)
cloud.translate((-850000, -6500000, -200))
g = cloud.computeGravityCenter()
print(g)
cloud.translate((850000, 6500000, 200))
g = cloud.computeGravityCenter()
print(g)

res = cloud.exportCoordToSF((False, True, True))
print("has scalar fields: %s"%cloud.hasScalarFields() )
n = cloud.getNumberOfScalarFields()
print("number of saclar fields: %s"%n)
csfname0 = cloud.getScalarFieldName(0)
print("cloud scalar field name: %s"%csfname0)

sf = cloud.getScalarField(0)
print("scalar field: %s"%sf)    
sfname = sf.getName()
print("scalar field name: %s"%sfname)
#sf.initNumpyApi()
asf = sf.toNpArray()

sf2 = cloud.getScalarField(1)
print("scalar field: %s"%sf2)    
sf2name = sf2.getName()
print("scalar field name: %s"%sf2name)

meanvar = sf2.computeMeanAndVariance()
print(meanvar)
sf2.computeMinAndMax()
print("min: %s"%sf2.getMin())
print("max: %s"%sf2.getMax())
asf2 = sf2.toNpArray()

cc.computeCurvature(cc.GAUSSIAN_CURV, 1.88, [cloud])



res=cc.SavePointCloud(cloud, "/home/paul/projets/CloudCompare/data/res.xyz")
















