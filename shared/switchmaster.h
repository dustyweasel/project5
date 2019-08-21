/***************************************************************************
 *   Copyright (C) 2007 by icecubeflower                                   *
 *   icecubeflower@yahoo.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <string>

#ifndef SWITCHMASTER
#define SWITCHMASTER

//day is x cycles long  (x milliseconds on fast machine)
#define DAYLEN 1800000
//x cycles to shift daylight
#define DAYSHIFT 2000.0f
#define CLOUDSHIFT 2000.0f

#define HORZ 1024
#define VERT 768
#define BPP 32

//for cartoon cave links
#define DVAL 800
#define SPLATTERMAX 1000

//should only be three sections this effects
#define PROGRAMMER
//#define VAULTCHECK

namespace Pathfinder
{
  extern const std::string Anibox_Path;    //="Data/Anibox/";
  extern const std::string Gizmo_Path;     //"Data/Gizmos/";
  extern const std::string Image_Path;     //="Data/Images/";
  extern const std::string Map_Path;       //="Data/Maps/";
  extern const std::string Song_Path;      //="Data/Songs/";
  extern const std::string Sound_Path;     //="Data/Sounds/";
}

#endif
