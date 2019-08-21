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

#ifndef ICEEDIT
#define ICEEDIT

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>
#include "MapBox.h"
#include "paintmap.h"
#include "printify.h"
#include "paintblocks.h"
#include "keygrabber.h"

//////////OUTDATED: /////////////////////////////
//covers ice_edit.cpp
//superupdate.cpp       tickmaster()
//paintmaster.cpp       draw()         -> paintmap() -> drawgiz() ->drawhero() -> drawblocks() -> drawmenu -> drawmenu -> drawfade()
//paintmap.cpp          drawmap()
//paintgiz.cpp          drawgiz()
//painthero.cpp         drawhero()
//paintblocks.cpp       drawblocks()
//paintmenu.cpp         drawmenu()
//paintfade.cpp         drawfade()
//navigate.cpp          up() setfx()
//keygrabber.cpp        getkey()
//keydown.cpp           keybreak()     ->up()
//mouseclick.cpp        mousepush()    ->setfx()
//mousemove.cpp         mousejog()

struct EditBox : public gcn::ActionListener
{
  EditBox();
  ~EditBox();
  void Initialize();
  void Go(SDL_Event &event);
  void Update(SDL_Event &event);
  bool GameOver();
  void initGui();
  void cleanGui();
  void reshape();
  void action(const gcn::ActionEvent& actionEvent);

private:
  void tickmaster(SDL_Event &event);
  void MouseScroll(SDL_Event &event, Uint32 history, MapBox &scrollmap);
  void draw();
  void DrawBackDrop(float &ftrash);
  void PaintSpecimen(int ipic);
  void PaintGizInfo(int iswitch);
  void drawhero();
  void mdrawhero();
  void drawmenu(int ispot2);
  void drawfade(int icorner);
  void up();
  void down();
  void left();
  void right();
  void setfx();
  void setfy();
//  bool getkey(SDL_Event &event, int ival);  //ival=0,alpha ival=1,number
//  bool getalpha(SDL_Event &event);
//  bool getnum(SDL_Event &event);
  void keybreak(SDL_Event &event);
  void arrow(SDL_Event &event);
  void mousepush(SDL_Event &event);
  void mousejog();
  void savecolor(bool bval);
  void Fade();
  void Save();
  void Quit();
  void StateSwitch(int ival);
  void Brighten();
  void Darken();
  void StandardWarp();

  int mWidth;
  int mHeight;
  int subWidth;
  int subHeight;
  SDL_Surface *screen;
////GUI stuff/////////////////////////////////////
  gcn::Gui* mGui;
  gcn::OpenGLGraphics* mOpenGLGraphics;
  gcn::ImageFont* mFont;
  gcn::ImageFont* mHighLightFont;
  gcn::OpenGLSDLImageLoader* mOpenGLImageLoader;  //I only use this for loading fonts, I think

  gcn::Container* mTop;
  gcn::Container* mMain;
  //FPSButton* mSingleplayButton;

  gcn::SDLInput* mSDLInput;  //need this?
//////////////////////////////////////////////////

  Gizmo hero;               //this is the cursor, doesn't really need to be a Gizmo, I guess
  Gizmo specimen;           //forgot
  Anibox anitest;           //forgot
  //int irow, icol;           //forgot
  float fx,fy;              //where to scroll screen
  int istate;               //what state we're in
  int istate2;              //these mean many different things depending other istate values
  int istate3;
  int istate4;
  int done;                 //when we're done
  float fmap[3];            //tint of screen (probably should make this a vector)
  Uint32 elticko;           //time since beginning in milliseconds (1/1000) second
  std::string rgcloader;    //holds user input
  Iceblock iceout;          //forgot
  int ifade;                //if this is > 0 then show some extra info
  float rgfedit[3];         //one color if data saved, another if not
  float rgfheader[3];       //these two store colors for text
  float rgfadvice[3];
  //PicBox monsterstore;

  MapBox icemap;           //the main map
  MapBox hackmap;          //another map
  GLuint statbox[10];       //forgot
  ImageVault picbox;       //holds ALL imagenames, both string and OpenGL name (GLuint)
  AudioBox boombox;
  PrintBox typewriter;      //use this things functions to print to the screen
  std::string basicloader;  //forgot
};

#endif
