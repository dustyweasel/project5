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

#include "weather.h"

/////////////////////////////////////////////////////constructor///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WeatherBox::WeatherBox()
{
   int ix;

   iweather=0;
   idrop=0;
   idrop2=0;
   isky=0;  //clear
   //imap=0;  //nothin'
   istrike=0;
   for(ix=0;ix<10;ix++)
      rgisplash[ix][2]=0;
   srand(time(NULL));

   iwind=rand()%2;  //wind strenth is 0 to 10 but usually at 0 to 2.  10 is like a hurricaine.
   fwind=float(rand()%360);  //cos() and sin() take radians
   fwind=(fwind*2.0f*M_PI)/360.0f;
   //if(fwind>0&&fwind<M_PI)
   //   inorth=-1;  //north
   //else
   //   inorth=1;   //south

   imod=rand()%DAYLEN; //0-149000=day 150000-299999=night, 300000-450000=day, etc.

   imod=0;  //hey i'm progamming here!
   iwind=0;

   if(imod%DAYLEN<DAYLEN/2)
   {
      isky=0;
      Day(rgfmap);
   }
   else
   {
      isky=1;
      Night(rgfmap);
   }

   quadratic=gluNewQuadric();   // Create A Pointer To The Quadric Object
   //now do a random weather thing
}

//////////////////////////////////////////////destructor///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WeatherBox::~WeatherBox()
{
   int ix;

   for(ix=0;ix<iweather;ix++)
   {
      delete []rgfcoord[ix];
   }
   if(iweather>0)
   {
      delete []rgfcoord;
   }
   //boombox.Killsound(0);  what's the point
   //boombox.Killsound(1);
   gluDeleteQuadric(quadratic);
}

//////////////////////////////////////////////////////////////////KillBox()/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeatherBox::KillBox()
{
   int ix;

   for(ix=0;ix<iweather;ix++)
   {
      delete []rgfcoord[ix];
   }
   if(iweather>0)
   {
      delete []rgfcoord;
   }
   iweather=0;
   idrop=0;
   idrop2=0;
//   boombox->Fadesound(0,1000);
//   boombox->Fadesound(1,1000);
//   boombox->Fadesound(2,1000);
   //change this when daytimes work
   //isky=0;
}

