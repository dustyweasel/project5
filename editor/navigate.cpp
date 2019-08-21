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

#include "ice_edit.h"

void EditBox::up()
{
  //hero.Teleport(hero.GetHor(),hero.GetVert()-16.0f,0,icemap.mapgrid);
  icemap.WarpGiz(hero,hero.GetHor(),hero.GetVert()-16.0f,0,true);
  setfy();
}

void EditBox::down()
{
  //hero.Teleport(hero.GetHor(),hero.GetVert()+16.0f,0,icemap.mapgrid);
  icemap.WarpGiz(hero,hero.GetHor(),hero.GetVert()+16.0f,0,true);
  setfy();
}

void EditBox::left()
{
  //hero.Teleport(hero.GetHor()-16.0f,hero.GetVert(),0,icemap.mapgrid);
  icemap.WarpGiz(hero,hero.GetHor()-16.0f,hero.GetVert(),0,true);
  setfx();
}

void EditBox::right()
{
  //hero.Teleport(hero.GetHor()+16.0f,hero.GetVert(),0,icemap.mapgrid);
  icemap.WarpGiz(hero,hero.GetHor()+16.0f,hero.GetVert(),0,true);
  setfx();
}

void EditBox::setfx()
{
   //if(hero.GetHor()<=504.0f)
  if(icemap.Get_Columns()*16<=mWidth||hero.GetHor()<=mWidth/2-8)
    fx=0.0f;
   //else if(hero.GetHor()<(icemap.Get_Columns()-1)*HORZ+HORZ/2-8)
  else if(hero.GetHor()<icemap.Get_Columns()*16-mWidth/2-8)
      //fx=hero.GetHor()-504.0f;
    fx=hero.GetHor()-(mWidth/2-8);
  else
      //fx=float(icemap.Get_Columns()-1)*1024.0f;
    fx=float(icemap.Get_Columns()*16-mWidth);
}

void EditBox::setfy()
{
  //if(hero.GetVert()<=376.0f)
  if(icemap.Get_Rows()*16<=mHeight||hero.GetVert()<=mHeight/2-8)
    fy=0.0f;
  //else if(hero.GetVert()<(icemap.Get_Rows()-1)*VERT+VERT/2-8)
  else if(hero.GetVert()<icemap.Get_Rows()*16-mHeight/2-8)
    //fy=hero.GetVert()-376.0f;
    fy=hero.GetVert()-(mHeight/2-8);
  else
    //fy=float(icemap.Get_Rows()-1)*768.0f;
    fy=float(icemap.Get_Rows()*16-mHeight);
}
