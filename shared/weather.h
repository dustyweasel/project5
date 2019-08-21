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

#ifndef WEATHER
#define WEATHER

#include <stdlib.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <math.h>
#include <time.h>
//#include <SDL/SDL.h>
//#include <SDL/SDL_mixer.h>
#include "soundmaster.h"
#include "switchmaster.h"
#include "printify.h"
//#include "BasicBox.h"

struct WeatherBox
{
   WeatherBox();
   ~WeatherBox();
   void KillBox();             //destroy everything, a destructor just for you!

   //these all get you to different weather states
   void Clearinit();                //shift to clear skies
   void Cloudinit();                //to cloudy skies
   void Raininit(int ival, int istart);  //rain (max drops, current drops, positive integers please and ival>=istart)
   void Storminit();                //bring on the lighting

   void Startrain(int ival,  int istart);           //an internal function, not for you
   void Rain();                //call this every drawing loop to animate
//   void RainUpdate(const BasicBox &primo);          //call this every main loop to animate
   bool Daycheck(bool bday);
//   void Drizzle(const BasicBox &primo);               //internal, animates rain drops
   void Modwind(float fnum);     //adds fnum radians to fwind
   void Augwind(int inum);       //modifies wind strength
   //void Zeus();                //turns lightning on or off if raining

   //these just set color
   void Day(float rgfval[]);
   void Night(float rgfval[]);
   void Bluecave(float rgfval[]);
   void Storm(float rgfval[]);
   void Lightning(float rgfval[]);

   void Colorshift();  //internal, not for you

//don't touch these unless you know what you're doing
   float **rgfcoord;
   int iweather;        //the maximum number of drops, doesn't fluctuate
   int idrop;           //number of drops to draw 0-iweather
   int idrop2;          //real # of drops to draw, for fading rain in and out
   GLfloat rgfmap[3];
   GLfloat rgfmap2[3];  //for lightning strikes
   GLfloat rgfmap3[3];  //for day change
///////////isky////////////////
   //GLfloat rgfmap4[3];
   //0==clear
   //1==thunderstorm
   //2==storm to clear
   //3==rainstorm
   //4==clear to storm
   int isky;
   int istrike;  //right now just for lighting strikes, possibly for other sub states later
///////isky2///////////////////
   //0==nothin'
   //1==lightning strike
//   int isky2;
///////////isky3////////////////////
   //0==day
   //1==night
   //2==night to day
   //3==day to night
//   int isky3;
   int icounter;  //time between night and day or cloud and clear
   int imod;  //used to store time of day for now
   float fwind; //0-359.999999999999  wind direction
   int iwind; //wind strength 0-10
   int irainx;
   int irainy;
   int rgisplash[10][3];  //store some splashes
   GLUquadricObj* quadratic;
   AudioBox *boombox;
   //int inorth;
};

#endif