////////////////////////////////////////////////////////////////////////Clearinit()//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeatherBox::Clearinit()
{
   switch(isky)
   {
///////////////////////day clear////////////////
   case 0:
      //already clear
      break;
///////////////////////night clear////////////////
   case 1:
      //already clear
      break;
///////////////////////day to night clear////////////////
   case 2:
      //already clear
      break;
//////////////////////night to day clear////////////////
   case 3:
      //already clear
      break;
///////////////////////day cloud////////////////
   case 4:
      Day(rgfmap3);
      icounter=0;
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/CLOUDSHIFT;
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/CLOUDSHIFT;
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/CLOUDSHIFT;
      isky=9;  //day could to clear
      break;
///////////////////////night cloud////////////////
   case 5:
      //Night(rgfmap3);
      icounter=0;
      //rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/CLOUDSHIFT;
      //rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/CLOUDSHIFT;
      //rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/CLOUDSHIFT;
      isky=11;  //night could to clear
      break;
///////////////////day to night cloud/////////////////
   case 6:
      //Night(rgfmap3);
      //rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(DAYSHIFT-icounter);
      //rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(DAYSHIFT-icounter);
      //rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(DAYSHIFT-icounter);
      isky=2;  //day to night clear
      break;
///////////////////night to day cloud/////////////
   case 7:
      Day(rgfmap3);
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(DAYSHIFT-icounter);
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(DAYSHIFT-icounter);
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(DAYSHIFT-icounter);
      isky=3;  //night to day clear
      break;
////////////////day clear to cloud///////////////
   case 8:
      //not now
      break;
/////////////////day cloud to clear////////////
   case 9:
      //not now
      break;
/////////////night clear to cloud//////////////
   case 10:
      //not now
      break;
/////////////////night cloud to clear////////////
   case 11:
      //not now
      break;
/////////////////day rain////////////
   case 12:
      idrop=0;
//      boombox->Fadesound(1,1000);
      Day(rgfmap3);
      icounter=0;
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/CLOUDSHIFT;
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/CLOUDSHIFT;
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/CLOUDSHIFT;
      isky=17;  //day rain to clear
      break;
/////////////////night rain////////////
   case 13:
      idrop=0;
//      boombox->Fadesound(1,1000);
      //Night(rgfmap3);
      icounter=0;
      //rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/CLOUDSHIFT;
      //rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/CLOUDSHIFT;
      //rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/CLOUDSHIFT;
      isky=19;  //night rain to clear
      break;
/////////////////day to night rain////////////
   case 14:
      KillBox();
      //Night(rgfmap3);
      //rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(DAYSHIFT-icounter);
      //rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(DAYSHIFT-icounter);
      //rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(DAYSHIFT-icounter);
      isky=2;  //day to night clear
      break;
/////////////////night to day rain////////////
   case 15:
      KillBox();
      Day(rgfmap3);
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(DAYSHIFT-icounter);
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(DAYSHIFT-icounter);
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(DAYSHIFT-icounter);
      isky=3;  //night to day clear
      break;
/////////////////day clear to rain////////////
   case 16:
      //not now
      break;
/////////////////day rain to clear////////////
   case 17:
      //not now
      break;
/////////////////night clear to rain////////////
   case 18:
      //not now
      break;
/////////////////night rain to clear////////////
   case 19:
      //not now
      break;
   }
/*//////////////////rainstorm or thunderstorm//////////////////////////
   case 3:
   case 1:  //case 1 and 3 should be identical
   //   boombox->Killsound(1);  //
   //   boombox->Fadesound(1,1000);  //rain
      isky=2;
      boombox->Fadesound(0,5000);
      boombox->Fadesound(1,5000);
      boombox->Fadesound(2,5000);
      switch(isky3)
      {
      case 0:  //day
         Day(rgfmap3);
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(iweather);
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(iweather);
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(iweather);
         icounter=0;
         break;
      case 1:  //night
         break;
      case 2:  //night to day
         Day(rgfmap3);
         //rgfmap3 was a small float to gradually add to rgfmap until it was at storm pigment
         //now storm is gone so change to day pigment  DAYSHIFT-icounter=cycles remaining until daylight
         //so speeds up addition to make Day pigment after DAYSHIFT total cycles even though some cycles gone already
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(DAYSHIFT-icounter);
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(DAYSHIFT-icounter);
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(DAYSHIFT-icounter);
         break;
      }
      break;
//////////////////////storm to clear//////////////////////////////////
   case 2:
      break;
//////////////////////clear to storm///////////////////////////
   case 4:
      break;
   }*/
}

////////////////////////////////////////////////////////////////////////////Cloudinit()////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeatherBox::Cloudinit()
{
   //if(iweather>0)
   //   KillBox();

   switch(isky)
   {
///////////day clear///////////////////////
   case 0:
      Storm(rgfmap3);
      icounter=0;
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/CLOUDSHIFT;
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/CLOUDSHIFT;
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/CLOUDSHIFT;
      isky=8;  //day  clear to cloud
      break;
//////////////night clear//////////////////
   case 1:
      icounter=0;
      isky=10;  //night clear to cloud  (same color for now)
      break;
///////////////day to night clear///////////////
   case 2:
      //Night(rgfmap3);
      //rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(DAYSHIFT-icounter);
      //rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(DAYSHIFT-icounter);
      //rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(DAYSHIFT-icounter);
      isky=6;  //day to night cloud
      break;
//////////////night to day clear//////////////////
   case 3:
      Storm(rgfmap3);
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(DAYSHIFT-icounter);
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(DAYSHIFT-icounter);
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(DAYSHIFT-icounter);
      isky=7;  //night to day cloud
      break;
//////////////day cloud//////////////////////
   case 4:
      //not now
      break;
//////////////night cloud//////////////////////
   case 5:
      //not now
      break;
/////////////day to night cloud///////////////////////
   case 6:
      //not now
      break;
/////////////night to day cloud///////////////////////
   case 7:
      //not now
      break;
////////////day clear to cloud////////////////////////
   case 8:
      //not now
      break;
///////////day cloud to clear/////////////////////////
   case 9:
      //not now
      break;
////////////night clear to cloud////////////////////////
   case 10:
      //not now
      break;
/////////////night cloud to clear///////////////////////
   case 11:
      //not now
      break;
/////////////day rain///////////////////////
   case 12:
      KillBox();
      isky=4;  //day cloud
      break;
/////////////night rain///////////////////////
   case 13:
      KillBox();
      isky=5;  //night cloud
      break;
/////////////day to night rain///////////////////////
   case 14:
      KillBox();
      isky=6;  //day to night cloud
      break;
/////////////night to day rain///////////////////////
   case 15:
      KillBox();
      isky=7;  //night to day cloud
      break;
/////////////day clear to rain///////////////////////
   case 16:
      //not now
      break;
/////////////day rain to clear///////////////////////
   case 17:
      //not now
      break;
/////////////night clear to rain///////////////////////
   case 18:
      //not now
      break;
/////////////night rain to clear///////////////////////
   case 19:
      //not now
      break;
   }
}

