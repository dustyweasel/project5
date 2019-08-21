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

#include "ice_edit.h"

void EditBox::keybreak(SDL_Event &event)
{
  std::string rgcfilename;
  Speckeeper specval;

  switch(istate)
  {
/////////////////////////////////////////////////istate==0////////////////////////////////////////////////////////
/////////////////////////////////////////////////menu///////////////////////////////////////////////////////////
  //istate2==show menu or not
  case 0:
    switch(event.key.keysym.sym)
    {
    case SDLK_ESCAPE:
      if(istate2==1)
        istate2=0;
      else
        istate2=1;
      break;
    case SDLK_q:
      if(event.key.keysym.mod & KMOD_ALT)
        Quit();
      break;
    case SDLK_s:
      if(event.key.keysym.mod & KMOD_ALT)
        Save();
      break;
    case SDLK_F2:  //open a map
      StateSwitch(2);
      break;
    case SDLK_F3:  //side links
      StateSwitch(11);
      break;
    case SDLK_F4:   //cave links
      StateSwitch(12);
      break;
    case SDLK_F5:   //edit gizmos
      StateSwitch(14);
      break;
    case SDLK_F6:  //add gizmos to map
      StateSwitch(15);
      break;
    case SDLK_F7:  //add layers
      StateSwitch(17);
      break;
    case SDLK_F8:  //edit anibox's
      StateSwitch(18);
      break;
    case SDLK_F12:  //edit anibox's
      StateSwitch(19);
      break;
    case SDLK_F9:   //rename map
      StateSwitch(1);
      break;
    case SDLK_F10:    //get layers
      StateSwitch(4);
      break;
    case SDLK_F11:        //resize
      StateSwitch(5);
      break;
    case SDLK_SPACE:  //block edit
      StateSwitch(8);
      break;
    case SDLK_KP_PLUS:
      Brighten();
      break;
    case SDLK_KP_MINUS:
      Darken();
      break;
    }
    arrow(event);
    break;
////////////////////////////////////////istate==1/////////////////////////////////////////////////////////////
///////////////////////////////////////rename map////////////////////////////////////////////////////////////
  case 1:
    if(getkey(event,rgcloader)==false)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_F2:    //open a map
        StateSwitch(2);
        break;
      case SDLK_F5:   //edit gizmos
        StateSwitch(14);
        break;
      case SDLK_F8:  //edit aniboxes
        StateSwitch(18);
        break;
      case SDLK_RETURN:
        rgcfilename=rgcloader+".map";
        if(icemap.Rename(rgcfilename,picbox))
          StateSwitch(0);
        break;
      }
    }
    break;
////////////////////////////////////////istate==2/////////////////////////////////////////////////////////////
///////////////////////////////////////open a new map////////////////////////////////////////////////////////////
  case 2:
    if(getkey(event,rgcloader)==false)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_F5:  //edit gizmos
        StateSwitch(14);
        break;
      case SDLK_F8:  //edit anibox's
        StateSwitch(18);
        break;
      case SDLK_RETURN:
        rgcfilename=rgcloader+".map";
        rgcloader.resize(0);
        ////////for a fun time spawn 1000 gizmos and pass false here and interact with them//////////////
        if(icemap.Loadmap(rgcfilename,true,picbox))
        {
          StandardWarp();
          savecolor(true);
          StateSwitch(0);
          icemap.Music(boombox);
        }
        else if(icemap.Rename(rgcfilename,picbox))
        {
          StateSwitch(3);
        }
        break;
      }
    }
    break;
///////////////////////////////////////////////////////////istate==3////////////////////////////////////////////
/////////////////////////////////////////////////create a new map/////////////////////////////////////////////////
  case 3:
    switch(istate2)
    {
    case 0:  //get layer1
      if(getkey(event,rgcloader)==false)
      {
        switch(event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          icemap.Apocalypse();
          StateSwitch(2);
          break;
        case SDLK_q:
          if(event.key.keysym.mod & KMOD_ALT)
            done=1;
          break;
        case SDLK_RETURN:
          rgcfilename=rgcloader+".png";
          icemap.LoadLayer(rgcfilename,picbox,0);
          if(icemap.GetLayerName(0,picbox)==rgcfilename)
            istate2=1;
          rgcloader="";
          break;
        }
      }
      break;
    case 1: //get rows (istate3)
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        StateSwitch(3);
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
        Quit();
        break;
      case SDLK_RETURN:
        istate2=2;
        break;
      } 
      break;
    case 2:  //get columns (istate4)
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        istate2=1;
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
        Quit();
        break;
      case SDLK_RETURN:
        istate2=3;
        break;
      }
      break;
    case 3:  //all good?
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        istate2=2;
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_RETURN:
        icemap.Morph(istate3,istate4);
        icemap.Writemap(picbox);
        icemap.WarpGiz(hero,512.0f,384.0f,2,true);
        setfx();
        setfy();
        istate=0;
        istate2=0;  //show menu
        savecolor(true);
        break;
      }
      break;
    }  //switch(istate2)
    break;
