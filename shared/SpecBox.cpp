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

#include "SpecBox.h"

Speckeeper::Speckeeper()
{
  Death();
}

void Speckeeper::Death()
{
  name="";
  icespec[0]=0;
  icespec[1]=0;
  icespec[2]=0;
}

SpecNode::SpecNode()
{
  specnext=NULL;
}

SpecNode::~SpecNode()
{
}

SpecBox::SpecBox()
{
   spechead=NULL;
   spectail=NULL;
   specreturn=NULL;
   specsize=0;
}

SpecBox::~SpecBox()
{
   while(spechead!=NULL)
   {
      specreturn=spechead->specnext;
      delete spechead;
      spechead=specreturn;
   }
}

void SpecBox::Reset()
{
  specreturn=spechead;
}

void SpecBox::Next()
{
  if(specreturn!=NULL)
    specreturn=specreturn->specnext;
}

bool SpecBox::End()
{
  if(specreturn==NULL)
    return true;
  else
    return false;
}

std::string SpecBox::GetName()
{
  std::string strval;

  if(specreturn!=NULL)
    strval=specreturn->specval.name;

  return strval;
}

Speckeeper SpecBox::GetNode()
{
  Speckeeper specval;

  if(specreturn!=NULL)
    specval=specreturn->specval;

  return specval;
}

bool SpecBox::InsertTail(int ival1, int ival2, int ival3, std::string rgcval)
{
  bool breturn=true;

  if(spectail!=NULL)
  {
    try
    {
      spectail->specnext=new SpecNode;
      spectail=spectail->specnext;
    }
    catch(std::bad_alloc&)
    {
      breturn=false;
    }
  }
  else
  {
    try
    {
      spectail=new SpecNode;
      spechead=spectail;
      specreturn=spectail;
    }
    catch(std::bad_alloc&)
    {
      breturn=false;
    }
  }
  if(breturn)
  {
    spectail->specval.icespec[0]=ival1;
    spectail->specval.icespec[1]=ival2;
    spectail->specval.icespec[2]=ival3;
    spectail->specval.name=rgcval;
    specsize+=1;
  }
  return breturn;
}

bool SpecBox::Clone(Speckeeper &specimen)
{
  if(specreturn!=NULL)
  {
    specreturn->specval=specimen;
    return true;
  }
  else
  {
    return false;
  }
}

bool SpecBox::SpecTaxi(int ival)
{
   int ix=0;

   if(ival<specsize)
   {
      specreturn=spechead;
      while(ix<ival)
      {
         specreturn=specreturn->specnext;
         ix+=1;
      }
      return true;
   }
   else
   {
      return false;
   }
}

void SpecBox::KillSpecBox()
{
   while(spechead!=NULL)
   {
      specreturn=spechead->specnext;
      delete spechead;
      spechead=specreturn;
   }
   spechead=NULL;
   spectail=NULL;
   specreturn=NULL;
   specsize=0;
}

bool SpecBox::ZapSpecNode(int inum)
{
   int ix=0;
   SpecNode *temp;

   if(inum<specsize)
   {
      if(inum==0)
      {
         temp=spechead;
         spechead=spechead->specnext;
         delete temp;
      }
      else
      {
         specreturn=spechead;
         while(ix<inum-1)
         {
            specreturn=specreturn->specnext;
            ix+=1;
         }
         temp=specreturn->specnext;
         specreturn->specnext=temp->specnext;
         delete temp;
         if(temp==spectail)
            spectail=specreturn;
      }
      specsize-=1;
      if(specsize==0)
         KillSpecBox();
   }
}

int SpecBox::GetSize()
{
  return specsize;
}
