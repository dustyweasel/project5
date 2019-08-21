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

#include "MapBox.h"

void MapBox::drawstore()
{
   int itrash;

   while(monsterstore.pichead!=NULL)
   {
      switch(monsterstore.picreturn->itype)
      {
      case 0:
         break;
      case 1:  //rat
      case 4:  //bugs
      case 5:  //lightning bugs
      case 6:  //dragon
         break;
      case 2:
         glPushMatrix();
         glTranslatef(monsterstore.pichead->ihor,monsterstore.pichead->ivert,0.0);
         //glBindTexture(GL_TEXTURE_2D, monsterstore.pichead->pic->texID);
         glBindTexture(GL_TEXTURE_2D, monsterstore.pichead->picnum);
         itrash=monsterstore.pichead->ihalfsize;
         glBegin(GL_POLYGON);
            glTexCoord2f(0,0);		glVertex3f(-itrash,-itrash,0.0);
            glTexCoord2f(1,0);		glVertex3f(itrash,-itrash,0.0);
            glTexCoord2f(1,1);		glVertex3f(itrash,itrash,0.0);
            glTexCoord2f(0,1);		glVertex3f(-itrash,itrash,0.0);
         glEnd();
         monsterstore.PopPic();
         glRotatef(monsterstore.pichead->fspin,0.0,0.0,1.0);
         //glBindTexture(GL_TEXTURE_2D, monsterstore.pichead->pic->texID);
         glBindTexture(GL_TEXTURE_2D, monsterstore.pichead->picnum);
         glBegin(GL_POLYGON);
            glTexCoord2f(0,0);		glVertex3f(-itrash,-itrash,0.0);
            glTexCoord2f(1,0);		glVertex3f(itrash,-itrash,0.0);
            glTexCoord2f(1,1);		glVertex3f(itrash,itrash,0.0);
            glTexCoord2f(0,1);		glVertex3f(-itrash,itrash,0.0);
         glEnd();
         //glRotatef(monsterstore.pichead->fspin,0.0,0.0,-1.0);
         glPopMatrix();//glTranslatef(-monsterstore.pichead->ihor,-monsterstore.pichead->ivert,0.0);
         break;
      }
      monsterstore.PopPic();
   }
}