///////////////////////////////////istate==4    ///////////////////////////////////////////
/////////////////////////////////////get layers                         //////////////////////////
  case 4:
    //istate2==which layer
    if(getkey(event,rgcloader)==false)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        StateSwitch(0);
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_s:
        if(event.key.keysym.mod & KMOD_ALT)
        {
          Save();
          rgcloader="";
          rgcloader.insert(0,icemap.GetLayerName(istate2,picbox),0,icemap.GetLayerName(istate2,picbox).length()-strlen(".png"));
        }
        break;
      case SDLK_DELETE:
        icemap.KillLayer(istate2);
        rgcloader="";
        rgcloader.insert(0,icemap.GetLayerName(istate2,picbox),0,icemap.GetLayerName(istate2,picbox).length()-strlen(".png"));
        savecolor(false);
        break;
      case SDLK_RETURN:
        rgcfilename=rgcloader+".png";
        icemap.LoadLayer(rgcfilename,picbox,istate2);
        rgcloader="";
        rgcloader.insert(0,icemap.GetLayerName(istate2,picbox),0,icemap.GetLayerName(istate2,picbox).length()-strlen(".png"));
        break;
      case SDLK_PAGEUP:
        istate2=1;
        rgcloader="";
          rgcloader.insert(0,icemap.GetLayerName(istate2,picbox),0,icemap.GetLayerName(istate2,picbox).length()-strlen(".png"));
        break;
      case SDLK_PAGEDOWN:
        istate2=0;
        rgcloader="";
        rgcloader.insert(0,icemap.GetLayerName(istate2,picbox),0,icemap.GetLayerName(istate2,picbox).length()-strlen(".png"));
        break;
      } //switch (keysym)
    }
    else
    {
      savecolor(false);
    }
    arrow(event);
    break;
///////////////////////////////////////////////////////////istate==5////////////////////////////////////////////
///////////////////////////////////////////////// resize /////////////////////////////////////////////////
  case 5:
    switch(istate2)
    {
    case 0:    //get rows  (istate3)
      if(getnum(event,istate3)==false)
      {
        switch(event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          icemap.Apocalypse();
          StateSwitch(0);
          break;
        case SDLK_q:
          if(event.key.keysym.mod & KMOD_ALT)
            Quit();
          break;
        case SDLK_RETURN:
          istate2=1;
          break;
        }
      }
      break;
    case 1:    //get columns  (istate4)
      if(getnum(event,istate4)==false)
      {
        switch(event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          icemap.Apocalypse();
          StateSwitch(5);  //go back to get rows
          break;
        case SDLK_q:
          if(event.key.keysym.mod & KMOD_ALT)
            Quit();
          break;
        case SDLK_RETURN:
          icemap.Morph(istate3,istate4);
          setfx();
          setfy();
          StateSwitch(0);
          break;
        }
      }
      break;
    }
///////////////////////////////////////////////////////////////istate==8////////////////////////////////////////////
///////////////////////////////////////////////////////////block edit//////////////////////////////////////
  case 8:
    switch(event.key.keysym.sym)
    {
    case SDLK_q:
      if(event.key.keysym.mod & KMOD_ALT)
        Quit();
      break;
    case SDLK_SPACE:
      StateSwitch(0);
      break;
    }
    arrow(event);
    break;
////////////////////////////////////////////////////////////istate==9///////////////////////////////////////////////
//////////////////////////////////////////////////////////////mouse edit////////////////////////////////////////////
  case 9:
    break;
////////////////////////////////////////////////////////////istate==10/////////////////////////////////////////////
////////////////////////////////////////////////////////mouse/////////////////////////////////////////////////
  case 10:
    break;
