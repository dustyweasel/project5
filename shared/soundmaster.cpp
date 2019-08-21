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

#include "soundmaster.h"

ChunkSpec::ChunkSpec()
{
   chunk=NULL;
   name="";
}

ChunkSpec::~ChunkSpec()
{
   if(chunk!=NULL)
      Mix_FreeChunk(chunk);
}

AudioBox::AudioBox()
{
  int ix;

  SDL_Init(SDL_INIT_AUDIO);
  music=NULL;

  // Initialize Audio sub system
  if(SDL_InitSubSystem(SDL_INIT_AUDIO)==-1)
  {
    fprintf( stderr, "Could not initialize audio subsystem: %s\n", SDL_GetError( ) );
  }
  // Open the sound device
  if(Mix_OpenAudio(44100,AUDIO_S16SYS,2,512)<0)
  {
    fprintf( stderr, "Unable to open audio: %s\n", SDL_GetError( ) );
  }

  Mix_AllocateChannels(8);  //I don't think this needs to be in a try block
  for(ix=0;ix<8;ix++)
     Mix_Volume(ix,MIX_MAX_VOLUME);
  Musicvolume(MIX_MAX_VOLUME/5.0);
}

AudioBox::~AudioBox()
{
  int ix;

  KillALL();
  Mix_CloseAudio( );
  SDL_QuitSubSystem( SDL_INIT_AUDIO );
}

bool AudioBox::Playsong(std::string rgcsong)
{
  Killsong();
  //rgcsong=Pathfinder::Song_Path+rgcsong;
  //music set to NULL if this fails.  That okay, I guess.
  music=Mix_LoadMUS((Pathfinder::Song_Path+rgcsong).c_str());
  if(music!=NULL)
  { 
    Mix_PlayMusic(music,-1);
    songname=rgcsong;
    return true;
  }
  else
  {
    return false;
  }
}

void AudioBox::Killsong()
{
   if(music!=NULL)
   {
      Mix_HaltMusic();
      Mix_FreeMusic(music);
      music=NULL;
   }
}

void AudioBox::Musicvolume(int ivolume)
{
   Mix_VolumeMusic(ivolume);
}

std::string AudioBox::GetSongName()
{
  return songname;
}

bool AudioBox::Playsound(std::string rgcsound)
{
  return Playsound(rgcsound,MIX_MAX_VOLUME);
}

bool AudioBox::Playsound(std::string rgcsound, int ivolume)
{
   int rgiavail[5];
   int ix=0;
   bool breturn=false;
   int ifree=0;

   rgcsound=Pathfinder::Sound_Path+rgcsound;

   //ensure that ifree==number of available chunks
   //and rgiavail records which chunks are available
   for(ix=0;ix<5;ix++)
   {
      if(Mix_Playing(ix)==0)
      {
         rgiavail[ifree]=ix;
         ifree+=1;
      }
   }

   //if a chunk is available then play the sound else force it
   if(ifree>0)
   {
      //make ix==element of rgiavail with chunk # with sound already loaded or just last available chunk
      ix=0;
      while(ix<ifree&&chunkbox[rgiavail[ix]].name!=rgcsound)
      {
         ix+=1;
      }
      //there weren't any matches, subtract 1 from ix to make it last element of rgiavail specifying an available chunk
      if(ix==ifree)
      {
         ix-=1;
         Killsound(rgiavail[ix]);  //chunkbox[rgiavail[ix]].chunk=NULL on errors
         chunkbox[rgiavail[ix]].chunk=Mix_LoadWAV(rgcsound.c_str());
         chunkbox[rgiavail[ix]].name=rgcsound;
         //loaded it, now we'll play it below
      }

      //play the damn sound finally
      Mix_Volume(rgiavail[ix],ivolume);
      Mix_PlayChannel(rgiavail[ix], chunkbox[rgiavail[ix]].chunk,0);
      if(chunkbox[rgiavail[ix]].chunk!=NULL)
        breturn=true;
   }
   //force it
   else
   {
     Killsound(0);
     chunkbox[0].chunk=Mix_LoadWAV(rgcsound.c_str());
     chunkbox[0].name=rgcsound;
     //play the damn sound finally
     Mix_Volume(0,ivolume);
     Mix_PlayChannel(0, chunkbox[0].chunk,0);
     if(chunkbox[0].chunk!=NULL)
       breturn=true;
   }

   return breturn;
}

