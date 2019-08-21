/***************************************************************************
 *   Copyright (C) 2007 by icecubeflower                                   *
 *   icecube@icebox                                                        *
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

#ifndef PICLOADER
#define PICLOADER

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "switchmaster.h"

//ImageVault is a linked list of VaultNodes
//OpenGL stores all the images for you, all this does is record a linked list of
//integers and imagenames which correspond to images loaded in memory

struct VaultNode
{
   VaultNode();
   ~VaultNode();

   VaultNode *imagenext;
   std::string imagename;
   GLuint imagenum;
};

struct ImageVault
{
   ImageVault();
   ~ImageVault();
   bool ImageLoader(std::string filename, GLuint &funnum);
   void Apocalypse();
   bool ImageZap(GLuint funnum);
   std::string GetName(GLuint funnum);  //returns full name of image
   std::string GetName();               //returns name of current image or empty string if imagereturn==NULL
   GLuint GetNum();                //returns number of current image or zero if NULL
   void Reset();                   //puts imagereturn at start of list
   bool End();                     //returns true if imagereturn==NULL (that is PAST imagetail)
   bool Next();                    //imagereturn=imagereturn->imagenext

private:
   VaultNode *imagehead;
   VaultNode *imagereturn;
};

#endif
