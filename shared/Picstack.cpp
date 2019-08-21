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

#include "Picstack.h"

PicNode::PicNode()
{
   //ihalfsize=0;
   //itype=0;
   //fspin=0.0;
   picnum=0;
   picnext=NULL;
}

PicNode::~PicNode()
{
}

PicBox::PicBox()
{
   pichead=NULL;
   picreturn=NULL;
}

PicBox::~PicBox()
{
   picreturn=pichead;
   if(picreturn!=NULL)
      pichead=pichead->picnext;
   while(picreturn!=NULL)
   {
      delete picreturn;
      picreturn=pichead;
   }
}

void PicBox::PushPic(int isize, int itype, int ihor, int ivert, float fspin, GLuint picnum)
{
   picreturn=new PicNode;
   //picreturn->pic=tex;
   picreturn->picnum=picnum;
   picreturn->ihalfsize=isize;
   picreturn->itype=itype;
   picreturn->fspin=fspin;
   picreturn->ihor=ihor;
   picreturn->ivert=ivert;
   picreturn->picnext=pichead;
   pichead=picreturn;
}

bool PicBox::PopPic()
{
   picreturn=pichead;
   if(pichead!=NULL)
   {
      pichead=pichead->picnext;
      delete picreturn;
      return true;
   }
   else
   {
      return false;
   }
}
