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

void EditBox::drawfade(int icorner)
{
   Iceblock icetrash;
   int ispot, ispot2;

//ispot2-x ispot-y
   switch(icorner)
   {
   case 0:  //top left
     ispot2=0;
     ispot=-690;
     break;
   case 1:  //top right
     ispot2=624;
     ispot=-690;
     break;
   case 2:  //bottom right
     ispot2=624;
     ispot=0;
     break;
   case 3:  //bottom left
     ispot2=0;
     ispot=0;
     break;
   default:
     ispot2=0;
     ispot=0;
     break;
   }

   glColor3f(0.0,0.0,0.0);
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);
   glBegin(GL_POLYGON);
      glVertex3f(0+ispot2  ,690+ispot,0.0);
      glVertex3f(400+ispot2,690+ispot,0.0);
      glVertex3f(400+ispot2,768+ispot,0.0);
      glVertex3f(0+ispot2  ,768+ispot,0.0);
   glEnd();

   icetrash=icemap.Grab_Block(int(hero.GetVert())/16,int(hero.GetHor())/16);

   glEnable(GL_TEXTURE_2D);
   glColor3fv(rgfheader);
   typewriter.glPrint(0+ispot2,698+ispot,"%s",icemap.GetName().c_str());
   glColor3fv(rgfedit);
   typewriter.glPrint(0+ispot2 ,714+ispot,"position=(%i,%i)",int(hero.GetHor())/16,int(hero.GetVert())/16);

   switch(iceout.terrain)
   {
   case 0:
      typewriter.glPrint(0+ispot2,730+ispot,"iceout=%i CLEAR",iceout.terrain);
      break;
   case 1:
      typewriter.glPrint(0+ispot2,730+ispot,"iceout=%i BLOCK",iceout.terrain);
      break;
   case 52:
      typewriter.glPrint(0+ispot2,730+ispot,"iceout=%i DEEP WATER",iceout.terrain);
      break;
   case 65532:
      typewriter.glPrint(0+ispot2,730+ispot,"iceout=%i UP LINK",iceout.terrain);
      break;
   case 65533:
      typewriter.glPrint(0+ispot2,730+ispot,"iceout=%i RIGHT LINK",iceout.terrain);
      break;
   case 65534:
      typewriter.glPrint(0+ispot2,730+ispot,"iceout=%i DOWN LINK",iceout.terrain);
      break;
   case 65535:
      typewriter.glPrint(0+ispot2,730+ispot,"iceout=%i LEFT LINK",iceout.terrain);
      break;
   default:
      if(iceout>1&&iceout<52)
         typewriter.glPrint(0+ispot2,730+ispot,"iceout=%i Link %i",iceout.terrain,iceout.terrain-2);
      else
         typewriter.glPrint(0+ispot2,730+ispot,"iceout=%i",iceout.terrain);
      break;
   }
   switch(icetrash.terrain)
   {
   case 0:
      typewriter.glPrint(0+ispot2,746+ispot,"block =%i CLEAR",icetrash.terrain);
      break;
   case 1:
      typewriter.glPrint(0+ispot2,746+ispot,"block =%i BLOCK",icetrash.terrain);
      break;
   case 52:
      typewriter.glPrint(0+ispot2,746+ispot,"block =%i DEEP WATER",icetrash.terrain);
      break;
   case 65532:
      typewriter.glPrint(0+ispot2,746+ispot,"iceout=%i UP LINK",icetrash.terrain);
      break;
   case 65533:
      typewriter.glPrint(0+ispot2,746+ispot,"iceout=%i RIGHT LINK",icetrash.terrain);
      break;
   case 65534:
      typewriter.glPrint(0+ispot2,746+ispot,"iceout=%i DOWN LINK",icetrash.terrain);
      break;
   case 65535:
      typewriter.glPrint(0+ispot2,746+ispot,"iceout=%i LEFT LINK",icetrash.terrain);
      break;
   default:
      if(icetrash>1&&icetrash<52)
         typewriter.glPrint(0+ispot2,746+ispot,"block =%i Link %i",icetrash.terrain,icetrash.terrain-2);
      else
         typewriter.glPrint(0+ispot2,746+ispot,"block =%i",icetrash.terrain);
      break;
   }
}
