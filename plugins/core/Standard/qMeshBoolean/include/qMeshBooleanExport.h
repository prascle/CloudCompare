//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: qMeshBoolean                #
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
//#                                                                        #
//##########################################################################

#ifndef Q_MESHBOOLEAN_PLUGIN_EXPORT_HEADER
#define Q_MESHBOOLEAN_PLUGIN_EXPORT_HEADER

#include <QtCore/QtGlobal>

#if defined(QMESHBOOLEAN_PLUGIN_LIBRARY_BUILD)
   #define QMESHBOOLEAN_PLUGIN_LIB_API Q_DECL_EXPORT
#else
   #define QMESHBOOLEAN_PLUGIN_LIB_API Q_DECL_IMPORT
#endif


#endif //Q_MESHBOOLEAN_PLUGIN_EXPORT_HEADER
