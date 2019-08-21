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

#include "MapBox.h"

MapBox::MapBox()
{
  layer[0]=0;
  layer[1]=0;
}

MapBox::~MapBox()
{
}

//don't free map images from OpenGL yet, pass a copy of imgmap back to GameBox and let GameBox free them when
//it wants to
//need to send back:
//   -Gizbox pics
//   -skylayer
//   -waterlayer
//   -layer1
//   -layer2
void MapBox::Apocalypse()
{
  int ix;

  mapgrid.Killmatrix();
  mapname="";
  for(ix=0;ix<4;ix++)
    link[ix]="";
  cave.KillSpecBox();
  monsterbox.KillGizBox();
  splatterbox.KillGizBox();
  do
  {
  }while(monsterstore.PopPic());
  attacknodes.Apocalypse();
  anilayer[0].Death();
  anilayer[1].Death();
  layer[0]=0;
  layer[1]=0;
}

bool MapBox::Loadmap(std::string strmapfile, bool bedit, ImageVault &picbox)
{
  std::ifstream infile;
  int ix;
  int icevector[3];
  std::string temp;
  bool breturn=true;
  int itemp;
  int multispawn;

  Apocalypse();
  mapname=strmapfile;

  strmapfile=Pathfinder::Map_Path+strmapfile;

  breturn=Normal_File(strmapfile);
  if(breturn)
  {
    infile.open(strmapfile.c_str(),std::ios::in|std::ios::binary);
    breturn=!infile.fail();
  }
  if(breturn)
    breturn=mapgrid.Readmatrix(infile);  //returns false only if matrix fails to spawn
  if(breturn)
  {
    infile.ignore();
    for(ix=0;ix<LAYERMAX;ix++)
    {
      getline(infile,temp);
      //temp="Data/Images/"+temp;
      picbox.ImageLoader(temp,layer[ix]);
    }
    breturn=!infile.fail();
  }
  if(breturn)  //breturn is false now if there is no layer1
  {
    //grab sidelinks, don't bother checking if they actually exist, game can handle junk sidelinks
    for(ix=0;ix<4;ix++)
    {
      getline(infile,link[ix]);
      //link[ix]="Data/Maps/"+link[ix];
    }
    breturn=!infile.fail();
  }
  if(breturn)
  {
    //grab cave links here!
    infile>>itemp;
    if(infile.fail())
    {
      breturn=false;
      itemp=0;
    }
    for(ix=0;ix<itemp;ix++)
    {
      infile>>icevector[0];
      infile>>icevector[1];
      infile>>icevector[2];
      infile>>temp;
      //temp="Data/Maps/"+temp;
      cave.InsertTail(icevector[0],icevector[1],icevector[2],temp);
    }
    breturn=!infile.fail();
  }
  if(breturn)
  {
    infile.ignore();
    for(ix=0;ix<LAYERMAX;ix++)
    {
      getline(infile,temp);
      //temp="Data/Anibox/"+temp;
      anilayer[ix].Spawnbox(temp,picbox);
    }
    breturn=!infile.fail();
  }
  if(breturn)
  {
    //load monsters
    monsterbox.KillGizBox();
    infile>>itemp;
    if(infile.fail())
    {
      itemp=0;
      breturn=false;
    }
    for(ix=0;ix<itemp;ix++)
    {
      infile>>icevector[0];  //x spawn?
      infile>>icevector[1];  //y spawn?
      infile>>icevector[2];  //spawn type
      infile>>temp;
      //temp="Data/Gizmos/"+temp;

      //this is the one place where we're loading the map differently depending on if we're using the editor or game engine
      if(!bedit)
      {
         switch(icevector[2])
         {
         case 0:
            multispawn=0;
            break;
         case 1:
            multispawn=9;
            break;
         case 2:
            multispawn=99;
            break;
         case 3:
            multispawn=999;
            break;
         case 4:
            multispawn=9999;  //this is just plain loony
            break;
         default:
            multispawn=1;
            break;
         }
         //check the return on next two calls, kill game if fails to load a guy?
         monsterbox.InsertNode(temp,icevector[0]*16+8,icevector[1]*16+8,multispawn, false, picbox);
      }
      else
      {
         monsterbox.InsertNode(temp,icevector[0]*16+8,icevector[1]*16+8,0,false, picbox);
         monsterbox.SetSpawnType(icevector[2]);
      }
    }
    breturn=!infile.fail();
    if(breturn)
    {
      infile.ignore();
      getline(infile,song);
    }
    breturn=!infile.fail();
  }
  if(breturn==false)
    Apocalypse();

  infile.close();

  return breturn;
}

