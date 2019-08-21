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

#include <stdlib.h>
#include <GL/gl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include "Gizbox.h"
#include "MapBox.h"
#include "ice_edit.h"

int main(int argc, char *argv[])
{
  SDL_Event event;
  SDL_Surface *screen;
  Uint8 *keys;
  EditBox manipulator;

  manipulator.Initialize();

  while (!manipulator.GameOver())
  {
    keys = SDL_GetKeyState(NULL);
    while ( SDL_PollEvent(&event) )
    {
      manipulator.Go(event);
    }

    manipulator.Update(event);
  }

  SDL_Quit();
  return 0;
}

