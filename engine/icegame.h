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

#ifndef ICEGAME
#define ICEGAME

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>
#include <sstream>
#include "MapBox.h"
#include "paintmap.h"
#include "weather.h"
#include "Picloader.h"
#include "drawbomb.h"
#include "paintblocks.h"
#include "keygrabber.h"
#include "fpsbutton.hpp"
#include "fpscheckbox.hpp"

//////////////////////////OUTDATED: ///////////////////////////////
//covers icegame.cpp
//       keydown.cpp      keybreak()   -> getkey()
//       superupdate.cpp  tickmaster() -> input()   -> loadlink() -> setfx()
//       playerpush.cpp   input()
//       orient.cpp       setfx()
//       linkloder.cpp    loadlink()
//       keygrabber.cpp   getkey()
//       paintify.cpp     draw()       -> drawmap() -> drawhero() -> drawblocks() -> drawgiz() -> drawstore() -> painthearts()
//       keyup.cpp        keyunbreak()
//       paintmap.cpp     drawmap()
//       painthero.cpp    drawhero()
//       drawblocks.cpp   drawblocks()
//       paintgiz.cpp     drawgiz()
//       picpez.cpp       drawstore()
//       paintstats.cpp   drawhearts()

class ResolutionListModel : public gcn::ListModel
{
public:
  ResolutionListModel();
  int getNumberOfElements();
  std::string getElementAt(int i);

//modes should probably be private
  SDL_Rect** modes;  //don't need to free it
  std::stringstream converter;
  std::string translation;

private:
  int isize;
};

struct GameBox : public gcn::ActionListener
{
  GameBox();
  ~GameBox();
  void Go(SDL_Event &event);
  void Update(Uint8 *keys);
  bool GameOver();
///////////public gui functions///////////////////////////
  void initGui();
  void cleanGui();
  void AlterVideo();
  void reshape();
  void action(const gcn::ActionEvent& actionEvent);
////////////////////////////////////////////////////////////

private:
  void keybreak(SDL_Event &event);
  void keyunbreak(SDL_Event &event);
  void tickmaster(Uint8 *keys);
  Iceblock input(Uint8 *stroky, Uint32 history);
  void setfy();
  void setfx();
  void loadlink(int inewstate);
  void loadlink2();
  void draw();
  void drawhero();
  void herotranslate();
  void drawhearts();
///////////////private gui functions///////////////////////////
  void initOptions();  //GUI stuff
  void cleanOptions();
  void initAbout();
  void cleanAbout();
//////////////////////////////////////////////////////////

  int mWidth;
  int mHeight;
  int subWidth;
  int subHeight;
  SDL_Surface *screen;

  MapBox *icemap;
  MapBox *lastmap;
  MapBox map1;
  MapBox map2;
  ImageVault picbox;  //totally unrelated to data type PicBox, sorry about that
  WeatherBox nature;
  AudioBox boombox;

  //0 = heart
  //1 = deadheart
  //2 = font
  //3 = pencil
  //4 = stars
  //5 = planet
  //6 = sun
  GLuint statbox[10];
  PrintBox typewriter;  //get rid of this?
  std::string basicloader;
  std::ifstream infile;

  Gizmo hero;
  float fx,fy;
  int fxstore, fystore;
  int istate;
  int istate2;
  int istate3;
  Uint32 elticko;
  Uint32 elsavo;  //what is this one for?
  Uint32 history;
  GLUquadricObj* quadratic;
  GLdouble dval;
  float flinkspeed;
  float masterscroll;
  int done;
  Anibox cutscene[2];
  std::string rgcloader[3];

  Iceblock mapblock;  //for loadlink2
//////////////////////////////////////GUI variables/////////////////////////////////////
  gcn::Gui* mGui;
  gcn::OpenGLGraphics* mOpenGLGraphics;
  gcn::ImageFont* mFont;
  gcn::ImageFont* mWhiteFont;
  gcn::ImageFont* mHighLightFont;
  gcn::OpenGLSDLImageLoader* mOpenGLImageLoader;  //I only use this for loading fonts, I think

  gcn::Container* mTop;
  gcn::Container* mMain;
  gcn::Container* mOptions;
  gcn::Container* mAbout;
  FPSButton* mSingleplayButton;
  FPSButton* mOptionsButton;
  FPSButton* mAboutButton;
  FPSButton* mQuitButton;
  FPSButton* mOptionsBackButton;
  FPSButton* mAboutBackButton;

  gcn::Icon* mOptionsBoxIcon;
  gcn::Icon* mAboutBoxIcon;
  gcn::DropDown* mResolution;
  ResolutionListModel* mResolutionListModel;
  gcn::ScrollArea* mResolutionScrollArea;
  gcn::ListBox* mResolutionListBox;

  gcn::Image* mBoxImage;  //move this to picbox?
  gcn::Label* mOptionsLabel;
  gcn::Label* mAboutLabel;
  FPSCheckBox* mFullScreen;
  bool mHaveFullscreen;
  bool mResolutionChange;
  gcn::Label* mResolutionLabel;

  gcn::TextBox* mAboutText;

  gcn::Label* mWebLabel;

  gcn::SDLInput* mSDLInput;  //need this?
///////////////////////////////////////////////////////////////////////////////////////////////
};

#endif
