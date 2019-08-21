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

#include "animate.h"

Anibox::Anibox()
{
   name="";
   saveticks=-1;
   ipics=NULL;
   itype=0;
   isize=0;
   ireturn=0;
   iloop=0;
}

Anibox::~Anibox()
{
   if(ipics!=NULL)
      delete[] ipics;
}

void Anibox::Death()
{
   name="";
   saveticks=-1;
   if(ipics!=NULL)
      delete[] ipics;
   ipics=NULL;
   isize=0;
   itype=0;
   ireturn=0;
   iloop=0;
}

bool Anibox::Spawnbox(std::string anifile, ImageVault &picbox)
{
  std::ifstream infile;
  int ix;
  std::string temp;
  bool breturn=false;

  temp=Pathfinder::Anibox_Path+anifile;
  if(Normal_File(temp))
  {
    infile.open(temp.c_str(),std::ios::in|std::ios::binary);
    breturn=!infile.fail();
  }
  if(breturn)
  {
    Death();

    name=anifile;

    infile>>itype;
    infile>>isize;
    infile>>iloop;
    infile.ignore();
    if(isize>0)
    {
      try
      {
        ipics=new GLuint[isize];

        for(ix=0;ix<isize;ix++)
        {
          getline(infile,temp);
          //temp="Data/Images/"+temp;
          picbox.ImageLoader(temp,ipics[ix]);
        }
      }
      catch(std::bad_alloc&)
      {
        Death();
        breturn=false;
      }
    }
    else
    {
      Death();
      breturn=false;
    }
  }
  infile.close();

  return breturn;
}

void Anibox::Writebox(ImageVault &picbox)
{
  std::ofstream outfile;
  int ix;

  outfile.open((Pathfinder::Anibox_Path+name).c_str(),std::ios::out|std::ios::binary);
  outfile<<itype<<"\n"
         <<isize<<"\n"
         <<iloop<<"\n";
  for(ix=0;ix<isize;ix++)
    outfile<<picbox.GetName(ipics[ix]).c_str()<<"\n";

  outfile.close();
}

GLuint Anibox::Getpic()
{
   if(ipics!=NULL)
      return ipics[ireturn];
   else
      return 0;
}

GLuint Anibox::Getpic(int ival)
{
  if(ival<isize)
    return ipics[ival];
  else
    return 0;
}

//returns formerly loaded GLuint in case you
//want to delete it or 0 if there's a problem
GLuint Anibox::Swap_Pic(std::string strpic, int element, ImageVault &picbox)
{
  GLuint GLval=0;

  if(element>=0&&element<isize)
  {
    GLval=ipics[element];
    if(!picbox.ImageLoader(strpic,ipics[element]))
      GLval=0;
  }

  return GLval;
}

void Anibox::Update(Uint32 newticks)
{
   if(saveticks==-1)
   {
      saveticks=newticks;
   }
   else if(newticks-saveticks>100)
   {
      ireturn+=1;
      if(ireturn>=isize)
         ireturn=iloop;
      saveticks=newticks;
   }
}

bool Anibox::Loaded()
{
   if(ipics==NULL)
      return false;
   else
      return true;
}

std::string Anibox::GetName()
{
   return name;
}

/*void Anibox::SetName(std::string strval)
{
  name=strval;
}*/

int Anibox::GetType()
{
  return itype;
}

void Anibox::SetType(int ival)
{
  itype=ival;
}

int Anibox::GetSize()
{
  return isize;
}

bool Anibox::SetSize(std::string strval, int ival, int newtype)
{
  bool breturn=false;
  int ix;

  Death();
  isize=ival;

  if(isize>0)
  {
    try
    {
      ipics=new GLuint[isize];
      for(ix=0;ix<isize;ix++)
        ipics[ix]=0;
      name=strval;
      itype=newtype;
      breturn=true;
    }
    catch(std::bad_alloc&)
    {
      Death();
      breturn=false;
    }
  }

  return breturn;
}

int Anibox::GetLoop()
{
  return iloop;
}

bool Anibox::SetLoop(int ival)
{
  if(ival>=0&&ival<isize)
  {
    iloop=ival;

    return true;
  }
  else
  {
    return false;
  }
}
