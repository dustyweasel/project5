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

#include "Bomb.h"

Bomb::Bomb()
{
  fhor=0.0f;
  fvert=0.0f;
  fsize=0.0f;
  idirection=0;
  iforce=0;
}

int Bomb::GetDirection()
{
   int ival=idirection;

   if(rand()%3==0)
   {
      ival+=7;
      if(rand()%2==0)
      {
         ival-=3;
      }
      if(ival>7)
         ival-=4;
   }

   return ival;
}

BombBox::BombBox()
{
  bullet=minefield.end();
}

void BombBox::Apocalypse()
{
  minefield.resize(0);
}

void BombBox::Reset()
{
  bullet=minefield.begin();
}

void BombBox::Finish()
{
  bullet=minefield.end();
}

void BombBox::InsertTail(Bomb newbomb)
{
  minefield.push_back(newbomb);
}

void BombBox::Next()
{
  if(End()==false)
  {
    bullet++;
  }
}

bool BombBox::End()
{
  if(bullet==minefield.end())
    return true;
  else
    return false;
}

Bomb BombBox::GetBomb()
{
  Bomb kaboom;

  if(!End())
    return *bullet;
  else
    return kaboom;
}

float BombBox::GetHor()
{
  if(!End())
    return bullet->fhor;
  else
    return 0.0f;
}

float BombBox::GetVert()
{
  if(!End())
    return bullet->fvert;
  else
    return 0.0f;
}

float BombBox::GetSize()
{
  if(!End())
    return bullet->fsize;
  else
    return 0.0f;
}

int BombBox::GetDirection()
{
  if(!End())
    return bullet->GetDirection();
  else
    return 0;
}

int BombBox::GetForce()
{
  if(!End())
    return bullet->iforce;
  else
    return 0;
}

std::list<Bomb>::iterator BombBox::GetTail()
{
  Finish();
  if(minefield.empty()==false)
    bullet--;
  return bullet;
}

void BombBox::ZapNode(std::list<Bomb>::iterator killer)
{
  minefield.erase(killer);
}
