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

#ifndef BOMB
#define BOMB

#include <stdlib.h>
#include <list>

struct Bomb
{
   Bomb();
   int GetDirection();

   float fhor;
   float fvert;
   float fsize;
   //0=player's team
   //1=bad guy
   //int iteam;
   int idirection;
   int iforce;
};

//finally using the STL
struct BombBox
{
  BombBox();
  void Apocalypse();
  void Reset();
  void Finish();
  void InsertTail(Bomb newbomb);
  void Next();
  bool End();
  Bomb GetBomb();
  float GetHor();
  float GetVert();
  float GetSize();
  int GetDirection();
  int GetForce();
  std::list<Bomb>::iterator GetTail();
  void ZapNode(std::list<Bomb>::iterator killer);

  std::list<Bomb> minefield;
  std::list<Bomb>::iterator bullet;
};

#endif
