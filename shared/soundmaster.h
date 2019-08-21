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

#ifndef SOUNDMASTER
#define SOUNDMASTER

//#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "switchmaster.h"

struct ChunkSpec
{
  ChunkSpec();
  ~ChunkSpec();

  Mix_Chunk *chunk;
  std::string name;
};

struct AudioBox
{
  AudioBox();
  ~AudioBox();

  bool Playsong(std::string rgcsong);
  void Killsong();
  void Musicvolume(int ivolume);  //try MIX_MAX_VOLUME
  std::string GetSongName();

//this is for 0-4 (along with Killsound)
  bool Playsound(std::string rgcsound);
  bool Playsound(std::string rgcsound, int ivolume);
  bool Isplaying(std::string rgcsound);

//for 5-7  ims for fade in/out in millisecons, use 0 or negative for no fade
  bool Loopsound(std::string rgcsound, int ims);
  bool Kill_loop(std::string rgcsound, int ims);
  bool Loopvolume(std::string rgcsound, int ivolume);

//stop all sounds and music now and free them now
  void KillALL();

private:
  bool Islooping(std::string rgcsound);
  void Killsound(int ival);
  ChunkSpec chunkbox[8];
  Mix_Music *music;
  std::string songname;
};

#endif
