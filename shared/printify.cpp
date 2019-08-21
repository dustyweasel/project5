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

#include "printify.h"

//  BuildFont and glPrint are taken from NeHe's site, I haven't bothered figuring out how they work yet
//  http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=13

PrintBox::PrintBox()
{
}

PrintBox::~PrintBox()
{
   glDeleteLists(base,95);
}

GLvoid PrintBox::BuildFont(GLuint isteal)
{
   fontnum=isteal;  //we're passing the Font.png in OpenGL memory
   base=glGenLists(95);
   glBindTexture(GL_TEXTURE_2D, fontnum);
   for (int loop=0; loop<95; loop++)
   {
      float cx=float(loop%16)/16.0f;
      float cy=float(loop/16)/8.0f;

      glNewList(base+loop,GL_COMPILE);
      {
         glBegin(GL_QUADS);
         {
            glTexCoord2f(cx,cy);			glVertex2i(0,0);
            glTexCoord2f(cx+0.0625f,cy);		glVertex2i(16,0);
            glTexCoord2f(cx+0.0625f, cy+0.125f);	glVertex2i(16,16);
            glTexCoord2f(cx,cy+0.125f);			glVertex2i(0,16);
         }
         glEnd();
         glTranslated(16,0,0);
      }
      glEndList();
   }
}

//  http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=13
GLvoid PrintBox::glPrint(GLint x, GLint y, const char *string, ...)
{
   char text[256];
   va_list ap;

   if (string == NULL)
      return;

   va_start(ap, string);
   vsprintf(text, string, ap);
   va_end(ap);

   glBindTexture(GL_TEXTURE_2D, fontnum);
   glPushMatrix();
   glLoadIdentity();
   glTranslated(x,y,0);
   glListBase(base-32);
   glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
   glPopMatrix();
}
