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

#include "Gizbox.h"

GizNode::GizNode()
{
   //giz=NULL;
   gizprev=NULL;
   giznext=NULL;
}

GizNode::~GizNode()
{
   //if(giz!=NULL)
   //   delete giz;
}

GizBox::GizBox()
{
   gizreturn=NULL;
   gizhead=NULL;
   giztail=NULL;
   igizsize=0;
}

GizBox::~GizBox()
{
   gizreturn=giztail;
   while(gizreturn!=NULL)
   {
      giztail=giztail->gizprev;
      delete gizreturn;
      gizreturn=giztail;
   }
}

//if this returns false you better free *newgiz from memory
bool GizBox::InsertTail(Gizmo *newgiz)
{
  bool breturn=false;

  if(newgiz!=NULL)
  {
    try
    {
      gizreturn=new GizNode;
      if(giztail==NULL)
      {
        giztail=gizreturn;
        gizhead=gizreturn;
      }
      else
      {
        giztail->giznext=gizreturn;
        gizreturn->gizprev=giztail;
        giztail=gizreturn;
      }
      igizsize+=1;
      giztail->giz=newgiz;
      breturn=true;
    }
    catch(std::bad_alloc&)
    {
      //just return false
    }
  }
  return breturn;
}

//if this returns false you better free *newgiz from memory
bool GizBox::InsertHead(Gizmo *newgiz)
{
  bool breturn=false;

  if(newgiz!=NULL)
  {
    try
    {
      gizreturn=new GizNode;
      if(giztail==NULL)
      {
         giztail=gizreturn;
         gizhead=gizreturn;
      }
      else
      {
         gizhead->gizprev=gizreturn;
         gizreturn->giznext=gizhead;
         gizhead=gizreturn;
      }
      igizsize+=1;
      gizhead->giz=newgiz;
      breturn=true;
    }
    catch(std::bad_alloc&)
    {
      //don't do anything
    }
  }
  return breturn;
}

//icopy = #of copies 0 = 1 gizmo, 1=2 gizmos, etc.
bool GizBox::InsertNode(std::string &rgcfilename, int hor, int vert, int icopy, bool bhead, ImageVault &picbox)
{
  int ij;
  Gizmo *fungiz;
  bool breturn=true;

  icopy+=1;

  for(ij=0;ij<icopy;ij++)
  {
    try
    {
      fungiz=new Gizmo;
      breturn=fungiz->Gizgen(rgcfilename,hor,vert,picbox);
      if(!bhead&&breturn)
        breturn=InsertTail(fungiz);
      else if(breturn)
        breturn=InsertHead(fungiz);

      if(!breturn)
      {
        delete fungiz;
        breturn=false;
        ij=icopy;
      }
    }
    catch(std::bad_alloc&)
    {
      breturn=false;
      ij=icopy;
    }
  }
  return breturn;
}

bool GizBox::ZapGiz()
{
  if(gizreturn!=NULL)
  {
    if(gizreturn->gizprev!=NULL)
      gizreturn->gizprev->giznext=gizreturn->giznext;
    if(gizreturn->giznext!=NULL)
      gizreturn->giznext->gizprev=gizreturn->gizprev;

    if(gizreturn==gizhead)
      gizhead=gizhead->giznext;
    if(gizreturn==giztail)
      giztail=giztail->gizprev;

    delete gizreturn;
    gizreturn=NULL;
    igizsize-=1;

    return true;
  }
  else
  {
    return false;
  }
}

void GizBox::KillGizBox()
{
   gizreturn=giztail;

   while(gizreturn!=NULL)
   {
      giztail=giztail->gizprev;
      delete gizreturn;
      gizreturn=giztail;
   }

   gizhead=NULL;
   giztail=NULL;
   gizreturn=NULL;
   igizsize=0;
}

GLuint GizBox::GetPic()
{
   if(gizreturn!=NULL)
      return gizreturn->giz->GetPic();
   else
      return 0;
}

GLuint GizBox::GetPic(int inum)
{
   if(gizreturn!=NULL)
      return gizreturn->giz->GetPic(inum);
   else
      return 0;
}

void GizBox::Reset()
{
   gizreturn=gizhead;
}

void GizBox::Next()
{
   if(gizreturn!=NULL)
      gizreturn=gizreturn->giznext;
}

