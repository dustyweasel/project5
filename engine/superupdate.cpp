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

#include "icegame.h"

void GameBox::tickmaster(Uint8 *keys)
{
  //Uint32 history;  //how much time has passed since last update

  history=SDL_GetTicks()-elticko;
  elticko=SDL_GetTicks();

  switch(istate)  //another switch(istate) to execute every cycle
  {
///////////////////////////////////  istate==0  main menu     /////////////////////////////////////////////////////////
  case 0:
    //nature.RainUpdate(primo);
    cutscene[1].Update(elticko);
    break;
//////////////////////////////////////istate==1  main game   /////////////////////////////////////////////////////////
      case 1:
      case 4:
      case 11:  //dead
      case 12:  //victory
         if(istate!=12)
           mapblock=input(keys, history);
         //iceblock=refactorizer.terrain;

         //this does stuff like calm the hero down if he's invincble after being hit or being slammed across the screen
         //why is this in InsertHead?  this is just updating hero being slammed across screen and stuff
         //only two places for inserting blood splatters, when hero attacks and the call to Update on the
         //next line
         //icemap->monsterbox.InsertHead(hero.gizupdate(NULL,icemap->mapgrid,picbox,boombox,history));

         //same as above line, no InsertHead
         //hero.gizupdate(NULL,icemap->mapgrid,picbox,boombox,history));
         //okay this is returning Gizmo* but I know it is NULL in this case for now,
         //someday maybe have to handle it to keep from leaking memory
         icemap->gizupdate(&hero,NULL,picbox,boombox,history);


         //updates everything in monsterbox
         //icemap->monsterbox.Update(&hero,icemap->mapgrid,history,picbox,boombox);
         icemap->UpdateMonsters(&hero,history,picbox,boombox);
         icemap->UpdateSplatter(&hero,history,picbox,boombox);
         //animate layer stuff like lakes or whatever
         icemap->UpdateAniLayers(elticko);

         setfx();
         setfy();

         if(mapblock>1&&mapblock<52)
         {
            //iceval-=2;  //cave links are 2-51 (50 total) subtract 2 to make it 0-49
            dval=DVAL;
            istate=9;
         }
         else if(mapblock>65531&&mapblock<65536)
         {
            loadlink(mapblock-65527); //65532==scroll up
            //next two lines stop skip-scrolling but are repeat of lines at the top, maybe smarter way to do this
            history=SDL_GetTicks()-elticko;
            elticko=SDL_GetTicks();
         }
         if((istate==1||istate==4)&&hero.GetHealth()<=0.0f)
           istate=11;
         else if((istate==1||istate==4)&&icemap->GetName()=="cave2.map"&&icemap->Clear())
         {
           boombox.Playsong("army_of_poes-light_3.mid");
              elsavo=elticko;
           istate=12;
           istate2=0;
         }
/////////////////////
if(elticko-elsavo>2000)
{
  istate2+=1;
  elsavo=elticko;
}
///////////////////////

         break;
//////////////////////////////////////istate==2  cutscene   /////////////////////////////////////////////////////////
//this is terrible coding, i'll fix it later
      case 2:
         //create another file type that holds sequences of animations and get rid of all this hard coded bs
    /*     switch(istate2)
         {
         case 0:
            cutscene[0].Update(elticko);
            if(elticko>5000)
            {
               istate2=1;
            }
            break;
         case 1:
            cutscene[0].Update(elticko);
            fx-=flinkspeed*float(history);
            if(fx<=-1024.0f)
            {
               fx=-1024.0f;
               cutscene[0].Death();
               istate2=2;
               elsavo=elticko;
               //fx=0;  do this before istate=0
            }
            break;
         case 2:  //our 2nd demo
            cutscene[1].Update(elticko);
            if(elticko-elsavo>6000)
            {
               elsavo=elticko;
               istate2=3;
            }
            break;
         case 3:  //icecubeflower / programming
            cutscene[1].Update(elticko);
            if(elticko-elsavo>1000)
            {
               elsavo=elticko;
               istate2=4;
            }
            break;
         case 4:  //JazzMint
            cutscene[1].Update(elticko);
            if(elticko-elsavo>3000)
            {
               elsavo=elticko;
               istate2=5;
            }
            break;
         case 5:  //icecubeflower / art
            cutscene[1].Update(elticko);
            if(elticko-elsavo>1000)
            {
               elsavo=elticko;
               istate2=6;
            }
            break;
         case 6:  //icecubeflower / SFX
            cutscene[1].Update(elticko);
            if(elticko-elsavo>5000)
            {
               elsavo=elticko;
               istate2=7;
            }
            break;
         case 7:  // help wanted
            cutscene[1].Update(elticko);
            if(elticko-elsavo>6000)
            {
               elsavo=elticko;
               istate=0;
               fx=0;
               istate2=0;
            }
            break;
         }*/
         break;
//////////////////////////////////////    istate==4   moved to case 1 /////////////////////////////////////////////////////////
//////////////////////////////////////   istate==5   scroll up ///////////////////////////////////////////////////
  case 5:
  case 7:
    masterscroll+=flinkspeed*float(history);
   // masterscroll+=1;
    if(masterscroll>=subHeight)
      istate=1;
    break;
//////////////////////////////////////    istate==8  scroll left   /////////////////////////////////////////////////////////
  case 6:
  case 8:
    masterscroll+=flinkspeed*float(history);
    if(masterscroll>=subWidth)
      istate=1;
    break;
//////////////////////////////////////              istate==9     /////////////////////////////////////////////////////////
  case 9:
    //commence cartoon cave link
    if(dval>5)
    {
      dval-=double((flinkspeed*float(history)));
      if(dval<1.0)
        dval=1.0;
    }
    else
    {
      boombox.Playsound("Data/Sounds/start.wav");
      istate=10;
      loadlink2();
      icemap->Music(boombox);
       elticko=SDL_GetTicks();
      setfx();
      setfy();
    }
    break;
//////////////////////////////////////              istate==10     /////////////////////////////////////////////////////////
  case 10:
    //finish cartoon cave link
    if(dval<800)
      dval+=double(flinkspeed*float(history));
    else
      istate=1;
    break;
  }
}
