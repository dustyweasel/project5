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

void EditBox::drawmenu(int ispot2)
{
  glColor3f(0.0,0.0,0.0);
  glDisable(GL_TEXTURE_2D);
  glBegin(GL_POLYGON);
    glVertex3f(0+ispot2,0,0.0);
    glVertex3f(450+ispot2,0,0.0);
    glVertex3f(450+ispot2,311,0.0);
    glVertex3f(0+ispot2,311,0.0);
  glEnd();
  glEnable(GL_TEXTURE_2D);
  glColor3fv(rgfadvice);
  typewriter.glPrint(ispot2,  0,"alt-Q   <quit>");
  typewriter.glPrint(ispot2, 16,"ESC     <toggle menu>");
  typewriter.glPrint(ispot2, 32,"F2      <open new map>");
  typewriter.glPrint(ispot2, 48,"SPACE   <toggle edit>");
  typewriter.glPrint(ispot2, 64,"R Click <toggle mouse mode>");
  typewriter.glPrint(ispot2, 80,"L Click <toggle edit>");
  typewriter.glPrint(ispot2, 96,"WHEEL   <toggle iceout>");
  typewriter.glPrint(ispot2,112,"F3      <side links>");
  typewriter.glPrint(ispot2,128,"F4      <cave links>");
  typewriter.glPrint(ispot2,144,"+ or -  <tint>");
  typewriter.glPrint(ispot2,160,"F5      <gizmo edit>");
  typewriter.glPrint(ispot2,176,"F6      <add gizmos>");
  typewriter.glPrint(ispot2,192,"F7      <add layers>");
  typewriter.glPrint(ispot2,208,"alt-S   <SAVE>");
  typewriter.glPrint(ispot2,224,"F8      <anibox edit>");
  typewriter.glPrint(ispot2,240,"F9      <rename map>");
  typewriter.glPrint(ispot2,256,"F10     <new layers>");
  typewriter.glPrint(ispot2,272,"F11     <resize>");
  typewriter.glPrint(ispot2,288,"F12     <music>");
}
