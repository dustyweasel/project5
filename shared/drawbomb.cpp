/***************************************************************************
 *   Copyright (C) 2009 by icecubeflower   *
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

#include "drawbomb.h"

//Revamp this.  Make BombBox return specific elements.  Make it private in MapBox.
void drawbombs(MapBox &icemap, float fx, float fy)
{
  GLUquadricObj* quadratic;

  quadratic=gluNewQuadric();
  glDisable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  glColor4f(0.0,0.0,1.0,1.0f);

  icemap.ResetAttackNodes();
  while(icemap.AttackNodeEnd()==false)
  {
    glPushMatrix();
    glTranslatef(icemap.GetAttackHor()-fx,icemap.GetAttackVert()-fy,0.0);
    gluDisk(quadratic,0.0,icemap.GetAttackSize(),25,1);
    glPopMatrix();
    icemap.NextAttackNode();
  }

  gluDeleteQuadric(quadratic);
}
