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

#include "TexBox.h"

TexBox::TexBox()
{
   itexsize=0;
   texnums=NULL;
}

TexBox::~TexBox()
{
   if(texnums!=NULL)
      delete[] texnums;
}

bool TexBox::CreateBox(int ival)
{
  bool breturn=false;
  int ix;

  KillTexBox();
  if(ival>0)
  {
    try
    {
      texnums=new GLuint[ival];
      itexsize=ival;
      for(ix=0;ix<itexsize;ix++)
        texnums[ix]=0;
      breturn=true;
    }
    catch(std::bad_alloc&)
    {
      //if TexBox not allocated, who cares
    }
  }
  return breturn;
}

//returns old value if successful, 0 otherwise
GLuint TexBox::InsertTex(std::string rgcpic, int itex, ImageVault &picbox)
{
  GLuint GLval=0;

  if(itex>=0&&itex<itexsize)
  {
    GLval=texnums[itex];
    if(!picbox.ImageLoader(rgcpic,texnums[itex]))
      GLval=0;
  }

  return GLval;
}

GLuint TexBox::GetPic(int inum)
{
   if(inum<itexsize&&inum>=0)
      return texnums[inum];
   else
      return 0;
}

void TexBox::KillTexBox()
{
   if(texnums!=NULL)
      delete[] texnums;

   itexsize=0;
   texnums=NULL;
}
