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

void EditBox::drawhero()
{
  glPushMatrix();

//gonna have to fix this for hackmap  (pass a paintmap like in paintmap()?)
  if(icemap.Get_Columns()*16<mWidth)
    glTranslatef(float(mWidth-icemap.Get_Columns()*16)/2.0f,0.0f,0.0f);
  if(icemap.Get_Rows()*16<mHeight)
    glTranslatef(0.0f,float(mHeight-icemap.Get_Rows()*16)/2.0f,0.0f);

  if(fy==0)
     glTranslatef(0.0,hero.GetVert(),0.0);
  //else if(fy==768*(icemap.Get_Rows()-1))
  //   glTranslatef(0.0,int(hero.GetVert())%768,0.0);
  else if(fy==icemap.Get_Rows()*16-mHeight)
    glTranslatef(0.0f,int(hero.GetVert())-((icemap.Get_Rows()*16)-mHeight),0.0f);
  else
   //  glTranslatef(0.0,376.0f,0.0);
    glTranslatef(0.0f,float(mHeight/2-8),0.0f);

  if(fx==0)
     glTranslatef(hero.GetHor(),0.0,0.0);
  //else if(fx==1024*(icemap.Get_Columns()-1))
  //   glTranslatef(int(hero.GetHor())%1024,0.0,0.0);
  else if(fx==icemap.Get_Columns()*16-mWidth)
    glTranslatef(int(hero.GetHor())-((icemap.Get_Columns()*16)-mWidth),0.0f,0.0f);
  else
     //glTranslatef(504.0,0.0,0.0);
     glTranslatef(float(mWidth/2-8),0.0f,0.0f);

  switch(istate)
  {
  case 0:
     glColor3f(0.6,0.0,0.9);
     break;
  case 1:
     glColor3f(0.6,0.0,0.9);
     break;
  case 2:
     glColor3f(0.6,0.0,0.9);
     break;
  case 3:
     glColor3f(0.6,0.0,0.9);
     break;
  case 4:
     glColor3f(0.6,0.0,0.9);
     break;
  case 5:
     glColor3f(0.6,0.0,0.9);
     break;
  case 6:
     glColor3f(0.6,0.0,0.9);
     break;
  case 7:
     glColor3f(float(rand())/float(RAND_MAX),float(rand())/float(RAND_MAX),float(rand())/float(RAND_MAX));
     break;
  case 8:
     glColor3f(float(rand())/float(RAND_MAX),float(rand())/float(RAND_MAX),float(rand())/float(RAND_MAX));
     break;
  case 9:
     break;
  case 10:
     break;
  case 11:
     glColor3f(0.6,0.0,0.9);
     break;
  case 12:
     glColor3f(0.6,0.0,0.9);
     break;
  case 13:
     break;
  case 14:
     glColor3f(0.6,0.0,0.9);
     break;
  case 15:
     glColor3f(0.6,0.0,0.9);
     break;
  case 16:
     break;
  case 17:
     glColor3f(0.6,0.0,0.9);
     break;
  }
  glBegin(GL_POLYGON);
     glVertex3f(-8.0f,-8.0f,0.0);
     glVertex3f(8.0f,-8.0f,0.0);
     glVertex3f(8.0f,8.0f,0.0);
     glVertex3f(-8.0f,8.0f,0.0);
  glEnd();
  glPopMatrix();
}

void EditBox::mdrawhero()
{
  glPushMatrix();
//gonna have to fix this for hackmap  (pass a paintmap like in paintmap()?)
  if(icemap.Get_Columns()*16<mWidth)
    glTranslatef(float(mWidth-icemap.Get_Columns()*16)/2.0f,0.0f,0.0f);
  if(icemap.Get_Rows()*16<mHeight)
    glTranslatef(0.0f,float(mHeight-icemap.Get_Rows()*16)/2.0f,0.0f);

  glTranslatef(hero.GetHor()-fx,hero.GetVert()-fy,0);

  switch(istate)
  {
  case 0:
     break;
  case 1:
     break;
  case 2:
     break;
  case 3:
     break;
  case 4:
     break;
  case 5:
     break;
  case 6:
     break;
  case 7:
     break;
  case 8:
     break;
  case 9:
     glColor3f(float(rand())/float(RAND_MAX),float(rand())/float(RAND_MAX),float(rand())/float(RAND_MAX));
     break;
  case 10:
     glColor3f(1.0,0.4,0.4);
     break;
  case 11:
     break;
  case 12:
     break;
  case 13:
     glColor3f(1.0,0.4,0.4);
     break;
  case 14:
     break;
  case 15:
     break;
  case 16:
     glColor3f(1.0,0.4,0.4);
     break;
  case 17:
     break;
  }
  glBegin(GL_POLYGON);
     glVertex3f(-8.0f,-8.0f,0.0);
     glVertex3f(8.0f,-8.0f,0.0);
     glVertex3f(8.0f,8.0f,0.0);
     glVertex3f(-8.0f,8.0f,0.0);
  glEnd();
  glPopMatrix();
}