///////////////////////////////////////////////////////////////////////Raininit()/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeatherBox::Raininit(int ival, int istart)
{
   //isky=4; //clear to storm  (might already be cloudy, maybe color won't change, not actually "clear" to storm)
   switch(isky)
   {
//////////////day clear////////////
   case 0:
      Startrain(ival, istart);
      Storm(rgfmap3);
      icounter=0;
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/CLOUDSHIFT;
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/CLOUDSHIFT;
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/CLOUDSHIFT;
      isky=16;  //day  clear to rain

      /*Storm(rgfmap3);
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(iweather);
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(iweather);
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(iweather);
      icounter=0;*/
      break;
//////////////night clear///////////////////////
   case 1:
      Startrain(ival, istart);
      //Night(rgfmap3);
      icounter=0;
      //rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/CLOUDSHIFT;
      //rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/CLOUDSHIFT;
      //rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/CLOUDSHIFT;
      isky=18;  //night  clear to rain
      break;
//////////////day to night clear////////////////////
   case 2:
      Startrain(ival, istart);
      //Night(rgfmap3);
      //rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(DAYSHIFT-icounter);
      //rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(DAYSHIFT-icounter);
      //rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(DAYSHIFT-icounter);
      isky=14;  //day to night rain
      break;
////////////////night to day clear/////////////////////
   case 3:
      Startrain(ival, istart);
      Storm(rgfmap3);
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(DAYSHIFT-icounter);
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(DAYSHIFT-icounter);
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(DAYSHIFT-icounter);
      isky=15;  //night to day rain
      break;
////////////////day cloud/////////////////////
   case 4:
      Startrain(ival, istart);
      isky=12;  //day rain
      break;
////////////////night cloud/////////////////////
   case 5:
      Startrain(ival, istart);
      isky=13;  //night rain
      break;
////////////////day to night cloud/////////////////////
   case 6:
      Startrain(ival, istart);
      isky=14;  //day to night rain
      break;
////////////////night to day cloud/////////////////////
   case 7:
      Startrain(ival, istart);
      isky=15;  //night to day rain
      break;
////////////////day clear to cloud/////////////////////
   case 8:
      //not now
      break;
////////////////day cloud to clear/////////////////////
   case 9:
      //not now
      break;
////////////////night clear to cloud/////////////////////
   case 10:
      //not now
      break;
////////////////night cloud to clear/////////////////////
   case 11:
      //not now
      break;
////////////////day rain/////////////////////
   case 12:
      //not now
      break;
////////////////night rain/////////////////////
   case 13:
      //not now
      break;
////////////////day to night rain/////////////////////
   case 14:
      //not now
      break;
////////////////night to day rain/////////////////////
   case 15:
      //not now
      break;
////////////////day clear to rain/////////////////////
   case 16:
      //not now
      break;
////////////////day rain to clear/////////////////////
   case 17:
      //not now
      break;
////////////////night clear to rain/////////////////////
   case 18:
      //not now
      break;
////////////////night rain to clear/////////////////////
   case 19:
      //not now
      break;
   /*case 0:  //day
      Storm(rgfmap3);
      rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/(iweather);
      rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/(iweather);
      rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/(iweather);
      icounter=0;
      break;
   case 1:  //night
      icounter=0;
      break;
   case 2:  //night to day
      break;
   case 3:  //day to night
      break;*/
   }
}

