/***************************************************************************
 *   Copyright (C) 2008 by icecubeflower                                   *
 *   icecube@icebox                                                        *
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

#include "icegrid.h"

Iceblock::Iceblock()
{
   terrain=0;
}

Iceblock::~Iceblock()
{
}

void Iceblock::operator =(Iceblock iceval)
{
   terrain=iceval.terrain;
}

bool Iceblock::operator ==(int ival)
{
   if(terrain==ival)
      return true;
   else
      return false;
}

void Iceblock::operator =(int ival)
{
   terrain=ival;
}

bool Iceblock::operator !=(int ival)
{
   if(terrain==ival)
      return false;
   else
      return true;
}

bool Iceblock::operator <(int ival)
{
   if(terrain<ival)
      return true;
   else
      return false;
}

bool Iceblock::operator >(int ival)
{
   if(terrain>ival)
      return true;
   else
      return false;
}

void Iceblock::operator +=(int ival)
{
   terrain+=ival;
}

void Iceblock::operator -=(int ival)
{
   terrain-=ival;
}

int Iceblock::operator -(int ival)
{
   return terrain-ival;
}

Icematrix::Icematrix()
{
   icemaster=NULL;
   icol=0;
   irow=0;
}

Icematrix::~Icematrix()
{
   Killmatrix();
}

//still need to test fail scenerio
bool Icematrix::Rematrix(int newrow, int newcol)
{
  int ix;
  bool breturn=false;

  if(newrow>0&&newcol>0)
  {
    breturn=true;
    Killmatrix();
    icol=newcol;
    irow=newrow;
    try
    {
      icemaster=new Iceblock*[irow];
      for(ix=0;ix<irow;ix++)
      {
        try
        {
          icemaster[ix]=new Iceblock[icol];
        }
        catch(std::bad_alloc&)
        {
          ix-=1;
          while(ix>=0)
          {
            delete[] icemaster[ix];
            ix--;
          }
          delete[] icemaster;
          icemaster=NULL;
          breturn=false;
          ix=irow;
          irow=0;
          icol=0;
        }
      }
    }
    catch(std::bad_alloc&)
    {
      //icemaster=NULL;  if new fails does the pointer still point where it did before?
      irow=0;
      icol=0;
    }
  }
  return breturn;
}

//start at top left corner, move down y then move right x
Iceblock Icematrix::Grab_Element(int grabrow, int grabcol)
{
   Iceblock iceval;

   if(grabrow>=0&&grabrow<irow&&grabcol>=0&&grabcol<icol)
      iceval=icemaster[grabrow][grabcol];

   return iceval;
}

bool Icematrix::Set_Element(int setrow, int setcol, Iceblock iceval)
{
  if(setrow>=0&&setrow<irow&&setcol>=0&&setcol<icol)
  {
    icemaster[setrow][setcol]=iceval;
    return true;
  }
  else
  {
    return false;
  }
}

int Icematrix::Get_Rows()
{
   return irow;
}

int Icematrix::Get_Columns()
{
   return icol;
}

void Icematrix::Killmatrix()
{
   int ix;

   for(ix=0;ix<irow;ix++)
   {
      delete[] icemaster[ix];
   }
   if(irow!=0)
      delete[] icemaster;

   irow=0;
   icol=0;
}

void Icematrix::Writematrix(std::ofstream &outfile)
{
  int ix, ij;

  outfile<<irow<<"\n"<<icol<<"\n";
  for(ix=0;ix<irow;ix++)
  {
    for(ij=0;ij<icol;ij++)
      outfile<<icemaster[ix][ij].terrain<<" ";
    outfile<<"\n";
  }
}

//You must send this a legit infile, if you opened a directory this will
//crash at infile>>ix.  If file is filled with garbage it will probably be
//fine
bool Icematrix::Readmatrix(std::ifstream &infile)
{
  int ix, ij;
  bool breturn=false;

  Killmatrix();

  infile>>ix;
  infile>>ij;
  if(infile.fail()==false)
  {
      //if it fails let it run for loop, irow will be zero
    breturn=Rematrix(ix,ij);
    for(ix=0;ix<irow;ix++)
    {
      for(ij=0;ij<icol;ij++)
      {
        infile>>icemaster[ix][ij].terrain;
      }
    }
    infile.ignore(); //eat that last '32'
    //if matrix spawned successfully but infile failed in for loops,
    //who cares, matrix exists, return true
  }
  return breturn;
}
