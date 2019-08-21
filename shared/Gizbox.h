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

#ifndef GIZBOX
#define GIZBOX

#include "Gizmo.h"

struct GizNode
{
   GizNode();
   ~GizNode();

   Gizmo *giz;
   GizNode *giznext;
   GizNode *gizprev;
};

struct GizBox
{
   GizBox();
   ~GizBox();

   bool InsertTail(Gizmo *newgiz);  //make these two private someday maybe
   bool InsertHead(Gizmo *newgiz);
   bool InsertNode(std::string &rgcfilename,int hor,int vert, int icopy, bool bhead, ImageVault &picbox);
   bool ZapGiz();
   void KillGizBox();
   GLuint GetPic();
   GLuint GetPic(int inum);
   void Reset();
   void Next();
   bool GizTaxi(int ival);
   int Gettype();
   void Update(Gizmo *enemy, Icematrix &mapgrid, Uint32 history, ImageVault &picbox, AudioBox &boombox,BombBox &attacknodes,
               GizBox &splatterbox);
   void Victimize(Gizmo *attacker, AudioBox *boombox, ImageVault *picbox);
   int GetGizBoxSize();
   bool GetHurt();
   int GetHor();
   int GetVert();
   int GetType();
   float GetSize();
   float GetSpin();
   int GetSpawnType();
   bool SetSpawnType(int ival);
   std::string GetName();
   bool End();
   bool Warp(float x, float y, Icematrix &mapgrid);
   bool Clear();  //returns true if all monsters are dead  (get rid of this function)

private:
   GizNode *gizhead;
   GizNode *giztail;
   GizNode *gizreturn;
   int igizsize;
};

#endif