/////////////////////////////////////////////////////////////////////Storminit()//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeatherBox::Storminit()
{
   //isky=4; //clear to storm  (might already be cloudy, maybe color won't change, not actually "clear" to storm)
   switch(isky)
   {
//////////////day clear////////////
   case 0:
      //no
      break;
//////////////night clear///////////////////////
   case 1:
      //no
      break;
//////////////day to night clear////////////////////
   case 2:
      //no
      break;
////////////////night to day clear/////////////////////
   case 3:
      //no
      break;
////////////////day cloud/////////////////////
   case 4:
      //no
      break;
////////////////night cloud/////////////////////
   case 5:
      //no
      break;
////////////////day to night cloud/////////////////////
   case 6:
      //no
      break;
////////////////night to day cloud/////////////////////
   case 7:
      //no
      break;
////////////////day clear to cloud/////////////////////
   case 8:
      //not now
      break;
////////////////day cloud to clear/////////////////////
   case 9:
      //not now
      break;
////////////////night clear to cloud/////////////////////
   case 10:
      //not now
      break;
////////////////night cloud to clear/////////////////////
   case 11:
      //not now
      break;
////////////////day rain/////////////////////
   case 12:
      isky=20;
      break;
////////////////night rain/////////////////////
   case 13:
      isky=21;
      break;
////////////////day to night rain/////////////////////
   case 14:
      isky=22;
      break;
////////////////night to day rain/////////////////////
   case 15:
      isky=23;
      break;
////////////////day clear to rain/////////////////////
   case 16:
      //not now
      break;
////////////////day rain to clear/////////////////////
   case 17:
      //not now
      break;
////////////////night clear to rain/////////////////////
   case 18:
      //not now
      break;
////////////////night rain to clear/////////////////////
   case 19:
      //not now
      break;
////////////////day storm/////////////////////
   case 20:
      //no
      break;
////////////////night storm/////////////////////
   case 21:
      //no
      break;
////////////////day to night storm/////////////////////
   case 22:
      //no
      break;
////////////////night to day storm/////////////////////
   case 23:
      //no
      break;
   }
}

//////////////////////////////////////////////////////////////////////////Startrain()///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//an internal function, not for user
void WeatherBox::Startrain(int ival, int istart)
{
   int ix;

   if(iweather>0)
      KillBox();

   rgfcoord=new float*[ival];
   iweather=ival;
   idrop=istart;
   idrop2=0;
   for(ix=0;ix<ival;ix++)
   {
      rgfcoord[ix]=new float[2];
      rgfcoord[ix][0]=rand()%1024;
      rgfcoord[ix][1]=rand()%768;
   }

//   boombox->Loadsound("Data/Sounds/thunder_1.ogg",0);  //maybe get two different thunder noises eventually
//   boombox->Loadsound("Data/Sounds/thunder_1.ogg",2);
//   boombox->Loadsound("Data/Sounds/rain.ogg",1);
//   boombox->Setvolume(0,MIX_MAX_VOLUME/2);
//   boombox->Setvolume(1,MIX_MAX_VOLUME/2);
//   boombox->Setvolume(2,MIX_MAX_VOLUME/2);

   //boombox->Playsound(1,-1);
//   boombox->Fadeinsound(1,-1,2000);  //loop rain noise forever
}

