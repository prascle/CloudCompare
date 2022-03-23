//##########################################################################
//#                                                                        #
//#                              CloudComPy                                #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; either version 3 of the License, or     #
//#  any later version.                                                    #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#  You should have received a copy of the GNU General Public License     #
//#  along with this program. If not, see <https://www.gnu.org/licenses/>. #
//#                                                                        #
//#          Copyright 2020-2021 Paul RASCLE www.openfields.fr             #
//#                                                                        #
//##########################################################################

#ifndef CLOUDCOMPY_CCTRACE_H_
#define CLOUDCOMPY_CCTRACE_H_

#ifdef _PYTHONAPI_DEBUG_

//system
#include <iostream>
#include <sstream>

#define CCTRACE(msg) {std::cerr<<std::flush<<__FILE__<<" ["<<__LINE__<<"] : "<<msg<<std::endl<<std::flush;}
#define CCTRACF(msg) {std::cerr<<std::flush<<"[CloudCompare] "<<msg<<std::endl<<std::flush;}
#else
#define CCTRACE(msg)
#define CCTRACF(msg)
#endif

#endif /* CLOUDCOMPY_PYAPI_CCTRACE_H_ */
