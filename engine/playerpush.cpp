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

//can't I move all these setfx fy's to one hit in superupdate?

#include "icegame.h"

Iceblock GameBox::input(Uint8 *stroky, Uint32 history)
{
   //Iceint iceblock;
   Iceblock iceval;


   switch(hero.GetState())
   {
   case 0:
   case 1:
   case 2:
   case 3:
   case 8:
   case 9:
   case 10:
   case 11:
   case 12:
   case 13:
   case 14:
   case 15:

//  Iceblock Gizmove(Gizmo &player, int idirection, Uint32 history);
//  Iceblock Gizrun(Gizmo &player, int idirection, Uint32 history);
      //right now this is only functional with a hero one block wide
      if(stroky[SDLK_UP]&&stroky[SDLK_RIGHT])
      {
         if(stroky[SDLK_LCTRL])
            //iceval=hero.Gizrun(4,history,icemap->mapgrid);
            iceval=icemap->Gizrun(hero,4,history);
         else
            //iceval=hero.Gizmove(4,history,icemap->mapgrid);
            iceval=icemap->Gizmove(hero,4,history);
         if(hero.GetVert()==0.0f)
            iceval=65532;  //signals for a scroll up
         else if(hero.GetHor()==float(icemap->Get_Columns()*16))
            iceval=65533;  //right
      }
      else if(stroky[SDLK_DOWN]&&stroky[SDLK_RIGHT])
      {
         if(stroky[SDLK_LCTRL])
            //iceval=hero.Gizrun(5,history,icemap->mapgrid);
            iceval=icemap->Gizrun(hero,5,history);
         else
            //iceval=hero.Gizmove(5,history,icemap->mapgrid);
            iceval=icemap->Gizmove(hero,5,history);
         if(hero.GetVert()==float(icemap->Get_Rows()*16))
            iceval=65534;  //down
         else if(hero.GetHor()==float(icemap->Get_Columns()*16))
            iceval=65533;  //right
      }
      else if(stroky[SDLK_DOWN]&&stroky[SDLK_LEFT])
      {
         if(stroky[SDLK_LCTRL])
            //iceval=hero.Gizrun(6,history,icemap->mapgrid);
            iceval=icemap->Gizrun(hero,6,history);
         else
            //iceval=hero.Gizmove(6,history,icemap->mapgrid);
            iceval=icemap->Gizmove(hero,6,history);
         if(hero.GetVert()==float(icemap->Get_Rows()*16))
            iceval=65534;  //down
         else if(hero.GetHor()==0.0f)
            iceval=65535;  //left
      }
      else if(stroky[SDLK_UP]&&stroky[SDLK_LEFT])
      {
         if(stroky[SDLK_LCTRL])
            //iceval=hero.Gizrun(7,history,icemap->mapgrid);
            iceval=icemap->Gizrun(hero,7,history);
         else
            //iceval=hero.Gizmove(7,history,icemap->mapgrid);
            iceval=icemap->Gizmove(hero,7,history);
         if(hero.GetVert()==0.0f)
            iceval=65532;  //signals for a scroll up
         else if(hero.GetHor()==0.0f)
            iceval=65535;  //left
      }
      else if(stroky[SDLK_UP])
      {
         if(stroky[SDLK_LCTRL])
            //iceval=hero.Gizrun(0,history,icemap->mapgrid);
            iceval=icemap->Gizrun(hero,0,history);
         else
            //iceval=hero.Gizmove(0,history,icemap->mapgrid);
            iceval=icemap->Gizmove(hero,0,history);
         if(hero.GetVert()==0.0f)
            iceval=65532;  //signals for a scroll up
      }
      else if(stroky[SDLK_DOWN])
      {
         if(stroky[SDLK_LCTRL])
            //iceval=hero.Gizrun(2,history,icemap->mapgrid);
            iceval=icemap->Gizrun(hero,2,history);
         else
            //iceval=hero.Gizmove(2,history,icemap->mapgrid);
            iceval=icemap->Gizmove(hero,2,history);
         if(hero.GetVert()==float(icemap->Get_Rows()*16))
            iceval=65534;
      }
      else if(stroky[SDLK_LEFT])
      {
         if(stroky[SDLK_LCTRL])
            //iceval=hero.Gizrun(3,history,icemap->mapgrid);
            iceval=icemap->Gizrun(hero,3,history);
         else
            //iceval=hero.Gizmove(3,history,icemap->mapgrid);
            iceval=icemap->Gizmove(hero,3,history);
         if(hero.GetHor()==0.0f)
            iceval=65535;  //left
      }
      else if(stroky[SDLK_RIGHT])
      {
         if(stroky[SDLK_LCTRL])
            //iceval=hero.Gizrun(1,history,icemap->mapgrid);
            iceval=icemap->Gizrun(hero,1,history);
         else
            //iceval=hero.Gizmove(1,history,icemap->mapgrid);
            iceval=icemap->Gizmove(hero,1,history);
         if(hero.GetHor()==float(icemap->Get_Columns()*16))
            iceval=65533;
      }
      break;
   }

   return iceval;
}