//rgicoord[][0]==horizontal
//rgicoord[][1]==vertical
////////////////////////////////////////////////////////////////////Rain()/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////DRAWING FUNCTION//////////////////////////////////////////////////
void WeatherBox::Rain()
{
   int ix;

   //glDisable(GL_BLEND);
   glDisable(GL_TEXTURE_2D);
   glLineWidth(2.0f);
   //glColor4f(0.2,0.2,0.7,0.5);
   glColor4f(0.3,0.3,0.3,0.5);
   //figure this before the loop
      irainx=int(double(10*iwind)*cos(fwind));
      irainy=int(5.0+double(10*iwind)*sin(fwind)*-1.0);  //multiply by negative one (screen coordinates)
   for(ix=0;ix<idrop2;ix++)
   {
      glPushMatrix();
      glTranslatef(rgfcoord[ix][0],rgfcoord[ix][1],0.0);
      glBegin(GL_LINES);
         glVertex2d(0,0);
         //if(iwind>1)
            glVertex2d(irainx, irainy);
         //else
         //   glVertex2d(0, 10);
         //glVertex2d( 5,-5);
         //glVertex2d(-5, 5);
      glEnd();
      glPopMatrix();
   }
   //draw splashes
   for(ix=0;ix<10;ix++)
   {
      switch(rgisplash[ix][2])
      {
      case 0:
         //do nothing
         break;
      //case 1:
      //   break;
      default:
         //draw first animation frame
         glPushMatrix();
         glTranslatef(rgisplash[ix][0],rgisplash[ix][1],0.0);
         //I don't know how this works.  Apparently I can use the same *quadratic to draw all ten discs?
         //am I leaking memory?
         gluDisk(quadratic,rgisplash[ix][2]-1,rgisplash[ix][2],25,1);
         //glEnable(GL_TEXTURE_2D);
         //glDisable(GL_BLEND);
         //glColor3f(0.0,1.0,0.0);
         //glPrint(rgisplash[ix][0], rgisplash[ix][1],"splash%i",rgisplash[ix][2]);
         glPopMatrix();
         break;
      }
   }
}