//0=1st gizmo, like an array
bool GizBox::GizTaxi(int ival)
{
  int ix=0;

  if(ival<igizsize)
  {
    gizreturn=gizhead;
    while(ix<ival)
    {
      gizreturn=gizreturn->giznext;
      ix+=1;
    }
    return true;
  }
  else
  {
    return false;
  }
}

//this one checks for collisions and hurts the *enemy
void GizBox::Update(Gizmo *enemy, Icematrix &mapgrid, Uint32 history, ImageVault &picbox, AudioBox &boombox, BombBox &attacknodes,
                    GizBox &splatterbox)
{
  gizreturn=gizhead;
  while(gizreturn!=NULL)
  {
    //could possibly have splatterbox insert nodes into itself, like if blood stains multiply or whatever
    splatterbox.InsertTail(gizreturn->giz->gizupdate(enemy,mapgrid,picbox,boombox,history,attacknodes));
    if(splatterbox.GetGizBoxSize()>SPLATTERMAX)
    {
      splatterbox.Reset();
      splatterbox.ZapGiz();
    }
    gizreturn=gizreturn->giznext;
  }
}

//Victimizes the GizBox
void GizBox::Victimize(Gizmo *attacker, AudioBox *boombox, ImageVault *picbox)
{
/*   Bomb *kaboom;
   Gizmo *pez;

   kaboom=attacker->Attack(boombox);

   if(kaboom!=NULL)
   {
      gizreturn=gizhead;
      while(gizreturn!=NULL)
      {
         if(gizreturn->giz->Hitcheck(kaboom))
         {
            pez=gizreturn->giz->Hurt(1.0f,picbox,boombox,kaboom->GetForce(),kaboom->GetDirection());
            //send GizBox::Update another GizBox so it can insert bloodstains into it
            InsertHead(pez);
         }
         gizreturn=gizreturn->giznext;
      }

      //instead of deleting it put it into a BombBox and give it a timer to make it last as long as the attack
      delete kaboom;
   }*/
}

int GizBox::GetGizBoxSize()
{
   return igizsize;
}

bool GizBox::GetHurt()
{
   if(gizreturn!=NULL)
      return gizreturn->giz->GetHurt();
   else
      return false;
}

int GizBox::GetHor()
{
   if(gizreturn!=NULL)
      return gizreturn->giz->GetHor();
   else
      return -1;
}

int GizBox::GetVert()
{
   if(gizreturn!=NULL)
      return gizreturn->giz->GetVert();
   else
      return -1;
}

int GizBox::GetType()
{
   if(gizreturn!=NULL)
      return gizreturn->giz->GetType();
   else
      return -1;
}

//returns fsize of current gizmo
float GizBox::GetSize()
{
   if(gizreturn!=NULL)
      return gizreturn->giz->GetSize();
   else
      return 0.0f;
}

float GizBox::GetSpin()
{
   if(gizreturn!=NULL)
      return gizreturn->giz->GetSpin();
   else
      return 0.0f;
}

int GizBox::GetSpawnType()
{
  if(gizreturn!=NULL)
    return gizreturn->giz->GetSpawnType();
  else
    return -1;
}

bool GizBox::SetSpawnType(int ival)
{
  if(gizreturn!=NULL)
  {
    gizreturn->giz->SetSpawnType(ival);
    return true;
  }
  return false;
}

std::string GizBox::GetName()
{
  std::string strval;

  if(gizreturn!=NULL)
    strval=gizreturn->giz->GetName();

  return strval;
}

bool GizBox::End()
{
   if(gizreturn==NULL)
      return true;
   else
      return false;
}

//bool Gizmo::Teleport(float x, float y, int idirection, Icematrix &mapgrid)
bool GizBox::Warp(float x, float y, Icematrix &mapgrid)
{
  bool breturn=false;

  if(gizreturn!=NULL)
    breturn=gizreturn->giz->Teleport(x,y,0,mapgrid,true);

  return breturn;
}

//get rid of this
bool GizBox::Clear()  //returns true if all monsters are dead
{
  bool breturn=true;

  Reset();
  while(End()==false)
  {
    if(gizreturn->giz->GetState()!=1000000)
      breturn=false;
    Next();
  }

  return breturn;
}