//////////////////////////////////////////////////////////istate==11////////////////////////////////////////////
////////////////////////////////////////////////////////side links////////////////////////////////////////////////
  case 11:
    if(getkey(event,rgcloader)==false)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        StateSwitch(0);
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_s:
        if(event.key.keysym.mod & KMOD_ALT)
        {
          Save();
          rgcloader="";
          rgcloader.insert(0,icemap.GetSideLink(istate2),0,icemap.GetSideLink(istate2).length()-strlen(".map"));
        }
        break;
      case SDLK_DELETE:
        icemap.SetSideLink(istate2,"");
        rgcloader="";
        hackmap.Apocalypse();
        savecolor(false);
        break;
      case SDLK_RETURN:
        rgcfilename=rgcloader+".map";
        if(hackmap.Loadmap(rgcfilename,true,picbox)==false)
        {
          rgcfilename="";
          rgcloader="";
        }
        icemap.SetSideLink(istate2,rgcfilename);
        break;
      case SDLK_PAGEUP:
        if(istate2<3)
          istate2+=1;
        else
          istate2=0;

        rgcloader="";
        if(hackmap.Loadmap(icemap.GetSideLink(istate2),true,picbox))
          rgcloader.insert(0,icemap.GetSideLink(istate2),0,icemap.GetSideLink(istate2).length()-strlen(".map"));
        break;
      case SDLK_PAGEDOWN:
        if(istate2>0)
          istate2-=1;
        else
          istate2=3;

        rgcloader="";
        if(hackmap.Loadmap(icemap.GetSideLink(istate2),true,picbox))
          rgcloader.insert(0,icemap.GetSideLink(istate2),0,icemap.GetSideLink(istate2).length()-strlen(".map"));
        break;
      } //switch (keysym)
    }
    else
    {
      savecolor(false);
    }
    arrow(event);
    break;
/////////////////////////////////////////////////////////////////istate==12/////////////////////////////////////////////
////////////////////////////////////////////////////////////cave  links/////////////////////////////////////////////////////
  case 12:
    //istate2==which cave link you're editing
    //istate3==0=alter pre-existing link 1=add a new link
    if(getkey(event,rgcloader)==false)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        switch(istate3)
        {
        case 0:
          hackmap.Apocalypse();
          StateSwitch(0);
          break;
        case 1:
          istate3=0;
          rgcloader="";
          rgcloader.insert(0,icemap.GetCaveNode().name,0,icemap.GetCaveNode().name.length()-strlen(".map"));
          break;
        }
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_s:
        if(event.key.keysym.mod & KMOD_ALT)
        {
          Save();
          rgcloader="";
          rgcloader.insert(0,icemap.GetCaveNode().name,0,icemap.GetCaveNode().name.length()-strlen(".map"));
        }
        break;
      case SDLK_KP_PLUS:
        if(icemap.GetCaveSize()<50)
        {
          istate3=1;
          rgcloader="";
        }
        break;
      case SDLK_DELETE:
        icemap.ZapCaveNode(istate2);//cave.ZapSpecNode(istate2);
        if(istate2>0)
          istate2-=1;
        hackmap.ChooseCaveNode(istate2);
        hackmap.Loadmap(icemap.GetCaveNode().name,true,picbox);
        rgcloader="";
        rgcloader.insert(0,icemap.GetCaveNode().name,0,icemap.GetCaveNode().name.length()-strlen(".map"));
        savecolor(false);
        break;
      case SDLK_RETURN:
        switch(istate3)
        {
        case 0:  //if altering a pre-existing link
          rgcfilename=rgcloader+".map";
          if(!hackmap.Loadmap(rgcfilename,true,picbox))
          {
            hackmap.Loadmap(icemap.GetCaveNode().name,true,picbox);
          }
          else
          {
            specval.Death();
            specval.name=rgcfilename;
            icemap.SetCaveNode(specval);
          }
          rgcloader="";
          rgcloader.insert(0,icemap.GetCaveNode().name,0,icemap.GetCaveNode().name.length()-strlen(".map"));
          break;
        case 1:  //if adding a new link
          rgcfilename=rgcloader+".map";
          if(!hackmap.Loadmap(rgcfilename,true,picbox))
          {
            rgcloader="";
          }
          else
          {
            specval.Death();
            specval.name=rgcfilename;
            icemap.LoadCaveNode(specval);
            istate2=icemap.GetCaveSize()-1;
            istate3=0;
          }
          break;
        }
        break;
      case SDLK_PAGEUP:
        switch(istate3)
        {
        case 0:
          istate2+=1;
          if(istate2>=icemap.GetCaveSize())
            istate2=0;

          rgcloader="";
          if(icemap.ChooseCaveNode(istate2)&&hackmap.Loadmap(icemap.GetCaveNode().name,true,picbox))
            rgcloader.insert(0,icemap.GetCaveNode().name,0,icemap.GetCaveNode().name.length()-strlen(".map"));
          break;
        case 1:
          break;
        }
        break;
      case SDLK_PAGEDOWN:
        switch(istate3)
        {
        case 0:
          istate2-=1;
          if(istate2<0)
            istate2=icemap.GetCaveSize()-1;

          rgcloader="";
          if(icemap.ChooseCaveNode(istate2)&&hackmap.Loadmap(icemap.GetCaveNode().name,true,picbox))
            rgcloader.insert(0,icemap.GetCaveNode().name,0,icemap.GetCaveNode().name.length()-strlen(".map"));
          break;
        case 1:
          break;
        }
        break;
      case SDLK_F2:
        if(icemap.GetCaveSize()>0)
        {
          icemap.WarpGiz(hero,512.0f,384.0f,2,true);
          setfx();
          setfy();
          istate=13;
        }
        break;
      } //switch (keysym)
    }
    else
    {
      savecolor(false);
    }
    arrow(event);
    break;