////////////////////////////////////////////////////////////////////RainUpdate()///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void WeatherBox::RainUpdate(const BasicBox &primo)
{
   switch(isky)
   {
////////////////////day clear////////////////////
   case 0:
      if(Daycheck(true))
      {
         Night(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=2;
      }
      break;
/////////////////night clear///////////////
   case 1:
      if(Daycheck(false))
      {
         Day(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=3;
      }
      break;
///////////////day to night clear///////////////////
   case 2:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=1;  //night
         Night(rgfmap);  //kill round off error
      }
      /*if(iweather>0)
      {
         Drizzle();
         if(itrick%20==0)
         {
            delete []rgicoord[iweather-1];
            iweather-=1;
            //if(isky3!=2&&isky3!=3)
            //only shift from cloud to day, if it starts changing from day to night or night to day let the
            //other function take care of it
            if(isky3<2)  //this doesn't actually work, if it reaches day or night and still changing storm conditions this kicks back in
               Colorshift();
         }
      }
      else if(isky2==0)  //make sure the lightning turns off first
      {
         delete []rgicoord;
         isky=0;
         if(isky3==0)
            Day(rgfmap);
         else if(isky3==1)
            Night(rgfmap);
         boombox->Killsound(0);  //thunder
         boombox->Killsound(1);  //rain
      }
      else
      {
         //if last else if didn't catch we need to let lightning turn off
         Drizzle();
      }
      break;
///////////////////night to day clear//////////////////////
   case 3:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=0;  //day
         Day(rgfmap);  //kill round off error
      }
      break;
////////////////////day cloud////////////////
   case 4:
      if(Daycheck(true))
      {
         Night(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=6;  //day to night cloud
      }
      /*if(isky<2)  //this doesn't actually work, if it reaches day or night and still changing storm conditions this kicks back in
         Colorshift();
      Drizzle();
      if(icounter>=iweather)
      {
         isky=3;
         Storm(rgfmap);
      }
      break;
///////////////night cloud/////////////////////////
   case 5:
      if(Daycheck(false))
      {
         Storm(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=7;  //night to day cloud
      }
      break;
///////////////day to night cloud////////////////
   case 6:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=5;  //night cloud
         Night(rgfmap);  //kill round off error
      }
      break;
///////////////night to day cloud////////////////////
   case 7:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=4;  //day cloud
         Storm(rgfmap);  //kill round off error
      }
      break;
////////////////day clear to cloud/////////////////
   case 8:
      if(icounter<CLOUDSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=4;  //day cloud
         Storm(rgfmap);  //kill round off error
      }
      if(Daycheck(true))
      {
         Night(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=6;  //day to night cloud
      }
      break;
//////////////day cloud to clear///////////////
   case 9:
      if(icounter<CLOUDSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=0;  //day clear
         Day(rgfmap);  //kill round off error
      }
      if(Daycheck(true))
      {
         Night(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=2;  //day to night clear
      }
      break;
////////////////night clear to cloud///////////////////
   case 10:
      if(icounter<CLOUDSHIFT)
      {
         icounter+=1;
      }
      else
      {
         isky=5;  //night cloud
      }
      if(Daycheck(false))
      {
         Storm(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=7;  //night to day cloud
      }
      break;
////////////////night cloud to clear////////////////
   case 11:
      if(icounter<CLOUDSHIFT)
      {
         //Colorshift();
         icounter+=1;
      }
      else
      {
         isky=1;  //night clear
         //Night(rgfmap);  //kill round off error
      }
      if(Daycheck(false))
      {
         Day(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=3;  //night to day clear
      }
      break;
///////////////////day rain///////////////
   case 12:
      if(Daycheck(true))
      {
         Night(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=14;  //day to night rain
      }
      Drizzle(primo);
      break;
//////////////////night rain////////////////////
   case 13:
      if(Daycheck(false))
      {
         Storm(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=15;  //night to day rain
      }
      Drizzle(primo);
      break;
////////////////day to night rain///////////////////
   case 14:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=13;  //night rain
         Night(rgfmap);  //kill round off error
      }
      Drizzle(primo);
      break;
/////////////night to day rain/////////////
   case 15:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=12;  //day rain
         Storm(rgfmap);  //kill round off error
      }
      Drizzle(primo);
      break;
///////////////day clear to rain///////////////////
   case 16:
      Drizzle(primo);
      if(icounter<CLOUDSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=12;  //day rain
         Storm(rgfmap);  //kill round off error
      }
      if(Daycheck(true))
      {
         Night(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=14;  //day to night rain
      }
      break;
/////////////day rain to clear/////////////////
   case 17:
      Drizzle(primo);
      if(icounter<CLOUDSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         KillBox();
         isky=0;  //day clear
         Day(rgfmap);  //kill round off error
      }
      if(Daycheck(true))
      {
         KillBox();
         Night(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=2;  //day to night clear
      }
      break;
//////////////night clear to rain///////////////////
   case 18:
      Drizzle(primo);
      if(icounter<CLOUDSHIFT)
      {
         //Colorshift();
         icounter+=1;
      }
      else
      {
         isky=13;  //night rain
         //Night(rgfmap);  //kill round off error
      }
      if(Daycheck(false))
      {
         Storm(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=15;  //night to day rain
      }
      break;
////////////night rain to clear////////////
   case 19:
      Drizzle(primo);
      if(icounter<CLOUDSHIFT)
      {
         //Colorshift();
         icounter+=1;
      }
      else
      {
         KillBox();
         isky=1;  //night clear
         //Night(rgfmap);  //kill round off error
      }
      if(Daycheck(false))
      {
         KillBox();
         Day(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=3;  //night to day clear
      }
      break;
///////////////////day storm///////////////
   case 20:
      if(Daycheck(true))
      {
         Night(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=22;  //day to night storm
      }
      Drizzle(primo);
      break;
//////////////////night storm////////////////////
   case 21:
      if(Daycheck(false))
      {
         Storm(rgfmap3);
         icounter=0;
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         isky=23;  //night to day storm
      }
      Drizzle(primo);
      break;
////////////////day to night storm///////////////////
   case 22:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=21;  //night storm
         Night(rgfmap);  //kill round off error
      }
      Drizzle(primo);
      break;
/////////////night to day storm/////////////
   case 23:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
         icounter+=1;
      }
      else
      {
         isky=20;  //day storm
         Storm(rgfmap);  //kill round off error
      }
      Drizzle(primo);
      break;
   }

   imod+=1;
}*/

////////////////////////////////////////////////////////////////////Daycheck()////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bday==true = day
//bday==false = night
bool WeatherBox::Daycheck(bool bday)
{
   if((bday&&imod%DAYLEN>=DAYLEN/2)||(!bday&&imod%DAYLEN<DAYLEN/2))
      return true;
   else
      return false;
}

/*
   {
      if(imod%DAYLEN>=DAYLEN/2)
      {
         isky3=3;  //day to night
         Night(rgfmap3);  //check for weather later
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         icounter=0;
      }
      break;
//////////////////night//////////////////////////
   case 1:
      if(imod%DAYLEN<DAYLEN/2)
      {
         isky3=2;  //night to day
         if(isky==1||isky==3)
            Storm(rgfmap3);
         else
            Day(rgfmap3);  //check for weather later
         rgfmap3[0]=(rgfmap3[0]-rgfmap[0])/DAYSHIFT;
         rgfmap3[1]=(rgfmap3[1]-rgfmap[1])/DAYSHIFT;
         rgfmap3[2]=(rgfmap3[2]-rgfmap[2])/DAYSHIFT;
         icounter=0;
      }
      break;
///////////////////night to day///////////////////
   case 2:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
      }
      else
      {
         isky3=0;  //day
         if(isky==1||isky==3)
            Storm(rgfmap);
         else
            Day(rgfmap);
      }
      break;
///////////////////day to night//////////////////////
   case 3:
      if(icounter<DAYSHIFT)
      {
         Colorshift();
      }
      else
      {
         isky3=1;  //night
         Night(rgfmap);  //kill round off error
      }
      break;
   }
}*/

/////////////////////////////////////////////////////////Drizzle()//////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void WeatherBox::Drizzle(const BasicBox &primo)
{
   int ix, ij;

   for(ix=0;ix<idrop2;ix++)
   {
      //If map stationary or scrolling up normal rain, else speed it up. (otherwise background moves with rain)
      //vertical
      if(primo.fystore-primo.fy>0&&primo.istate==1)
         rgfcoord[ix][1]+=1-0.5*sin(fwind)*double(iwind)+(primo.fystore-primo.fy);
      else if(primo.istate==5)
         rgfcoord[ix][1]+=1-0.5*sin(fwind)*double(iwind)+primo.ilinkspeed;
      else
         rgfcoord[ix][1]+=1-0.5*sin(fwind)*double(iwind);

      //horizontal
      if(primo.istate==6)
         rgfcoord[ix][0]-=primo.ilinkspeed+0.5*cos(fwind)*double(iwind);
      else if(primo.istate==8)
         rgfcoord[ix][0]+=primo.ilinkspeed+0.5*cos(fwind)*double(iwind);
      else
         rgfcoord[ix][0]+=(primo.fxstore-primo.fx)+0.5*cos(fwind)*double(iwind);

      //horizontal wrap
      if(rgfcoord[ix][0]<-50)
         rgfcoord[ix][0]=1074;
      else if(rgfcoord[ix][0]>1074)
         rgfcoord[ix][0]=-50;

      //vertical wrap
      if(rgfcoord[ix][1]<-50)
         rgfcoord[ix][1]=818;
      else if(rgfcoord[ix][1]>818)
         rgfcoord[ix][1]=-50;

      //reset
      if(rand()%1000==0)
      {
    //////////////make some splashes///////////////
         ij=0;  //grab first available of ten splashes
         while(rgisplash[ij][2]!=0&&ij<10)
            ij+=1;
         if(ij<10)  //else forget it, don't need to animate every one
         {
            rgisplash[ij][0]=int(rgfcoord[ix][0]);
            rgisplash[ij][1]=int(rgfcoord[ix][1]);
            rgisplash[ij][2]=1;  //turn on the drop animation
         }

         rgfcoord[ix][0]=rand()%1024;
         rgfcoord[ix][1]=rand()%768;
      }
   }

   for(ij=0;primo.itrick%30==0&&ij<10;ij++)
   {
      switch(rgisplash[ij][2])
      {
      case 0:
         //leave it alone
         break;
      case 3:
         rgisplash[ij][2]=0;
         break;
      default:
         rgisplash[ij][2]+=1;
         break;
      }
   }

   if(idrop!=idrop2&&imod%20==0)
   {
      if(idrop2>idrop)
         idrop2-=2;
      else
         idrop2+=1;
   }
}*/

////////////////////////////////////////////////////////////////Modwind()///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeatherBox::Modwind(float fnum)
{
   if(fnum>0&&fnum<2*M_PI)
      fwind+=fnum;
   if(fwind>2*M_PI)
      fwind-=2*M_PI;
}

////////////////////////////////////////////////////////////////////////////////Augwind()///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeatherBox::Augwind(int inum)
{
   iwind+=inum;
   if(iwind<0)
      iwind=0;
   else if(iwind>10)
      iwind=10;
   if(iwind>0)
   {
//      boombox->Loadsound("Data/windy.wav",3);
//      boombox->Setvolume(3,(MIX_MAX_VOLUME/10)*iwind);
//      boombox->Fadeinsound(3,-1,1000);

      /*if(iwind==10)
      {
         boombox->Playsong("Data/fourfiends.ogg");
         boombox->Musicvolume(MIX_MAX_VOLUME);
      }*/

   }
   else
   {
//      boombox->Fadesound(3,1000);
   }
}
 /*  if(itrick%250==0)
   {
      if(isky==1&&rand()%20==0)
      {
         //boombox->Loadsound("Data/thunder_1.ogg");
         if(boombox->Channelstatus(0)==0)
            boombox->Playsound(0,0);
         else
            boombox->Playsound(2,0);
         if(isky2==0)
         {
            rgfmap2[0]=rgfmap[0];
            rgfmap2[1]=rgfmap[1];
            rgfmap2[2]=rgfmap[2];
            Lightning(rgfmap);
            //Day(rgfmap);
         }
         isky2=1;
      }
      else if(isky2==1)
      {
         rgfmap[0]=rgfmap2[0];
         rgfmap[1]=rgfmap2[1];
         rgfmap[2]=rgfmap2[2];
         isky2=0;
      }
   }
}*/

/*void WeatherBox::Zeus()
{
   if(istrike==0)
      istrike=1;
   else if(istrike==1)
      istrike=0;
}*/

///////////////////////////////////////////////////////////////COLOR FUNCTIONS////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeatherBox::Day(float rgfval[])
{
   rgfval[0]=1.0;
   rgfval[1]=1.0;
   rgfval[2]=1.0;
}

void WeatherBox::Night(float rgfval[])
{
   rgfval[0]=0.0;
   rgfval[1]=0.0;
   rgfval[2]=0.2;
}

void WeatherBox::Bluecave(float rgfval[])
{
   rgfval[0]=0.0;
   rgfval[1]=0.0;
   rgfval[2]=0.1;
}

void WeatherBox::Storm(float rgfval[])
{
   rgfval[0]=0.2;
   rgfval[1]=0.2;
   rgfval[2]=0.2;
}

void WeatherBox::Lightning(float rgfval[])
{
   rgfval[0]=1.0;
   rgfval[1]=1.0;
   rgfval[2]=0.3;
}

//////////////////////////////////////////////////////////////////////Colorshift()//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WeatherBox::Colorshift()
{
   switch(istrike)
   {
   case 0:  //nothin'
      rgfmap[0]+=rgfmap3[0];
      rgfmap[1]+=rgfmap3[1];
      rgfmap[2]+=rgfmap3[2];
      break;
   case 1:  //lightning strike
      rgfmap2[0]+=rgfmap3[0];
      rgfmap2[1]+=rgfmap3[1];
      rgfmap2[2]+=rgfmap3[2];
   case 2:
      break;
   }
}
