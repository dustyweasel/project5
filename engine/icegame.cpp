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

#include "icegame.h"

GameBox::GameBox()
{
  std::string temp;

  mResolutionChange=false;

  SDL_Init(SDL_INIT_VIDEO);

  const SDL_VideoInfo* myPointer = SDL_GetVideoInfo(); //I don't think this needs to be freed
  mWidth=myPointer->current_w;
  mHeight=myPointer->current_h;

  //SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);      //for windows
  SDL_putenv("__GL_SYNC_TO_VBLANK=1");                //for linux and an NVidia card
  //????????????????????                              //for linux and another video card?  beats me.

  mHaveFullscreen = true;
  screen = SDL_SetVideoMode(mWidth, mHeight, BPP, SDL_OPENGL|SDL_FULLSCREEN);
  //screen = SDL_SetVideoMode(mWidth, mHeight, BPP, SDL_OPENGL);

  if(!screen)
  {
    fprintf(stderr, "Couldn't initialize screen for some reason!: %s\n", SDL_GetError());
    SDL_Quit();
    exit(2);
  }
  //SDL_ShowCursor  (SDL_DISABLE);  //let overworld decide this
  SDL_WM_SetCaption("Project5", "project5");

   srand(time(NULL));

   icemap=&map1;
   lastmap=&map2;

   done = 0;
   istate=0;
   istate2=0;
   elticko=SDL_GetTicks();
   flinkspeed=1.2f;

   quadratic=gluNewQuadric();
   fx=0;
   fy=0;
   fxstore=0;
   fystore=0;
   istate3=0;
   elticko=0;
   rgcloader[0]="";
   rgcloader[1]="";
   rgcloader[2]="";

   basicloader="Font.png";
   picbox.ImageLoader(basicloader,statbox[2]);
   typewriter.BuildFont(statbox[2]);

   basicloader="heart.png";
   picbox.ImageLoader(basicloader,statbox[0]);
   basicloader="deadheart.png";
   picbox.ImageLoader(basicloader,statbox[1]);
   basicloader="pencil.png";
   picbox.ImageLoader(basicloader,statbox[3]);

   //3 GUI textures
   basicloader="base.jpg";
   picbox.ImageLoader(basicloader,statbox[4]);
   basicloader="mars0_src.jpg";
   picbox.ImageLoader(basicloader,statbox[5]);
   basicloader="MoonMap.jpg";
   picbox.ImageLoader(basicloader,statbox[6]);

   basicloader="whiskey.ani";
   cutscene[0].Spawnbox(basicloader,picbox);
   basicloader="adventure.ani";
   cutscene[1].Spawnbox(basicloader,picbox);

   //nature.Raininit(100,100);
   infile.open("Data/Save1/save1.sav");
   if(infile.fail()==false)
      infile>>rgcloader[0];
   infile.close();
   infile.open("Data/Save2/save2.sav");
   if(infile.fail()==false)
      infile>>rgcloader[1];
   infile.close();
   infile.open("Data/Save3/save3.sav");
   if(infile.fail()==false)
      infile>>rgcloader[2];
   infile.close();

  boombox.Playsong("raw.ogg");

  gluQuadricNormals(quadratic, GLU_SMOOTH);
  gluQuadricTexture(quadratic,GL_TRUE);

   //SDL_ShowCursor(false);
   reshape();
   initGui();
}

GameBox::~GameBox()
{
  gluDeleteQuadric(quadratic);
  cleanGui();
}

void GameBox::Go(SDL_Event &event)
{
  switch(event.type)
  {
  case SDL_KEYUP:
    keyunbreak(event);
    break;
  case SDL_KEYDOWN:
    keybreak(event);
    break;
  case SDL_QUIT:
    done = 1;
    break;
  case SDL_MOUSEMOTION:
  case SDL_MOUSEBUTTONDOWN:
  case SDL_MOUSEBUTTONUP:
    mSDLInput->pushInput(event);
    break;
  }
  mGui->logic();
}

void GameBox::Update(Uint8 *keys)
{
  tickmaster(keys);
  if (mResolutionChange)
  {
    // Clear the screen before remaking the Gui
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapBuffers();

    cleanGui();
    initGui();
    mResolutionChange = false;
  }
  draw();
}

bool GameBox::GameOver()
{
   if(done==0)
      return false;
   else
      return true;
}

void GameBox::reshape()
{
  glViewport(0, 0, mWidth, mHeight);		
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glShadeModel(GL_SMOOTH);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();	
  gluPerspective(45.0, float(mWidth)/float(mHeight), 1.0, 10.0);

  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();
}
