/***************************************************************************
 *   Copyright (C) 2009 by icecubeflower   *
 *   icecubeflower@yahoo.com   *
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

#ifndef SPECBOX
#define SPECBOX

#include <string>

//cave links       [0]=link type [1]=x-warp [2]=y-warp
struct Speckeeper
{
   Speckeeper();
   void Death();
   int icespec[3];  //not all three are always used
   std::string name;
};

struct SpecNode
{
   SpecNode();
   ~SpecNode();

   Speckeeper specval;
   SpecNode *specnext;
};

struct SpecBox
{
   SpecBox();
   ~SpecBox();
   void Reset();
   void Next();
   bool End();
   std::string GetName();  //(could also use GetNode().name)
   Speckeeper GetNode();
   bool InsertTail(int ival1, int ival2, int ival3, std::string rgcval);
   bool Clone(Speckeeper &specimen);  //this and InsertTail() only way to enter values
   bool SpecTaxi(int ival);
   void KillSpecBox();
   bool ZapSpecNode(int inum);
   int GetSize();

private:
   SpecNode *spechead;
   SpecNode *spectail;
   SpecNode *specreturn;
   int specsize;
};

#endif