void MapBox::Morph(int irow, int icol)
{
   monsterbox.KillGizBox();

   mapgrid.Rematrix(irow, icol);
}

bool MapBox::Writemap(ImageVault &picbox)
{
  std::ofstream outfile;
  int ix;
  std::string temp;
  bool breturn=false;

  if(mapname!="")
  {
    temp=Pathfinder::Map_Path+mapname;
    outfile.open(temp.c_str(),std::ios::out|std::ios::binary);
    breturn=!outfile.fail();
  }

  if(breturn)
  {
    mapgrid.Writematrix(outfile);

    for(ix=0;ix<LAYERMAX;ix++)
      outfile<<picbox.GetName(layer[ix])<<"\n";

    for(ix=0;ix<4;ix++)
    {
      //temp="";
      //if(link[ix]!="")
      //  temp.insert(0,link[ix],strlen("Data/Maps/"),link[ix].length()-strlen("Data/Maps/"));
      //outfile<<temp<<"\n";
      outfile<<link[ix]<<"\n";
    }

    outfile<<cave.GetSize()<<"\n";
    cave.Reset();
    while(cave.End()==false)
    {
      outfile<<cave.GetNode().icespec[0]<<" ";
      outfile<<cave.GetNode().icespec[1]<<" ";
      outfile<<cave.GetNode().icespec[2]<<"\n";
      //temp="";
      //temp.insert(0,cave.GetNode().name,strlen("Data/Maps/"),
      //            cave.GetNode().name.length()-strlen("Data/Maps/"));
      //outfile<<temp<<"\n";
      outfile<<cave.GetNode().name<<"\n";
      cave.Next();
    }

    for(ix=0;ix<LAYERMAX;ix++)
    {
  //    temp="";
    //  if(anilayer[ix].GetName()!="")
      //  temp.insert(0,anilayer[ix].GetName(),0,anilayer[ix].GetName().length()-strlen("Data/Anibox"));
      //outfile<<temp<<"\n";
      outfile<<anilayer[ix].GetName()<<"\n";
    }
    temp="";

    outfile<<monsterbox.GetGizBoxSize()<<"\n";
    monsterbox.Reset();
    while(monsterbox.End()==false)
    {
      outfile<<int(monsterbox.GetHor())/16<<" ";
      outfile<<int(monsterbox.GetVert())/16<<" ";
      outfile<<monsterbox.GetSpawnType()<<"\n";

      //temp="";
      //temp.insert(0,monsterbox.GetName(),strlen("Data/Gizmos/"),monsterbox.GetName().length()-strlen("Data/Gizmos/"));
      //outfile<<temp<<"\n";
      outfile<<monsterbox.GetName()<<"\n";
      monsterbox.Next();
    }

    outfile<<song<<"\n";
  }

  outfile.close();
  return breturn;
}

std::string MapBox::GetSideLink(int ival)
{
  std::string strval;

  if(ival>=0&&ival<=3)
    strval=link[ival];

  return strval;
}

bool MapBox::SetSideLink(int ival, std::string strval)
{
  if(ival>=0&&ival<=3)
  {
    link[ival]=strval;
    return true;
  }
  else
  {
    return false;
  }
}

bool MapBox::Loaded()
{
  if(mapname!="")
    return true;
  else
    return false;
}

bool MapBox::Rename(std::string strval, ImageVault &picbox)
{
  std::ofstream outfile;

  strval=Pathfinder::Map_Path+strval;

  outfile.open(strval.c_str());
  outfile.close();

  if(Normal_File(strval))
  {
    mapname="";
    mapname.insert(0,strval,Pathfinder::Map_Path.length(),strval.length()-Pathfinder::Map_Path.length());
    Writemap(picbox);
    return true;
  }
  else
  {
    return false;
  }
}

std::string MapBox::GetName()
{
  return mapname;
}

void MapBox::SetSong(std::string name)
{
  song=name;
}

std::string MapBox::GetSong()
{
  return song;
}

