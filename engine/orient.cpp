/***************************************************************************
 *   Copyright (C) 2007 by icecubeflower   *
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

#include "icegame.h"

//these count on a 1024x768 pixel screen
//vertical example:
//pixels numbered 0-767
//grid surrounds pixels, top line=0 bottom line =768
//game divided into 16x16 pixel blocks
//block one is pixel 0-15
//a hero's coordinates use the grid, not the pixel
//a hero at 0,15 is in block one
//a hero at 0,16 is in block two
//trick is hero can move all the way to irow*768 which puts him on next map

//instead of using hero it would probably be easy to create a gizmo *camera and make
//camera point at anything we want

void GameBox::setfy()
{
   //fystore=fy;
  //if(hero.GetVert()<=384.0f)
  if(icemap->Get_Rows()*16<=mHeight||hero.GetVert()<=mHeight/2)
    fy=0;
  //else if(hero.GetVert()<icemap->Get_Rows()*VERT-(VERT/2))
  else if(hero.GetVert()<icemap->Get_Rows()*16-mHeight/2)
    //fy=int(hero.GetVert())-384;
    fy=hero.GetVert()-float(mHeight/2);
  else
    //fy=(icemap->Get_Rows()-1)*768;
    fy=icemap->Get_Rows()*16-mHeight;
}

void GameBox::setfx()
{
   //fxstore=fx;
   //if(hero.GetHor()<=512.0f)
   if(icemap->Get_Columns()*16<=mWidth||hero.GetHor()<=mWidth/2)
      fx=0.0f;
   //else if(hero.GetHor()<icemap->Get_Columns()*HORZ-(HORZ/2))
   else if(hero.GetHor()<icemap->Get_Columns()*16-mWidth/2)
      //fx=hero.GetHor()-512.0f;
     fx=hero.GetHor()-float(mWidth/2);
   else
      //fx=float(icemap->Get_Columns()-1)*1024.0f;
     fx=icemap->Get_Columns()*16-mWidth;
}
