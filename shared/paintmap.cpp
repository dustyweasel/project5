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

//I don't need to cast fx and fy as floats anymore, fix it later

#include "paintmap.h"

//careful to not use icemap and hackmap in here, use paintmap
void drawmap(MapBox &paintmap, float fx, float fy, int mWidth, int mHeight, int subWidth, int subHeight) //<-paintmap!!!
{
  //int subWidth=mWidth;
  //int subHeight=mHeight;

  glPushMatrix();

  if(paintmap.Get_Columns()*16<mWidth)
  {
    subWidth=paintmap.Get_Columns()*16;  //get rid of this line? or get rid of global subWidth?
    glTranslatef(float(mWidth-paintmap.Get_Columns()*16)/2.0f,0.0f,0.0f);
  }
  if(paintmap.Get_Rows()*16<mHeight)
  {
    subHeight=paintmap.Get_Rows()*16;
    glTranslatef(0.0f,float(mHeight-paintmap.Get_Rows()*16)/2.0f,0.0f);
  }

  if(paintmap.GotAniLayer(0))
  {
    glBindTexture(GL_TEXTURE_2D, paintmap.GetAniLayerPic(0));
    glBegin(GL_POLYGON);
      glTexCoord2f(float(fx)/float(mWidth),1.0+float(fy)/float(mHeight));	glVertex3f(0,subHeight,0.0);
      glTexCoord2f(1.0+float(fx)/float(mWidth),1.0+float(fy)/float(mHeight));	glVertex3f(subWidth,subHeight,0.0);
      glTexCoord2f(1.0+float(fx)/float(mWidth),float(fy)/float(mHeight));	glVertex3f(subWidth,0,0.0);
      glTexCoord2f(float(fx)/float(mWidth),float(fy)/float(mHeight));		glVertex3f(0,0,0.0);
    glEnd();
  }
  if(paintmap.GetLayer(0)!=0)
  {
    glBindTexture(GL_TEXTURE_2D, paintmap.GetLayer(0));
    glBegin(GL_POLYGON);
      glTexCoord2f(float(fx)/(paintmap.Get_Columns()*16.0f)     ,     (float(fy)+float(subHeight))/(paintmap.Get_Rows()*16.0f));
      glVertex3f(0,subHeight,0.0);
      glTexCoord2f((float(fx)+float(subWidth))/(paintmap.Get_Columns()*16.0f)     ,(float(fy)+float(subHeight))/(paintmap.Get_Rows()*16.0f));
      glVertex3f(subWidth,subHeight,0.0);
      glTexCoord2f((float(fx)+float(subWidth))/(paintmap.Get_Columns()*16.0f),float(fy)/(paintmap.Get_Rows()*16.0f));
      glVertex3f(subWidth,0,0.0);
      glTexCoord2f(float(fx)/(paintmap.Get_Columns()*16.0f),float(fy)/(paintmap.Get_Rows()*16.0f));
      glVertex3f(0,0,0.0);
    glEnd();
  }

  glPopMatrix();
}

void drawmap2(MapBox &paintmap, float fx, float fy, float mWidth, float mHeight)
{
  float subWidth;
  float subHeight;

  if(paintmap.Get_Columns()*16<mWidth)
  {
    subWidth=paintmap.Get_Columns()*16;
    glTranslatef(float(mWidth-paintmap.Get_Columns()*16)/2.0f,0.0f,0.0f);
  }
  else
  {
    subWidth=mWidth;
  }
  if(paintmap.Get_Rows()*16<mHeight)
  {
    subHeight=paintmap.Get_Rows()*16;
    glTranslatef(0.0f,float(mHeight-paintmap.Get_Rows()*16)/2.0f,0.0f);
  }
  else
  {
    subHeight=mHeight;
  }

  glBindTexture(GL_TEXTURE_2D, paintmap.GetLayer(1));
    glBegin(GL_POLYGON);
      glTexCoord2f(float(fx)/(paintmap.Get_Columns()*16.0f)     ,     (float(fy)+float(subHeight))/(paintmap.Get_Rows()*16.0f));
      glVertex3f(0,subHeight,0.0);
      glTexCoord2f((float(fx)+float(subWidth))/(paintmap.Get_Columns()*16.0f)     ,(float(fy)+float(subHeight))/(paintmap.Get_Rows()*16.0f));
      glVertex3f(subWidth,subHeight,0.0);
      glTexCoord2f((float(fx)+float(subWidth))/(paintmap.Get_Columns()*16.0f),float(fy)/(paintmap.Get_Rows()*16.0f));
      glVertex3f(subWidth,0,0.0);
      glTexCoord2f(float(fx)/(paintmap.Get_Columns()*16.0f),float(fy)/(paintmap.Get_Rows()*16.0f));
      glVertex3f(0,0,0.0);
    glEnd();
}