GLuint MapBox::GetLayer(int ival)
{
  if(ival>=0&&ival<LAYERMAX)
    return layer[ival];
  else
    return 0;
}

bool MapBox::Music(AudioBox &boombox)
{
  boombox.Playsong(song);
}

std::string MapBox::GetLayerName(int ival, ImageVault &picbox)
{
  std::string strval;

  if(ival>=0&&ival<LAYERMAX)
    strval=picbox.GetName(layer[ival]);

  return strval;
}

GLuint MapBox::LoadLayer(std::string strfile, ImageVault &picbox, int ival)
{
  GLuint GLval=0;

  if(ival>=0&&ival<LAYERMAX)
  {
    GLval=layer[ival];
    if(!picbox.ImageLoader(strfile, layer[ival]))
    {
      layer[ival]=GLval;
      GLval=0;
    }
  }

  return GLval;
}

GLuint MapBox::KillLayer(int ival)
{
  GLuint GLval=0;

  if(ival>=0&&ival<LAYERMAX)
  {
    GLval=layer[ival];
    layer[ival]=0;
  }
  return GLval;
}

bool MapBox::WarpGiz(Gizmo &player,float x, float y, int iface, bool bcenter)
{
  return player.Teleport(x,y,iface,mapgrid,bcenter);
}

bool MapBox::WarpGiz(Gizmo &player, Speckeeper &specval,bool bcenter)
{
  return player.Teleport(float(specval.icespec[1])*16.0f,float(specval.icespec[2])*16.0f,specval.icespec[0],mapgrid,bcenter);
}

Iceblock MapBox::Gizmove(Gizmo &player, int idirection, Uint32 history)
{
  return player.Gizmove(idirection,history,mapgrid);
}

Iceblock MapBox::Gizrun(Gizmo &player, int idirection, Uint32 history)
{
  return player.Gizrun(idirection,history,mapgrid);
}
//   Iceblock Gizmove(int idirection, Uint32 history, Icematrix &mapgrid);
//   Iceblock Gizrun(int idirection, Uint32 history, Icematrix &mapgrid);


//UpdateMonsters calls Gizmo.gizupdate a lot from within monsterbox so this function is never called by
//monsters, only by hero.  So this actual Gizmo* return will always be NULL for now
//(*enemy is actually passed as NULL for now)
Gizmo* MapBox::gizupdate(Gizmo *self,Gizmo *enemy, ImageVault &picbox, AudioBox &boombox, Uint32 history)
{
  self->gizupdate(enemy,mapgrid,picbox,boombox,history,attacknodes);
}

void MapBox::BombDrop(Gizmo &player, AudioBox &boombox)
{
  player.Attack(&boombox,attacknodes);
}

int MapBox::GetCaveSize()
{
  return cave.GetSize();
}

void MapBox::ResetCave()
{
  cave.Reset();
}

Speckeeper MapBox::GetCaveNode()
{
  return cave.GetNode();
}

bool MapBox::SetCaveNode(Speckeeper &specimen)
{
  return cave.Clone(specimen);
}

bool MapBox::ZapCaveNode(int ival)
{
  return cave.ZapSpecNode(ival);
}

bool MapBox::LoadCaveNode(Speckeeper &specimen)
{
  return cave.InsertTail(specimen.icespec[0],specimen.icespec[1],specimen.icespec[2],specimen.name);
}

bool MapBox::ChooseCaveNode(int ival)
{
  return cave.SpecTaxi(ival);
}

void MapBox::KillCave()
{
  cave.KillSpecBox();
}

void MapBox::ResetMonsters()
{
  monsterbox.Reset();
}

bool MapBox::MonsterEnd()
{
  return monsterbox.End();
}

int MapBox::MonsterHor()
{
  return monsterbox.GetHor();
}

int MapBox::MonsterVert()
{
  return monsterbox.GetVert();
}

GLuint MapBox::GetMonsterPic()
{
  return monsterbox.GetPic();
}

GLuint MapBox::GetMonsterPic(int ival)
{
  return monsterbox.GetPic(ival);
}

int MapBox::GetMonsterType()
{
  return monsterbox.GetType();
}

int MapBox::GetSpawnType()
{
  return monsterbox.GetSpawnType();
}

bool MapBox::SetSpawnType(int ival)
{
  return monsterbox.SetSpawnType(ival);
}

