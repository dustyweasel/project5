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

void GameBox::drawhearts()
{
   int ix;
   float ftemp;

   glPushMatrix();
   glTranslatef(float(mWidth-244),24.0f,0.0f);
   glBindTexture(GL_TEXTURE_2D, statbox[0]);
   for(ix=0;ix<int(hero.GetHealth());ix++)
   {
      glBegin(GL_POLYGON);
         glTexCoord2f(0,0);		glVertex3f(-8,-8,0.0);
         glTexCoord2f(1,0);		glVertex3f(8,-8,0.0);
         glTexCoord2f(1,1);		glVertex3f(8,8,0.0);
         glTexCoord2f(0,1);		glVertex3f(-8,8,0.0);
      glEnd();
      glTranslatef(24,0,0);
   }
   if(hero.GetHealth()-float(ix)>0.0f)
   {
      ftemp=(hero.GetHealth()-float(ix))*8.0f;
      glBegin(GL_POLYGON);
         glTexCoord2f(0,0);		glVertex3f(-ftemp,-ftemp,0.0);
         glTexCoord2f(1,0);		glVertex3f(ftemp,-ftemp,0.0);
         glTexCoord2f(1,1);		glVertex3f(ftemp,ftemp,0.0);
         glTexCoord2f(0,1);		glVertex3f(-ftemp,ftemp,0.0);
      glEnd();
      glTranslatef(24,0,0);
      ix+=1;
   }
   glBindTexture(GL_TEXTURE_2D, statbox[1]);
   while(ix<10)
   {
      glBegin(GL_POLYGON);
         glTexCoord2f(0,0);		glVertex3f(-8,-8,0.0);
         glTexCoord2f(1,0);		glVertex3f(8,-8,0.0);
         glTexCoord2f(1,1);		glVertex3f(8,8,0.0);
         glTexCoord2f(0,1);		glVertex3f(-8,8,0.0);
      glEnd();
      glTranslatef(24,0,0);
      ix+=1;
   }
   glPopMatrix();
}
