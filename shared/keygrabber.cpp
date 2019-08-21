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

#include "keygrabber.h"
#include <fstream>

bool getkey(SDL_Event &jollyroger, std::string &strval)
{
   if(((jollyroger.key.keysym.sym>='a'&&jollyroger.key.keysym.sym<='z')||
       (jollyroger.key.keysym.sym>='0'&&jollyroger.key.keysym.sym<='9')||
       (jollyroger.key.keysym.sym>=256&&jollyroger.key.keysym.sym<=265)||  //keypad 0-9
       jollyroger.key.keysym.sym=='-'||
       (jollyroger.key.keysym.sym==SDLK_BACKSPACE))&&
       !(jollyroger.key.keysym.mod & KMOD_ALT))
   {
      if(jollyroger.key.keysym.sym!=SDLK_BACKSPACE||(jollyroger.key.keysym.sym==SDLK_BACKSPACE&&strval.length()>0))
      {
         if(jollyroger.key.keysym.sym=='-'&&jollyroger.key.keysym.mod & KMOD_SHIFT)
            strval+="_";
         else if(jollyroger.key.keysym.sym=='-')
            strval+="-";
         else if(jollyroger.key.keysym.sym==SDLK_BACKSPACE)
            strval.resize(strval.length()-1);
         else if((jollyroger.key.keysym.mod & KMOD_SHIFT)&&(jollyroger.key.keysym.sym>='a'&&jollyroger.key.keysym.sym<='z'))
            strval+=jollyroger.key.keysym.sym-('a'-'A');
         else if(jollyroger.key.keysym.sym>=256&&jollyroger.key.keysym.sym<=265)
            strval+=jollyroger.key.keysym.sym-(256-'0');
         else
            strval+=jollyroger.key.keysym.sym;  //add a character
       }
       return true;
    }
    else
    {
       return false;
    }
}

bool getnum(SDL_Event &jollyroger, int &ival)
{
  int icheat;

  if(((jollyroger.key.keysym.sym>='0'&&jollyroger.key.keysym.sym<='9')||
      (jollyroger.key.keysym.sym>=256&&jollyroger.key.keysym.sym<=265)||  //keypad 0-9
      (jollyroger.key.keysym.sym==SDLK_BACKSPACE))&&
      !(jollyroger.key.keysym.mod & KMOD_ALT))
  {
    if(jollyroger.key.keysym.sym!=SDLK_BACKSPACE)
    {
      if(jollyroger.key.keysym.sym>='0'&&jollyroger.key.keysym.sym<='9')
        icheat=jollyroger.key.keysym.sym-'0';
      else
        icheat=jollyroger.key.keysym.sym-256;
      ival*=10;
      ival+=icheat;
    }
    else
    {
      ival/=10;
    }

    return true;
  }
  else
  {
    return false;
  }
}
