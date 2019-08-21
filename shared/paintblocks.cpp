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

#include "paintblocks.h"

void drawblocks(MapBox &icemap, float fx, float fy, int mWidth, int mHeight)
{
  int ix, ij;

  glPushMatrix();

  if(icemap.Get_Columns()*16<mWidth)
    glTranslatef(float(mWidth-icemap.Get_Columns()*16)/2.0f,0.0f,0.0f);
  if(icemap.Get_Rows()*16<mHeight)
    glTranslatef(0.0f,float(mHeight-icemap.Get_Rows()*16)/2.0f,0.0f);

  glTranslatef(-(int(fx)%16),-(int(fy)%16),0.0);
  for(ij=int(fy)/16;ij<int(fy)/16+48;ij++)
  {
    for(ix=int(fx)/16;ix<int(fx)/16+64;ix++)
    {
      if(icemap.Grab_Block(ij,ix)!=0)
      {
        if(icemap.Grab_Block(ij,ix)==1)
          glColor3f(1.0f,0.0f,0.0f);
        else if(icemap.Grab_Block(ij,ix)>1&&icemap.Grab_Block(ij,ix)<52)
          glColor3f(0.0f,1.0f,0.0f);
        else
          glColor3f(0.0f,0.0f,1.0f);
        glBegin(GL_POLYGON);
          glVertex3f(0.0f,0.0f,0.0f);
          glVertex3f(16.0f,0.0f,0.0f);
          glVertex3f(16.0f,16.0f,0.0f);
          glVertex3f(0.0f,16.0f,0.0f);
        glEnd();
      }
      glTranslatef(16.0,0.0,0.0);
    }
    glTranslatef(-1024.0,16.0,0.0);
  }
  glPopMatrix();
}