bool AudioBox::Isplaying(std::string rgcsound)
{
   int ix;
   bool breturn=false;

   for(ix=0;ix<5;ix++)
   {
      if(Mix_Playing(ix)!=0&&chunkbox[ix].name==rgcsound)
         breturn=true;
   }
   return breturn;
}

bool AudioBox::Loopsound(std::string rgcsound, int ims)
{
   int rgiavail[3];
   int ix;
   bool breturn=false;
   int ifree=0;

   //ensure that ifree==number of available chunks
   //and rgiavail records which chunks are available
   for(ix=5;ix<8;ix++)
   {
      if(Mix_Playing(ix)==0)
      {
         rgiavail[ifree]=ix;
         ifree+=1;
      }
   }

   //if a chunk is available then loop the sound else return false
   if(ifree>0&&Islooping(rgcsound)==false)
   {
      //make ix==element of rgiavail with chunk # with sound already loaded or just last available chunk
      ix=0;
      while(ix<ifree&&chunkbox[rgiavail[ix]].name!=rgcsound)
         ix+=1;
      //there weren't any matches, subtract 1 from ix to make it last element of rgiavail specifying an available chunk
      if(ix==ifree)
      {
         ix-=1;
         Killsound(rgiavail[ix]);
         chunkbox[rgiavail[ix]].chunk=Mix_LoadWAV((Pathfinder::Sound_Path+rgcsound).c_str());
         chunkbox[rgiavail[ix]].name=rgcsound;
         //loaded it, now we'll play it below
      }

      //loop the damn sound finally
      if(ims<=0)  //only positive values make sense for fadeins
         Mix_PlayChannel(rgiavail[ix], chunkbox[rgiavail[ix]].chunk,-1);
      else
         Mix_FadeInChannel(rgiavail[ix], chunkbox[rgiavail[ix]].chunk, -1, ims);

      if(chunkbox[rgiavail[ix]].chunk!=NULL)
        breturn=true;
   }

   return breturn;
}

bool AudioBox::Kill_loop(std::string rgcsound, int ims)
{
   bool breturn=false;
   int ix;

   for(ix=5;ix<8;ix++)
   {
      if(Mix_Playing(ix)!=0&&chunkbox[ix].name==rgcsound)
      {
         breturn=true;
         if(ims<=0)
            Mix_HaltChannel(ix);
         else
            Mix_FadeOutChannel(ix,ims);
      }
   }

   return breturn;
}

bool AudioBox::Loopvolume(std::string rgcsound, int ivolume)
{
   bool breturn=false;
   int ix;

   for(ix=5;ix<8;ix++)
   {
      if(chunkbox[ix].name==rgcsound)
      {
         breturn=true;
         Mix_Volume(ix,ivolume);
      }
   }
   return breturn;
}

void AudioBox::KillALL()
{
   int ix;

   Killsong();
   for(ix=0;ix<8;ix++)
   {
      Killsound(ix);
   }
}

//returns true if rgcsound is currently looping in 5,6,or 7
bool AudioBox::Islooping(std::string rgcsound)
{
   int ix;
   bool breturn=false;

   //ensure that ifree==number of available chunks
   //and rgiavail records which chunks are available
   for(ix=5;ix<8;ix++)
   {
      if(Mix_Playing(ix)!=0&&chunkbox[ix].name==rgcsound)
         breturn=true;
   }
   return breturn;
}

void AudioBox::Killsound(int ival)
{
   if(chunkbox[ival].chunk!=NULL)
   {
      Mix_HaltChannel(ival);
      Mix_FreeChunk(chunkbox[ival].chunk);
      chunkbox[ival].chunk=NULL;
      chunkbox[ival].name="";
   }
}