//////////////////////////////////////////////////////////istate==13////////////////////////////////////////////////////
/////////////////////////////////////////////////////pick warp point///////////////////////////////////////////////////////
  case 13:
    break;
////////////////////////////////////////////////////////////istate==14///////////////////////////////////////////////////////
///////////////////////////////////////////////////////edit gizmos////////////////////////////////////////////////////////////
  case 14:
  //istate2: 0==choose a gizmo 1==edit png filenames 2==spawn a new gizmo 3==edit sound filenames
  //istate3: depends on istate2
  if(getkey(event,rgcloader)==false)  //(if they hit a key that we don't want to put into a string)
  {
    switch(event.key.keysym.sym)
    {
    case SDLK_ESCAPE:
      switch(istate2)
      {
      case 1:  //editing png file names
        rgcloader="";
        istate2=0;
        break;
      case 2:  //spawning a new gizmo
        rgcloader="";
        istate2=0;
        break;
      case 3: //editing sound file names
        istate2=1;
        istate3=0;
        rgcloader="";
        rgcloader.insert(0,specimen.GetPicName(istate3,picbox),0,specimen.GetPicName(istate3,picbox).length()-strlen(".png"));
        break;
      }
      break;
    case SDLK_F2:  //load a new map
      if(istate2==0)
      {
        icemap.Apocalypse();
        hackmap.Apocalypse();
        StateSwitch(2);
      }
      break;
    case SDLK_q:
      if(event.key.keysym.mod & KMOD_ALT)
        Quit();
      break;
    case SDLK_F3:
      switch(istate2)
      {
      case 1:
        istate2=2;
        rgcloader=specimen.GetName();
        break;
      }
      break;
    case SDLK_F5:
      switch(istate2)
      {
      case 1:
        istate2=3;
        istate3=0;
        rgcloader="";
        rgcloader.insert(0,specimen.GetSoundName(0),0,specimen.GetSoundName(0).length()-strlen(".wav"));
        break;
      }
      break;
    case SDLK_s:
      if(event.key.keysym.mod & KMOD_ALT)
      {
        switch(istate2)
        {
        case 0:
          break;
        case 1:
        case 3:
          specimen.Gizwrite(picbox);
          savecolor(true);
          break;
        case 2:
          break;
        }
      }
      break;
    case SDLK_RETURN:
      switch(istate2)
      {
      case 0:         //choosing a gizmo to edit
        istate3=0;    //display the first png right away
        rgcloader+=".giz";

        //if(specified gizmo does not exist)
        if(!specimen.Gizgen(rgcloader,0,0,picbox))
        {
          istate2=2;
        }
        //they picked a pre-existing gizmo file
        else
        {
          savecolor(true);
          rgcloader="";
          rgcloader.insert(0,picbox.GetName(specimen.GetPic(0)),0,picbox.GetName(specimen.GetPic(0)).length()-strlen(".png"));
          istate2=1;
        }
        break;
      case 1:  //editing filenames in giz file
        rgcloader=rgcloader+".png";
        specimen.PicSwap(rgcloader,picbox,istate3);  //this returns GLuint of dead image if you want to free it
        if(specimen.GetPicName(istate3,picbox)!=rgcloader)
          rgcloader="";
        else
          rgcloader.resize(rgcloader.length()-strlen(".png"));
        break;
      case 2:  //istate2==2 / creating a new Gizmo
        specimen.Gizspawn(istate3,rgcloader);  //rgcloader was set back in istate2==0 / istate3  is set here
        istate3=0;                             //start at 1st filename in istate2==1
        istate2=1;                             //istate2==2 is between 0 and 1
        rgcloader="";
        break;
      case 3:
        rgcloader=rgcloader+".wav";
        if(boombox.Playsound(rgcloader))
        {
          specimen.SetSound(istate3,rgcloader);
          rgcloader.resize(rgcloader.length()-strlen(".wav"));
        }
        else
        {
          rgcloader="";
          rgcloader.insert(0,specimen.GetSoundName(istate3),0,specimen.GetSoundName(istate3).length()-strlen(".wav"));
        }
        break;
      }
      break;
    } //switch (keysym)
  }//if key == false
  else
  {
    savecolor(false);
  }
  break;