bool MapBox::ZapGiz()
{
  return monsterbox.ZapGiz();
}

void MapBox::NextMonster()
{
  monsterbox.Next();
}

bool MapBox::MonsterHurt()
{
  return monsterbox.GetHurt();
}

//returns # of Gizmos in monsterbox
int MapBox::GetMonsterBoxSize()
{
  return monsterbox.GetGizBoxSize();
}

float MapBox::GetMonsterSpin()
{
  return monsterbox.GetSpin();
}

float MapBox::GetMonsterSize()
{
  return monsterbox.GetSize();
}

void MapBox::UpdateMonsters(Gizmo *self, Uint32 history, ImageVault &picbox, AudioBox &boombox)
{
  monsterbox.Update(self,mapgrid,history,picbox,boombox,attacknodes,splatterbox);
}

bool MapBox::MonsterTaxi(int ival)
{
  return monsterbox.GizTaxi(ival);
}

std::string MapBox::GetMonsterName()
{
  return monsterbox.GetName();
}

bool MapBox::InsertMonster(std::string strval, int hor, int vert, int icopy, bool bhead, ImageVault &picbox)
{
  return monsterbox.InsertNode(strval,hor,vert,icopy,bhead,picbox);
}


//bool GizBox::Warp(float x, float y, Icematrix &mapgrid)
bool MapBox::WarpMonster(float x, float y)
{
  return monsterbox.Warp(x,y,mapgrid);
}

void MapBox::NukeMonsters()
{
  monsterbox.KillGizBox();
}

//returns true if all monsters are dead
bool MapBox::Clear()  //get rid of this
{
  return monsterbox.Clear();
}

void MapBox::UpdateSplatter(Gizmo *self, Uint32 history, ImageVault &picbox, AudioBox &boombox)
{
  splatterbox.Update(self,mapgrid,history,picbox,boombox,attacknodes,splatterbox);
}

int MapBox::Get_Rows()
{
  return mapgrid.Get_Rows();
}

int MapBox::Get_Columns()
{
  return mapgrid.Get_Columns();
}

Iceblock MapBox::Grab_Block(int y, int x)
{
  return mapgrid.Grab_Element(y,x);
}

bool MapBox::Set_Element(float y, float x, Iceblock iceval)
{
  return mapgrid.Set_Element(y,x,iceval);
}

void MapBox::KillMatrix()
{
  mapgrid.Killmatrix();
}

//0 = waterlayer 1=skylayer
//if we ever make more than two of these then I guess make an array of
//anibox but no point really for just two of them
bool MapBox::GotAniLayer(int ival)
{
  if(ival>=0&&ival<ANILAYER)
    return anilayer[ival].Loaded();
  else
    return false;
}

GLuint MapBox::GetAniLayerPic(int ival)
{
  if(ival>=0&&ival<ANILAYER)
    return anilayer[ival].Getpic();
  else
    return 0;
}

std::string MapBox::GetAniLayerName(int ival)
{
  std::string strval;

  if(ival>=0&&ival<ANILAYER)
    strval=anilayer[ival].GetName();

  return strval;
}

void MapBox::UpdateAniLayers(Uint32 elticko)
{
  int ix;

  for(ix=0;ix<ANILAYER;ix++)
    anilayer[ix].Update(elticko);
}

bool MapBox::AniLayerSpawn(std::string anifile, ImageVault &picbox, int ival)
{
  if(ival>=0&&ival<ANILAYER)
    return anilayer[ival].Spawnbox(anifile,picbox);
  else
    return false;
}

void MapBox::AniLayerDeath(int ival)
{
  if(ival>=0&&ival<ANILAYER)
    anilayer[ival].Death();
}

int MapBox::AniLayerType(int ival)
{
  if(ival>=0&&ival<ANILAYER)
    return anilayer[ival].GetType();
  else
    return 0;
}

void MapBox::ResetAttackNodes()
{
  attacknodes.Reset();
}

bool MapBox::AttackNodeEnd()
{
  return attacknodes.End();
}

float MapBox::GetAttackHor()
{
  return attacknodes.GetHor();
}

float MapBox::GetAttackVert()
{
  return attacknodes.GetVert();
}

float MapBox::GetAttackSize()
{
  return attacknodes.GetSize();
}

void MapBox::NextAttackNode()
{
  attacknodes.Next();
}
