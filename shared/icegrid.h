/***************************************************************************
 *   Copyright (C) 2008 by icecubeflower                                   *
 *   icecube@icebox                                                        *
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

#ifndef ICEGRID
#define ICEGRID

#include <stdlib.h>  //need this for NULL
#include <fstream>
#include "filechecker.h"


//Don't think cartesian.  It goes Y,X not X,Y and 0,0 is top left of screen
//and down and to the right is positive and negative doesn't exist

/*  **iceblock=new iceblock*[irow]
        |
     *iceblock=new iceblock[icol]
     *iceblock=new iceblock[icol]
     *iceblock=new iceblock[icol]     */

struct Iceblock
{
   Iceblock();
   ~Iceblock();
   void operator=(Iceblock iceval);
   bool operator ==(int ival);
   void operator =(int ival);
   bool operator !=(int ival);
   bool operator <(int ival);
   bool operator >(int ival);
   void operator +=(int ival);
   void operator -=(int ival);
   int operator -(int ival);

   int terrain;
};

struct Icematrix
{
   Icematrix();
   ~Icematrix();
   bool Rematrix(int newrow, int newcol);
   Iceblock Grab_Element(int grabrow, int grabcol);
   bool Set_Element(int setrow, int setcol, Iceblock iceval);
   int Get_Rows();
   int Get_Columns();
   void Killmatrix();
   void Writematrix(std::ofstream &outfile);
   bool Readmatrix(std::ifstream &infile);

private:
   Iceblock **icemaster;
   int icol;  //columns (#of screens, icol==3 means three screens wide==192 blocks wide)
   int irow;  //rows
};

#endif
