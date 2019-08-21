/***************************************************************************
 *   Copyright (C) 2009 by icecubeflower                                   *
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

#include "ice_edit.h"

EditBox::EditBox()
{
  SDL_Init(SDL_INIT_VIDEO);

  mWidth=1024;
  mHeight=768;
  subWidth=1024;
  subHeight=768;

  screen = SDL_SetVideoMode(1024, 768, 16, SDL_OPENGL);
  if(!screen)
  {
    fprintf(stderr, "Couldn't set 1024x768 GL video mode: %s\n", SDL_GetError());
    SDL_Quit();
    exit(2);
  }
  SDL_WM_SetCaption("pr5edit", "pr5edit");

  done = 0;
  istate=2;
  fx=0;
  fy=0;
  fmap[0]=0.9f;
  fmap[1]=0.9f;
  fmap[2]=0.9f;

//  irow=1;
//  icol=1;
  fx=0;
  fy=0;
  istate=0;
  istate2=0;
  istate3=0;

  done=0;
  elticko=0;
  rgcloader="";
  iceout=0;
  ifade=0;
  rgfheader[0]=0.0f;
  rgfheader[1]=0.0f;
  rgfheader[2]=1.0f;
  rgfadvice[0]=0.2f;
  rgfadvice[1]=0.7f;
  rgfadvice[2]=0.3f;

  //icemap=new MapBox;
  //hackmap=new MapBox;
  //picbox=new ImageVault;
   reshape();
   initGui();
}

EditBox::~EditBox()
{
  //delete icemap;
  //delete hackmap;
  //delete picbox;
}

void EditBox::Initialize()
{
  basicloader="Font.png";
  picbox.ImageLoader(basicloader,statbox[0]);
  typewriter.BuildFont(statbox[0]);

  elticko = SDL_GetTicks();
  savecolor(true);
  //SDL_ShowCursor(false);
}

void EditBox::Go(SDL_Event &event)
{
  switch(event.type)
  {
  case SDL_MOUSEMOTION:
    mousejog();
    break;
  case SDL_MOUSEBUTTONDOWN:
    mousepush(event);
    break;
  case SDL_KEYUP:
    break;
  case SDL_KEYDOWN:
    keybreak(event);
    break;
  case SDL_QUIT:
    done=1;
    break;
  }
}

void EditBox::Update(SDL_Event &event)
{
  tickmaster(event);
  draw();
}

void EditBox::savecolor(bool bval)
{
  if(bval)
  {
    rgfedit[0]=0.0;
    rgfedit[1]=0.5;
    rgfedit[2]=1.0;
  }
  else
  {
    rgfedit[0]=1.0;
    rgfedit[1]=0.4;
    rgfedit[2]=0.4;
  }
}

void EditBox::Fade()
{
  ifade=3000;
}

void EditBox::Save()
{
  if(icemap.Writemap(picbox))
    savecolor(true);  //if Writemap ever returns false then something is wrong
  Fade();
}

void EditBox::Quit()
{
  done=1;
}

void EditBox::StateSwitch(int ival)
{
  int ix;

  rgcloader="";
  istate2=0;
  istate3=0;
  istate4=0;
  switch(ival)
  {
  case 0:  //menu
    istate=0;
    istate2=1; //menu off by default
    break;
  case 1:  //rename map
    istate=1;
    break;
  case 2:  //loadmap
    icemap.Apocalypse();
    hackmap.Apocalypse();
    istate=2;
    break;
  case 3:  //new map wizard
    istate=3;
    break;
  case 4:  //add layers
    rgcloader.insert(0,icemap.GetLayerName(0,picbox),0,icemap.GetLayerName(0,picbox).length()-strlen(".jpg"));
    istate=4;
    break;
  case 5:     //resize  (leaves cave link list intact)
    icemap.KillMatrix();
    for(ix=0;ix<4;ix++)
      icemap.SetSideLink(ix,"");
    icemap.NukeMonsters();
    istate=5;
    break;
  case 8:     //block edit
    savecolor(false);
    Fade();
    istate=8;
    break;
  case 11:  //sidelinks
    if(hackmap.Loadmap(icemap.GetSideLink(0),true,picbox))
      rgcloader.insert(0,icemap.GetSideLink(0),0,icemap.GetSideLink(0).length()-strlen(".map"));
    istate=11;
    break;
  case 12:  //cave links
    icemap.ResetCave();
    if(hackmap.Loadmap(icemap.GetCaveNode().name,true,picbox))
      rgcloader.insert(0,icemap.GetCaveNode().name,0,icemap.GetCaveNode().name.length()-strlen(".map"));
    else
      istate2=-1;
    istate=12;
    break;
  case 14:  //edit Gizmos
    istate=14;
    break;
  case 15:  //add Gizmos
    istate=15;
    break;
  case 17:  //add layers
    rgcloader.insert(0,icemap.GetAniLayerName(0),0,icemap.GetAniLayerName(0).length()-strlen(".ani"));
    istate=17;
    break;
  case 18:  //edit Anibox's
    istate=18;
    break;
  case 19:  //edit music
    rgcloader.insert(0,icemap.GetSong(),0,icemap.GetSong().length()-strlen(".mid"));
    istate=19;
    break;
  }
}

bool EditBox::GameOver()
{
  if(done==0)
    return false;
  else
    return true;
}

void EditBox::StandardWarp()
{
  icemap.WarpGiz(hero,512.0f,376.0f,2,true);
  setfx();
  setfy();
}

void EditBox::Brighten()
{
  if(fmap[0]<1.0f)
  {
    fmap[0]+=0.1f;
    fmap[1]+=0.1f;
    fmap[2]+=0.1f;
  }
}

void EditBox::Darken()
{
  if(fmap[0]>0.0f)
  {
    fmap[0]-=0.1f;
    fmap[1]-=0.1f;
    fmap[2]-=0.1f;
  }
}

void EditBox::initGui()
{
  mOpenGLGraphics = new gcn::OpenGLGraphics();
  mOpenGLGraphics->setTargetPlane(mWidth, mHeight);
  mOpenGLImageLoader = new gcn::OpenGLSDLImageLoader();
  gcn::Image::setImageLoader(mOpenGLImageLoader);

  mSDLInput = new gcn::SDLInput();
//try/catch?  YES
  mFont = new gcn::ImageFont("Data/Images/techyfontbig2.png"," abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
  mHighLightFont = new gcn::ImageFont("Data/Images/techyfontbighighlight.png"," abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");

  mTop = new gcn::Container();
  mTop->setOpaque(false);
  mMain = new gcn::Container();
  mMain->setOpaque(false);
  mTop->add(mMain);

  /*mSingleplayButton = new FPSButton("PLAY DEMO #3",boombox);
//////////////////////////////////////////////
	mSingleplayButton->setHighLightFont(mHighLightFont);
	mSingleplayButton->adjustSize();
	mSingleplayButton->setActionEventId("play");
	mSingleplayButton->addActionListener(this);
	mSingleplayButton->setFont(mFont);
	mSingleplayButton->adjustSize();
	mMain->add(mSingleplayButton);*/
////////////////////////////////////////////////

  gcn::OpenGLImage* image;

  mGui = new gcn::Gui();
  mGui->setGraphics(mOpenGLGraphics);
  mGui->setInput(mSDLInput);

  mGui->setTop(mTop);

  mTop->setDimension(gcn::Rectangle(0, 0, mWidth, mHeight));
  mMain->setDimension(gcn::Rectangle(0, 0, mWidth, mHeight));
  //mSingleplayButton->setPosition(mWidth/16, mHeight/16);
}

void EditBox::cleanGui()
{
  delete mSDLInput;

  delete mFont;
  delete mHighLightFont;

  delete mGui;
  delete mOpenGLGraphics;
  delete mOpenGLImageLoader;

  delete mTop;
  delete mMain;
  //delete mSingleplayButton;
}

void EditBox::action(const gcn::ActionEvent& actionEvent)
{
  std::ifstream infile;
  std::string rgcfilename;

  if(actionEvent.getId()=="quit")
  {
    //mRunning = false;
  }
}

void EditBox::reshape()
{
  glViewport(0, 0, mWidth, (GLint) mHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, mWidth, mHeight, 0.0f, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
