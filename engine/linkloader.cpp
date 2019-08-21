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

//for side links
void GameBox::loadlink(int inewstate)
{
  //std::string strtemp;
  MapBox *tempmap;

  //strtemp=icemap->GetSideLink(inewstate-5);

  if((lastmap->GetName()==icemap->GetSideLink(inewstate-5)&&lastmap->Loaded())||lastmap->Loadmap(icemap->GetSideLink(inewstate-5),false,picbox))
  {
    tempmap=lastmap;
    lastmap=icemap;
    icemap=tempmap;
    if(icemap->Get_Columns()*16<mWidth)
      subWidth=icemap->Get_Columns()*16;
    else
      subWidth=mWidth;
    if(icemap->Get_Rows()*16<mHeight)
      subHeight=icemap->Get_Rows()*16;
    else
      subHeight=mHeight;

    istate=inewstate;
    masterscroll=0.0f;
    switch(istate)
    {
    case 5:  //up
      //fy=float(icemap->Get_Rows()-1)*768.0f;
      fy=float(icemap->Get_Rows()*16-subHeight);
      icemap->WarpGiz(hero,hero.GetHor(),float(icemap->Get_Rows()*16),0,false);
      break;
    case 6: //right
      fx=0;
      icemap->WarpGiz(hero,0,hero.GetVert(),1,false);
      break;
    case 7: //down
      fy=0;
      icemap->WarpGiz(hero,hero.GetHor(),0,2,false);
      break;
    case 8:  //left
      //fx=float(icemap->Get_Columns()-1)*1024.0f;
      fx=float(icemap->Get_Columns()*16-subWidth);
      icemap->WarpGiz(hero,float(icemap->Get_Columns()*16),hero.GetVert(),3,false);
      break;
    }
  }
}

void GameBox::loadlink2()
{
  MapBox *tempmap;
  Speckeeper specval;

  if(icemap->ChooseCaveNode(mapblock.terrain-2)!=false)
  {
    tempmap=lastmap;
    lastmap=icemap;
    icemap=tempmap;

    if(icemap->GetName()!=lastmap->GetCaveNode().name)
      icemap->Loadmap(lastmap->GetCaveNode().name,false,picbox);

    if(icemap->Get_Columns()*16<mWidth)
      subWidth=icemap->Get_Columns()*16;
    else
      subWidth=mWidth;
    if(icemap->Get_Rows()*16<mHeight)
      subHeight=icemap->Get_Rows()*16;
    else
      subHeight=mHeight;

    specval=lastmap->GetCaveNode();
    icemap->WarpGiz(hero,specval,true);

    setfx();
    setfy();
  }
}
