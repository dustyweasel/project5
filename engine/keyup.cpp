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

void GameBox::keyunbreak(SDL_Event &event)
{
   switch(istate)
   {
///////////////////////////////////  istate==0  main menu     /////////////////////////////////////////////////////////
   case 0:
      break;
///////////////////////////////////  istate==1  main game     /////////////////////////////////////////////////////////
   case 1:
   case 4:
      switch(event.key.keysym.sym)
      {
      case SDLK_UP:
         hero.Gizface(0);
         break;
      case SDLK_DOWN:
         hero.Gizface(2);
         break;
      case SDLK_RIGHT:
         hero.Gizface(1);
         break;
      case SDLK_LEFT:
         hero.Gizface(3);
         break;
      }
      break;
///////////////////////////////////  istate==2 cutscene    /////////////////////////////////////////////////////////
   case 2:
      break;
///////////////////////////////////  istate==3/////////////////////////////////////////////////////////
   case 3:
      break;
///////////////////////////////////  istate==4     /////////////////////////////////////////////////////////
  /* case 4:
      break;*/
///////////////////////////////////  istate==5     /////////////////////////////////////////////////////////
   case 5:  //scroll up
   case 6:
   case 7:
   case 8:
      switch(event.key.keysym.sym)
      {
      case SDLK_UP:
         hero.Gizface(0);
         break;
      case SDLK_DOWN:
         hero.Gizface(2);
         break;
      case SDLK_RIGHT:
         hero.Gizface(1);
         break;
      case SDLK_LEFT:
         hero.Gizface(3);
         break;
      }
      break;
///////////////////////////////////  istate==9     /////////////////////////////////////////////////////////
   case 9:
      break;
   }
}
