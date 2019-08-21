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

//HEY! rand() % X = 0 thru X-1
//maybe that makes more sense than using RAND_MAX.

#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <fstream>
#include <iostream>
#include "icegame.h"

int main(int argc, char *argv[])
{
   SDL_Event event;
   Uint8 *keys;

   GameBox overworld;

   while(overworld.GameOver()==false)
   {
      keys = SDL_GetKeyState(NULL);
      while ( SDL_PollEvent(&event) )
      {
         overworld.Go(event);
      }
      overworld.Update(keys);
   }

   SDL_Quit();
   return 0;
}
