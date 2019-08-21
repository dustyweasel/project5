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

void GameBox::keybreak(SDL_Event &event)
{
   int ix, ij;
   char ctrash;
   int itrash;  //don't confuse with itrash1
   std::ofstream outfile;
   std::ifstream infile;
   std::ifstream savefile;
   std::string rgcfilename;
   std::string rgcplayername;  //i think i'll be able to get rid of these two strings when the time comes
   std::string rgclayer1;
 //  Gizmo *hitchecker;
 //  Gizmo *spawn;

   switch(istate)
   {
//////////////////////////////////////              istate==0     main menu  /////////////////////////////////////////////////////////
   case 0:
      //istate2 == which saved game
      //istate3 == picking a game or entering a new name
      switch(istate3)
      {
      case 0:
         switch(event.key.keysym.sym)
         {
         case SDLK_q:
            if(event.key.keysym.mod & KMOD_ALT)
               done=1;
            break;
         case SDLK_ESCAPE:
    boombox.Playsound("button.wav");
    mMain->setVisible(true);
    mAbout->setVisible(false);
    //mMultiplay->setVisible(false);
    mOptions->setVisible(false);
            //istate=2;
            break;
         case SDLK_DELETE:
            istate3=2;
            boombox.Playsound("switch_game.wav");
            break;
         case SDLK_RETURN:
            /*if(rgcloader[istate2]=="")
            {
               istate3=1;
               boombox.Playsound("switch_game.wav");
            }
            else
            {
               //seriously, this is terrible, make a savefile structure or something
               switch(istate2)
               {
               case 0:
                  infile.open("Data/Save1/save1.sav");
                  break;
               case 1:
                  infile.open("Data/Save2/save2.sav");
                  break;
               case 2:
                  infile.open("Data/Save3/save3.sav");
                  break;
               }

               infile>>rgcfilename;
               infile>>rgcfilename;

               icemap->Loadmap(rgcfilename, false,picbox);
               icemap->Music(boombox);
               infile>>rgcfilename;

               infile.close();   //the mapname is stored in rgcfilename so reopen it later

               //open the gizmo file
               hero.Gizgen(rgcfilename,1024.0f,1024.0f,picbox);
               setfx();
               setfy();

               dval=5;
               istate=10;
               elticko=SDL_GetTicks();

               boombox.Playsound("start.wav");
               //boombox.Playsong("Data/Songs/Atmsphere1.ogg");
            }*/
            break;
         case SDLK_DOWN:
       /*     istate2+=1;
            if(istate2>2)
               istate2=0;
            boombox.Playsound("switch_game.wav");*/
            break;
         case SDLK_UP:
         /*   istate2-=1;
            if(istate2<0)
               istate2=2;
            boombox.Playsound("switch_game.wav");*/
            break;
         }
         break;
      case 1:
         if(getkey(event, rgcloader[istate2])==false)
         {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
               rgcloader[istate2]="";
              // boombox.Playsound("Data/Sounds/delete.wav");
              // nature.boombox.Playsound("Data/Sounds/TextDone.wav");  //get this from giz file eventually
    mMain->setVisible(true);
    mAbout->setVisible(false);
    //mMultiplay->setVisible(false);
    mOptions->setVisible(false);
               istate3=0;
               break;
            case SDLK_q:
               if(event.key.keysym.mod & KMOD_ALT)
                  done=1;
               break;
            case SDLK_DOWN:
               //nature.boombox.Loadsound("Data/Sounds/Error.wav",4);  //get this from giz file eventually
               //nature.boombox.Setvolume(4,MIX_MAX_VOLUME);
              // nature.boombox.Playsound(4,0);
               break;
            case SDLK_UP:
             //  nature.boombox.Loadsound("Data/Sounds/Error.wav",4);  //get this from giz file eventually
             //  nature.boombox.Setvolume(4,MIX_MAX_VOLUME);
             //  nature.boombox.Playsound(4,0);
               break;
            case SDLK_RETURN:
               if(rgcloader[istate2]!="")
               {
                  //totally rework this someday, make a savefile structure or something
                  //while(rgcloader[istate2].length()<14)
                  //   rgcloader[istate2]+=' ';
                  switch(istate2)
                  {
                  case 0:
                     outfile.open("Data/Save1/save1.sav");
                     break;
                  case 1:
                     outfile.open("Data/Save2/save2.sav");
                     break;
                  case 2:
                     outfile.open("Data/Save3/save3.sav");
                     break;
                  }
                  outfile<<rgcloader[istate2]<<"\n";
                  outfile<<"start.map"<<"\n";
                  //ix=strlen("lake.map");
                  //while(ix<14)
                 // {
                   //  outfile<<' ';
                    // ix+=1;
                 // }
                  outfile<<"start.giz"<<"\n";
                 // ix=strlen("start.giz");
                 // while(ix<14)
                 // {
                 //    outfile<<' ';
                 //    ix+=1;
                 // }
                  outfile.close();
                  for(ix=0;ix<3;ix++)
                     rgcloader[ix]="";
                  infile.open("Data/Save1/save1.sav");
                  if(infile.fail()==false)
                     infile>>rgcloader[0];
                     //namegrabber(rgcloader[0],infile);
                  infile.close();
                  infile.open("Data/Save2/save2.sav");
                  if(infile.fail()==false)
                     infile>>rgcloader[1];
                     //namegrabber(rgcloader[1],infile);
                  infile.close();
                  infile.open("Data/Save3/save3.sav");
                  if(infile.fail()==false)
                     infile>>rgcloader[2];
                     //namegrabber(rgcloader[2],infile);
                  infile.close();
                  istate3=0;
                  boombox.Playsound("pencap.wav");  //get this from giz file eventually
               }
               break;
            }
         }
         else
         {
           // if(!nature.boombox.Isplaying("Data/Sounds/write.wav"))
               boombox.Playsound("write.wav");  //get this from giz file eventually
         }
         break;
      case 2:
         switch(event.key.keysym.sym)
         {
         case SDLK_ESCAPE:
            boombox.Playsound("switch_game.wav");
            //nature.boombox.Playsound("Data/Sounds/TextDone.wav");  //get this from giz file eventually
            istate3=0;
            break;
         case SDLK_q:
            if(event.key.keysym.mod & KMOD_ALT)
               done=1;
            break;
         case SDLK_DELETE:
            istate3=0;
            boombox.Playsound("erase.wav");  //get this from giz file eventually
            rgcloader[istate2]="";
            switch(istate2)
            {
            case 0:
               outfile.open("Data/Save1/save1.sav");
               break;
            case 1:
               outfile.open("Data/Save2/save2.sav");
               break;
            case 2:
               outfile.open("Data/Save3/save3.sav");
               break;
            }
            outfile.close();
            break;
         }
         break;
      }  //switch(istate3)
      break;
//////////////////////////////////////              istate==1   main game    /////////////////////////////////////////////////////////
   case 1:
   case 4:
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
         //if(event.key.keysym.mod & KMOD_ALT)
         //{
            reshape();
            istate=0;
            istate2=0;
    mMain->setVisible(true);
    mAbout->setVisible(false);
    //mMultiplay->setVisible(false);
    mOptions->setVisible(false);
         //}
         break;
      case SDLK_LALT:
         //genertate Bomb with timer to last as long as attack animation, start attack animation,
         //stick bomb in bomb-list, check for collisions between bombs and enemies
         //icemap->monsterbox.Victimize(&hero, boombox, picbox);
         //hero.Attack(boombox,icemap->attacknodes);
         icemap->BombDrop(hero,boombox);
         break;
      #ifdef PROGRAMMER
      case SDLK_F2:
         if(istate==1)
            istate=4;
         else if(istate==4)
            istate=1;
         break;
      case SDLK_c:
         nature.Cloudinit();
         break;
      case SDLK_e:
         nature.Clearinit();
         break;
      case SDLK_r:
         nature.Raininit(200,200);
         break;
      case SDLK_d:
            nature.Augwind(-1);
         break;
      case SDLK_f:
            nature.Augwind(1);
         break;
      case SDLK_h:
         nature.Modwind(0.1f);
         break;
      case SDLK_u:
         nature.rgfmap[0]+=0.1;
         break;
      case SDLK_j:
         nature.rgfmap[0]-=0.1;
         break;
      case SDLK_i:
         nature.rgfmap[1]+=0.1;
         break;
      case SDLK_k:
         nature.rgfmap[1]-=0.1;
         break;
      case SDLK_o:
         nature.rgfmap[2]+=0.1;
         break;
      case SDLK_l:
         nature.rgfmap[2]-=0.1;
         break;
      case SDLK_KP_PLUS:
         hero.Grow();
         break;
      case SDLK_KP_MINUS:
         hero.Shrink();
         break;
      #endif
      }
      break;
///////////////////////////////////////  istate==2 cut scene ///////////////////////////
   case 2:
      istate=0;
      fx=0;
      istate2=0;
      boombox.Playsound("switch_game.wav");
      break;
   case 5:  //scroll up
   case 6:
   case 7:
   case 8:
   case 9: //start cartoon cave link
   case 10: //finish cartoon cave link
   default:
      switch(event.key.keysym.sym)
      {
      case SDLK_q:
         if(event.key.keysym.mod & KMOD_ALT)
         {
            istate=0;
            istate2=0;
            boombox.Playsong("army_of_poes-close_your_eyes.mid");
         }
         break;
      case SDLK_ESCAPE:
         //if(event.key.keysym.mod & KMOD_ALT)
         //{
            reshape();
            istate=0;
            istate2=0;
    mMain->setVisible(true);
    mAbout->setVisible(false);
    //mMultiplay->setVisible(false);
    mOptions->setVisible(false);
         //}
         break;
      }
      break;
   }//switch (istate)
}