/////////////////////////////////////////////////////////////////istate==15////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////add gizmos//////////////////////////////////////////////////////
  case 15:
    //istate2==which gizmo you're editing
    //istate3 / 0==edit spawn type, etc. of current gizmo
             // 1==add a new gizmo
    if(getkey(event,rgcloader)==false)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        switch(istate3)
        {
        case 0:
          StateSwitch(0);
          break;
        case 1:
          istate3=0;
          break;
        }
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_s:
        if(event.key.keysym.mod & KMOD_ALT)
          Save();
        break;
      case SDLK_KP_PLUS:
        istate3=1;
        rgcloader="";
        break;
      case SDLK_DELETE:
        icemap.ZapGiz();
        if(istate2>0)
          istate2-=1;
        savecolor(false);
        break;
      case SDLK_RETURN:
        switch(istate3)
        {
        case 0:  //edit spawn type and stuff
          //don't do anything
          break;
        case 1:  //add new gizmo
          rgcfilename=rgcloader+".giz";
          if(!icemap.InsertMonster(rgcfilename,0,0,0,false,picbox))
          {
            rgcloader="";
          }
          else
          {
            istate3=0;  //edit spawn type, etcx
            istate2=icemap.GetMonsterBoxSize()-1;
            icemap.MonsterTaxi(istate2);
            icemap.SetSpawnType(0);
          }
          break;
        }
        break;
      case SDLK_PAGEUP:
        istate2+=1;
        if(istate2>=icemap.GetMonsterBoxSize())
          istate2=0;
        icemap.MonsterTaxi(istate2);
        break;
      case SDLK_PAGEDOWN:
        istate2-=1;
        if(istate2<0)
          istate2=icemap.GetMonsterBoxSize()-1;
        icemap.MonsterTaxi(istate2);
        break;
      case SDLK_F2:
        if(icemap.GetMonsterBoxSize()>0)
          istate=16;
        break;
      } //switch (keysym)
    }
    else
    {
      savecolor(false);
    }
    arrow(event);
    break;
///////////////////////////////////////////////////////////////////////////istate==16/////////////////////////////
/////////////////////////////////////////////////////////////////pic spawn point////////////////////////////////
  case 16:   //pick spawn point (from case 15)
    break;
//////////////////////////////////////////////////////////////istate==17////////////////////////////////////////
////////////////////////////////////////////////////////////add layers/////////////////////////////////////////////
  case 17:
    //istate2==which layer
    //istate3==which filename you're editing
    if(getkey(event,rgcloader)==false)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        StateSwitch(0);
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_s:
        if(event.key.keysym.mod & KMOD_ALT)
        {
          Save();
          rgcloader="";
          rgcloader.insert(0,icemap.GetAniLayerName(istate2),0,icemap.GetAniLayerName(istate2).length()-strlen(".ani"));
        }
        break;
      case SDLK_DELETE:
        icemap.AniLayerDeath(istate2);
        rgcloader="";
        rgcloader.insert(0,icemap.GetAniLayerName(istate2),0,icemap.GetAniLayerName(istate2).length()-strlen(".ani"));
        savecolor(false);
        break;
      case SDLK_RETURN:
        rgcfilename=rgcloader+".ani";

        if(!icemap.AniLayerSpawn(rgcfilename,picbox,istate2))
        {
          rgcloader="";
          rgcloader.insert(0,icemap.GetAniLayerName(istate2),0,icemap.GetAniLayerName(istate2).length()-strlen(".ani"));
        }
        break;
      case SDLK_PAGEUP:
        istate2=1;
        rgcloader="";
        rgcloader.insert(0,icemap.GetAniLayerName(istate2),0,icemap.GetAniLayerName(istate2).length()-strlen(".ani"));
        break;
      case SDLK_PAGEDOWN:
        istate2=0;
        rgcloader="";
        rgcloader.insert(0,icemap.GetAniLayerName(istate2),0,icemap.GetAniLayerName(istate2).length()-strlen(".ani"));
        break;
      } //switch (keysym)
    }
    else
    {
      savecolor(false);
    }
    arrow(event);
    break;
