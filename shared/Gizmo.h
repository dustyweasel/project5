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

//Gizmo.h
//defined it TWO files:
//Gizmo.cpp
//Gizmoswitch.cpp

#ifndef GIZMO
#define GIZMO

#define SOUNDTOTAL 3

//the number of defined gizmo types
//  places to modify when IGIZ is increased:
//  paintmaster.cpp (editor) istate==14
//  gizmoswitch.cpp  switcher() gizupdate()
//  paintgiz.cpp
//  picpez.cpp
//  paintgizinfo() in paintmaster

//0 = standard player gizmo | NO AI     |
//1 = rat gizmo             | SIMPLE AI |
//2 = simple mill           | SPIN      |
//3 = stain                 |           |
//4 = bugs                  | SWARM AI  |
//5=  lightning bugs
//6 = dragon
#define IGIZ 7

#include <fstream>
#include "TexBox.h"
#include "soundmaster.h"
#include "icegrid.h"
#include "icedistance.h"
#include "Bomb.h"

//get rid of pointer return types?

//considered making a GizStatBox structure/linked list that would store variables like base fspeed, idewey, texbox and just give
//Gizmos a pointer to it so only one GizStatBox node for all 100 rats or whatever.  But for now every rat has own set of variables,
//the memory used is insiginificant compared to one map .png image so to hell with it for now
struct Gizmo
{
   //in Gizmo.cpp
   Gizmo();
   ~Gizmo();
   bool Gizspawn(int ival, std::string strval);
   GLuint PicSwap(std::string strval, ImageVault &picbox, int texelement);
   bool Gizgen(std::string strgiz, float spawnhor, float spawnvert, ImageVault &imagebox);
   void Gizwrite(ImageVault &picbox);
   Iceblock Gizmove(int idirection, Uint32 history, Icematrix &mapgrid);
   Iceblock Gizrun(int idirection, Uint32 history, Icematrix &mapgrid);
   bool Hitcheck(Bomb &kaboom);
   Gizmo* Hurt(float fpain,ImageVault &imagebox, AudioBox &boombox, float force, int idirection);
   void Apocalypse();
   void Gizface(int idirection);
   void Attack(AudioBox *boombox, BombBox &attacknodes);
   void SubAttack(Bomb &kaboom, AudioBox *boombox, BombBox &attacknodes);
   GLuint GetPic();
   GLuint GetPic(int inum);
   std::string GetPicName(int inum, ImageVault &picbox);
   int GetType();
   void Grow();  //pass a float to this someday
   void Shrink();
   bool Teleport(float x, float y, int idirection, Icematrix &mapgrid, bool bcenter);
   float GetHor();
   float GetVert();
   bool GetHurt();
   float GetSize();
   float GetSpin();
   float GetHealth();
   int GetState();
   int GetSpawnType();
   void SetSpawnType(int ival);
   std::string GetName();
   int GetMax();
   void SetSound(int ival, std::string strval);
   std::string GetSoundName(int ival);
//in Gizmoswitch.cpp  (this is the file you update if you add new Gizmo types)
   Gizmo* gizupdate(Gizmo *enemy, Icematrix &mapgrid, ImageVault &picbox, AudioBox &boombox, Uint32 history, BombBox &attacknodes);

private:
//in Gizmo.cpp
   Iceblock Gizsubmove(int idirection, float fmove, Icematrix &mapgrid);  //only used by Gizmove I think
   void SlamSet(int idirection, float force);
   Iceblock Gizslam(Uint32 history, Icematrix &mapgrid);
   void Gizcalm(Icematrix &mapgrid, Uint32 history,BombBox &attacknodes);  //called by gizupdate()
   void Die(AudioBox &boombox);
   bool Hitcheck(Gizmo *killer);
//in Gizmoswitch.cpp
   bool Switcher(int inum);
   Iceblock MoveAI(Iceblock icearray[], int ilen);

   std::string name;          //name of the gizmo file
   float fhor;
   float fvert;
   float fspeed;
   float basespeed;
   float fsize;          //radius in pixels (units)
   //float basesize;       //not actually using this yet
   int itype;            //type for AI and stuff
   int spawntype;        //not actually stored in .giz file
   int iturn;            //used for AI, records how much time you want to pass before new command is issued
   int iorder;           //see the AI code
   float fspin;          //for windmills and stuff
   float fhitpoints;
   int ipics;            //# of Gizmo pics
   int idewey[6];        //see gizmoswitch.cpp
   GLuint iauto;            //the image we're on
   std::string soundfiles[SOUNDTOTAL];

   int itimer;           //strictly used to time bhurt
   float slamdistance;
   float fupdate;        //fupdate generally stores how many pixels Gizmo moved since last pic change and stuff
//could get rid of fupdate, fmoment, fpix, fspin, fspeed and make switches for itype, save memory or use GixStatBox but seems like overkill for now
   float fpix;           //tied to fupdate, the number of pixels you want this gizmo to move before you change sprites
   float fmoment;        //similar to fpix, time between attack frames
   int igizstate;        //see manual if i ever wrote it
   bool bhurt;           //is Gizmo invincible?
   std::list<Bomb>::iterator bombkeeper;

   TexBox giztex;
};

#endif

//0==pain
//1==death
//2==attack
//std::string soundfiles