////////////////////////////////////////////////////////////istate==18///////////////////////////////////////////////////////
///////////////////////////////////////////////////////edit anibox////////////////////////////////////////////////////////////
  case 18:
    //istate2: 0==try to open pre-existing file
             //1==edit image names
             //2==set type (sets anitest.itype directly)
             //3==#of images (use istate3)
    //istate3: used in istate2==1 and istate2==3
    if(getkey(event,rgcloader)==false)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        anitest.Death();
        StateSwitch(0);
        break;
      case SDLK_F2:  //load a new map
        if(istate2==0)
        {
          icemap.Apocalypse();
          hackmap.Apocalypse();
          StateSwitch(2);
        }
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_F3:
        switch(istate2)
        {
        case 0:
          break;
        case 1:
          //istate2=2;  what is this?
          break;
        case 2:
          break;
        }
        break;
      case SDLK_F6:
        switch(istate2)
        {
        case 1:
          istate2=4;
          break;
        }
        break;
      case SDLK_s:
        if(event.key.keysym.mod & KMOD_ALT)
        {
          switch(istate2)
          {
          case 1:
            anitest.Writebox(picbox);
            savecolor(true);
            break;
          }
        }
        break;
      case SDLK_RETURN:
        switch(istate2)
        {
        case 0:
          istate3=0;
          rgcloader=rgcloader+".ani";

          if(!anitest.Spawnbox(rgcloader, picbox))
          {
            istate2=2;
          }
          else
          {
            istate3=0;
            savecolor(true);
            rgcloader="";
            rgcloader.insert(0,picbox.GetName(anitest.Getpic(istate3)),0,picbox.GetName(anitest.Getpic(istate3)).length()-strlen(".jpg"));
            istate2=1;
          }
          break;
        case 1:  //editing filenames in giz file  (uses istate3)
          rgcfilename=rgcloader+".jpg";
          anitest.Swap_Pic(rgcfilename,istate3,picbox);
          if(anitest.Getpic(istate3)!=0)
            istate3+=1;
          else
            rgcloader="";
          break;
        case 2:  //get type (sets type directly in anitest)
          istate2=3;
          istate3=0;
          break;
        case 3:  //get the number of png files (uses istate3)
          anitest.SetSize(rgcloader,istate3,istate4);
          istate2=1;
          istate3=0;
          break;
        case 4:  //set iloop
          istate2=1;
          break;
        }
        break;
      } //switch (keysym)
    }
    else
    {
      savecolor(false);
    }
    break;
//////////////////////////////////////////istate==19////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////change music////////////////////////////////////////////
  case 19:
    if(getkey(event,rgcloader)==false)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        StateSwitch(0);
        break;
      case SDLK_q:
        if(event.key.keysym.mod & KMOD_ALT)
          Quit();
        break;
      case SDLK_s:
        if(event.key.keysym.mod & KMOD_ALT)
        {
          Save();
          rgcloader="";
          rgcloader.insert(0,icemap.GetSong(),0,icemap.GetSong().length()-strlen(".mid"));
        }
        break;
      case SDLK_RETURN:
        rgcloader+=".mid";
        if(boombox.Playsong(rgcloader))
        {
          icemap.SetSong(rgcloader);
          rgcloader.resize(rgcloader.length()-4);
        }
        else
        {
          rgcloader="";
          rgcloader.insert(0,icemap.GetSong(),0,icemap.GetSong().length()-strlen(".mid"));
        }
        break;
      }
    }
    else
    {
      savecolor(false);
    }
    arrow(event);
    break;
  }  //switch (istate)
}

void EditBox::arrow(SDL_Event &event)
{
  switch(event.key.keysym.sym)
  {
  case SDLK_UP:
    Fade();
    up();
    break;
  case SDLK_DOWN:
    Fade();
    down();
    break;
  case SDLK_LEFT:
    Fade();
    left();
    break;
  case SDLK_RIGHT:
    Fade();
    right();
    break;
  }
}
