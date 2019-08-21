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

void EditBox::draw()
{
  float ftrash;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  switch(istate)
  {
////////////////////////////////////////////////////////istate==0////////////////////////////////////////////////
///////////////////////////////////////////////menu///////////////////////////////////////////////////////////////
  case 0:
    glEnable(GL_TEXTURE_2D);
    glColor3fv(rgfheader);
    typewriter.glPrint(230,360,"ICECUBEFLOWER MAP EDITOR 3000");
    typewriter.glPrint(210,386,"At WAR against the 3rd dimension.");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
    icemap.drawgiz(0,fx,fy,false,mWidth,mHeight,subWidth,subHeight);
    icemap.drawstore();
    glDisable(GL_TEXTURE_2D);
    drawhero();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    drawblocks(icemap,fx,fy,mWidth,mHeight);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //drawmenu() menu and drawfade() take care of their own GL_TEXTURE_2D and leave it Enabled
    if(istate2==0)  //if drawing menu
    {
      if(hero.GetHor()<512.0f&&hero.GetVert()<384.0f)
        drawmenu(574);
      else
        drawmenu(0);
    }
    break;
///////////////////////////////////////////////////istate==1//////////////////////////////////////////////////////////////
//////////////////////////////////////////rename map///////////////////////////////////////////////////////////////
  case 1:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
    glDisable(GL_TEXTURE_2D);

    DrawBackDrop(ftrash);

    glEnable(GL_TEXTURE_2D);
    glColor3fv(rgfheader);
    typewriter.glPrint(150,528,"Name the map: ");
    glColor3fv(rgfedit);
    typewriter.glPrint(380-16*(rgcloader.length()),544,rgcloader.c_str());
    typewriter.glPrint(380,544,".map");


    glDisable(GL_TEXTURE_2D);
    drawhero();
    break;
///////////////////////////////////////////////////istate==2//////////////////////////////////////////////////////////////
//////////////////////////////////////////open a new map///////////////////////////////////////////////////////////////
  case 2:
    glEnable(GL_TEXTURE_2D);
    glColor3fv(rgfheader);
    typewriter.glPrint(150,528,"Enter the name of a map to open: ");
    glColor3fv(rgfedit);
    typewriter.glPrint(380-16*(rgcloader.length()),544,rgcloader.c_str());
    typewriter.glPrint(380,544,".map");
    glColor3fv(rgfadvice);
    typewriter.glPrint(16,716, "To figure out how to create a map to load, read the manual.txt");
    typewriter.glPrint(16,732, "if I ever bothered to write it. -icecubeflower");
    break;
///////////////////////////////////////////////////istate==3//////////////////////////////////////////////////////////////
///////////////////////////////////////////////create a map///////////////////////////////////////////////////////////////
  case 3:
    glEnable(GL_TEXTURE_2D);
    glColor3fv(rgfheader);
    switch(istate2)
    {
    case 0:
      typewriter.glPrint(150,528,"Enter the name of the layer1 .png file: ");
      glColor3fv(rgfedit);
      typewriter.glPrint(380-16*(rgcloader.length()),544,rgcloader.c_str());
      typewriter.glPrint(380,544,".png");
      glColor3fv(rgfadvice);
      typewriter.glPrint(64,716, "OMG! WTF!? %s does not exist!", icemap.GetName().c_str());
      break;
    case 1:
      typewriter.glPrint(150,528,"How many screens tall do you want the map to be?: ");
      glColor3fv(rgfedit);
      typewriter.glPrint(380,544,"%i screens tall",istate3);
      glColor3fv(rgfadvice);
      typewriter.glPrint(64,700, "mapname= %s", icemap.GetName().c_str());
      typewriter.glPrint(64,716, "layer1 = %s", icemap.GetLayerName(0,picbox).c_str());//icemap.layer1.c_str());
      break;
    case 2:
      typewriter.glPrint(150,528,"How many screens wide do you want the map to be?: ");
      glColor3fv(rgfedit);
      typewriter.glPrint(380,544,"%i screens wide",istate4);
      glColor3fv(rgfadvice);
      typewriter.glPrint(64,684, "mapname= %s", icemap.GetName().c_str());
      typewriter.glPrint(64,700, "layer1 = %s", icemap.GetLayerName(0,picbox).c_str());//icemap.layer1.c_str());
      typewriter.glPrint(64,716, "rows   = %i", istate3);
      break;
    case 3:
      typewriter.glPrint(64,600,"All good? (hit enter or escape)");
      glColor3fv(rgfadvice);
      typewriter.glPrint(64,668, "mapname= %s", icemap.GetName().c_str());
      typewriter.glPrint(64,684, "layer1 = %s", icemap.GetLayerName(0,picbox).c_str());//icemap.layer1.c_str());
      typewriter.glPrint(64,700, "rows   = %i", istate3);
      typewriter.glPrint(64,716, "columns= %i", istate4);
      break;
    default:
      typewriter.glPrint(64,716, "istate2==%i, that wasn't supposed to happen", istate2);
      break;
    }
    break;
///////////////////////////////////////////////////istate==4//////////////////////////////////////////////////////////////
///////////////////////////////////////////////add layers///////////////////////////////////////////////////////////////
  case 4:
    glEnable(GL_TEXTURE_2D);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);

    DrawBackDrop(ftrash);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),544-int(ftrash),rgcloader.c_str());
      typewriter.glPrint(160,544-int(ftrash),".png");

    glColor3fv(rgfheader);
    switch(istate2)
    {
    case 0:
      typewriter.glPrint(0,528-int(ftrash),"layer1");
      break;
    case 1:
      typewriter.glPrint(0,528-int(ftrash),"layer2");
      break;
    }

    glColor3fv(rgfadvice);
    typewriter.glPrint(16,732-int(ftrash), "Use PGUP/PGDN");
    typewriter.glPrint(16,748-int(ftrash), "Note: Just read the manual.txt");

    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(300.0,540.0-ftrash,0.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, icemap.GetLayer(istate2));
    glBegin(GL_POLYGON);
      glTexCoord2f(0.0,0.0);	glVertex3f(0,0,0.0);
      glTexCoord2f(1.0,0.0);	glVertex3f(256,0,0.0);
      glTexCoord2f(1.0,1.0);	glVertex3f(256,192,0.0);
      glTexCoord2f(0.0,1.0);	glVertex3f(0,192,0.0);
    glEnd();
    glPopMatrix();

    glColor3fv(rgfadvice);
    typewriter.glPrint(600,616-int(ftrash),"RETURN <INPUT>");
    typewriter.glPrint(600,632-int(ftrash),"Delete <Zap it>");
    typewriter.glPrint(600,648-int(ftrash),"alt-S  <SAVE>");

    glDisable(GL_TEXTURE_2D);
    drawhero();
    break;
///////////////////////////////////////////////////istate==5//////////////////////////////////////////////////////////////
///////////////////////////////////////////////     resize ///////////////////////////////////////////////////////////////
  case 5:
    glEnable(GL_TEXTURE_2D);
    switch(istate2)
    {
    case 0: //get rows
      glColor3fv(rgfadvice);
      typewriter.glPrint(150,528,"How many screens tall?: %i",istate3);
      break;
    case 1: //get columns
      glColor3fv(rgfheader);
      typewriter.glPrint(150,528,"How many screens tall?: %i",istate3);
      glColor3fv(rgfadvice);
      typewriter.glPrint(150,544,"How many screens wide?: %i",istate4);
      break;
    }
    break;
///////////////////////////////////////////////////istate==8//////////////////////////////////////////////////////////////
///////////////////////////////////////////////block edit///////////////////////////////////////////////////////////////
  case 8:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
    icemap.drawgiz(0,fx,fy,false,mWidth,mHeight,subWidth,subHeight);
    icemap.drawstore();

    glDisable(GL_TEXTURE_2D);
    drawhero();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    drawblocks(icemap,fx,fy,mWidth,mHeight);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    break;
///////////////////////////////////////////////////istate==9//////////////////////////////////////////////////////////////
///////////////////////////////////////////////mouse edit///////////////////////////////////////////////////////////////
  case 9:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
icemap.drawgiz(0,fx,fy,false,mWidth,mHeight,subWidth,subHeight);
    icemap.drawstore();

    glDisable(GL_TEXTURE_2D);
    mdrawhero();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    drawblocks(icemap,fx,fy,mWidth,mHeight);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    break;
///////////////////////////////////////////////////istate==10//////////////////////////////////////////////////////////////
///////////////////////////////////////////////mouse///////////////////////////////////////////////////////////////
  case 10:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
icemap.drawgiz(0,fx,fy,false,mWidth,mHeight,subWidth,subHeight);
    icemap.drawstore();

    glDisable(GL_TEXTURE_2D);
    mdrawhero();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    drawblocks(icemap,fx,fy,mWidth,mHeight);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    break;
///////////////////////////////////////////////////istate==11//////////////////////////////////////////////////////////////
///////////////////////////////////////////////side links///////////////////////////////////////////////////////////////
  case 11:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);

    DrawBackDrop(ftrash);
    glEnable(GL_TEXTURE_2D);

    glColor3fv(rgfheader);
    switch(istate2)
    {
    case 0:
      typewriter.glPrint(0,528-int(ftrash),"Top link: ");
      break;
    case 1:
      typewriter.glPrint(0,528-int(ftrash),"Right link: ");
      break;
    case 2:
      typewriter.glPrint(0,528-int(ftrash),"Bottom link: ");
      break;
    case 3:
      typewriter.glPrint(0,528-int(ftrash),"Left link: ");
      break;
    default:
      typewriter.glPrint(0,528-int(ftrash),"messed UP");
      break;
    }
    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),544-int(ftrash),rgcloader.c_str());
    typewriter.glPrint(160,544-int(ftrash),".map");
    glColor3fv(rgfadvice);
    typewriter.glPrint(16,732-int(ftrash), "Use PGUP/PGDN");
    typewriter.glPrint(16,748-int(ftrash), "Note: I don't check your .map files.");
    typewriter.glPrint(600,616-int(ftrash),"RETURN <INPUT>");
    typewriter.glPrint(600,632-int(ftrash),"alt-S  <SAVE>");
    typewriter.glPrint(600,648-int(ftrash),"Delete <Kill a link>");

    if(hackmap.Loaded())
    {
      glColor3f(1.0,1.0,1.0);

      glBindTexture(GL_TEXTURE_2D, hackmap.GetLayer(0));
      glPushMatrix();
      glTranslatef(300.0f,540.0f-ftrash,0.0f);
      glBegin(GL_POLYGON);
        glTexCoord2f(0.0,0.0);	glVertex3f(0,0,0.0);
        glTexCoord2f(1.0,0.0);	glVertex3f(256,0,0.0);
        glTexCoord2f(1.0,1.0);	glVertex3f(256,192,0.0);
        glTexCoord2f(0.0,1.0);	glVertex3f(0,192,0.0);
      glEnd();
      glPopMatrix();
    }
    else
    {
      glColor3fv(rgfedit);
      typewriter.glPrint(370,620-int(ftrash),"NO FILE");
    }

    glDisable(GL_TEXTURE_2D);
    drawhero();
    break;
///////////////////////////////////////////////////istate==12//////////////////////////////////////////////////////////////
///////////////////////////////////////////////cave links///////////////////////////////////////////////////////////////
  case 12:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);

    DrawBackDrop(ftrash);

    glEnable(GL_TEXTURE_2D);

    switch(istate3)
    {
    case 0:
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528-int(ftrash),"Cave link %i: ",istate2);
      glColor3fv(rgfedit);
      typewriter.glPrint(160-16*(rgcloader.length()),544-int(ftrash),rgcloader.c_str());
      typewriter.glPrint(160,544-int(ftrash),".map");
      if(icemap.GetCaveSize()>0)
      {
        icemap.ChooseCaveNode(istate2);
        glColor3fv(rgfheader);
        typewriter.glPrint(0,576-int(ftrash),"Warp point:");
        glColor3fv(rgfedit);
        typewriter.glPrint(16,592-int(ftrash),"(%i,%i)",icemap.GetCaveNode().icespec[1],
                                                        icemap.GetCaveNode().icespec[2]);
        glColor3fv(rgfheader);
        typewriter.glPrint(0,624-int(ftrash),"Link type:");
        glColor3fv(rgfedit);
        switch(icemap.GetCaveNode().icespec[0])
        {
          case 0:
            typewriter.glPrint(16,640-int(ftrash),"0) cave down");
            break;
          case 1:
            typewriter.glPrint(16,640-int(ftrash),"1) cave up");
            break;
          case 2:
            typewriter.glPrint(16,640-int(ftrash),"2) cave right");
            break;
          case 3:
            typewriter.glPrint(16,640-int(ftrash),"3) cave left");
            break;
          default:
            typewriter.glPrint(16,640-int(ftrash),"%i",icemap.GetCaveNode().icespec[0]);
            break;
        }
      }
      glColor3fv(rgfadvice);
      typewriter.glPrint(16,748-int(ftrash), "Creating Cave Links for %s",icemap.GetName().c_str());

      if(hackmap.GetName()!="")
      {
        glColor3f(1.0,1.0,1.0);
        glBindTexture(GL_TEXTURE_2D, hackmap.GetLayer(0));
        glPushMatrix();
        glTranslatef(300.0,540.0-ftrash,0.0);
        glBegin(GL_POLYGON);
          glTexCoord2f(0.0,0.0);	glVertex3f(0,0,0.0);
          glTexCoord2f(1.0,0.0);	glVertex3f(256,0,0.0);
          glTexCoord2f(1.0,1.0);	glVertex3f(256,192,0.0);
          glTexCoord2f(0.0,1.0);	glVertex3f(0,192,0.0);
        glEnd();
        glPopMatrix();

        glColor3fv(rgfadvice);
        typewriter.glPrint(600,584-int(ftrash),"F2     <Warp point>");
        typewriter.glPrint(600,600-int(ftrash),"WHEEL  <Link type>");
        typewriter.glPrint(600,616-int(ftrash),"RETURN <INPUT>");
        typewriter.glPrint(600,632-int(ftrash),"alt-S  <SAVE>");
        typewriter.glPrint(600,664-int(ftrash),"Delete <Kill a link>");
        typewriter.glPrint(600,680-int(ftrash),"PGUP/PGDN <cycle>");
      }
      else
      {
        glColor3fv(rgfheader);
        typewriter.glPrint(370,620-int(ftrash),"NO FILE");
      }

      glColor3fv(rgfadvice);
      typewriter.glPrint(600,648-int(ftrash),"+      <Add a link>");
      break;
    case 1:
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528-int(ftrash),"New link: ");
      glColor3fv(rgfedit);
      typewriter.glPrint(160-16*(rgcloader.length()),544-int(ftrash),rgcloader.c_str());
      typewriter.glPrint(160,544-int(ftrash),".map");
      glColor3fv(rgfadvice);
      typewriter.glPrint(16,732-int(ftrash), "You have to enter a legit .map file and");
      typewriter.glPrint(16,748-int(ftrash), "hit enter before I'll add a cave link.");
      break;
    }

    glDisable(GL_TEXTURE_2D);
    drawhero();
    break;
///////////////////////////////////////////////////istate==13//////////////////////////////////////////////////////////////
///////////////////////////////////////////////pick warp point///////////////////////////////////////////////////////////////
  case 13:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(hackmap,fx,fy,mWidth,mHeight,subWidth,subHeight);

    glDisable(GL_TEXTURE_2D);
    mdrawhero();
    break;
///////////////////////////////////////////////////istate==14//////////////////////////////////////////////////////////////
///////////////////////////////////////////////edit gizmos///////////////////////////////////////////////////////////////
  case 14:
    //istate2: if you're picking a gizmo or editing file names
    //istate3: which filename you're editing
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    switch(istate2)
    {
    case 0:  //choosing a gizmo file
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528,"Gizmo file:");
      glColor3fv(rgfedit);
      typewriter.glPrint(160-16*(rgcloader.length()),544,rgcloader.c_str());
      typewriter.glPrint(160,544,".giz");
      glColor3fv(rgfadvice);
      typewriter.glPrint(16,748, "Enter a gizmo file.  (F2 to exit)");//  (Type only matters for new gizmos.)");
      typewriter.glPrint(200,150, "icecubeflower's GIZMO EDITOR 3000");
      typewriter.glPrint(250,182, "\"it'll edit yer gizmos\"");
      break;
    case 1:  //editing filenames in giz file
      PaintGizInfo(0);
      glColor3fv(rgfadvice);
      typewriter.glPrint(16,748, "Now you're entering filenames.");
      typewriter.glPrint(600,584,"filename %i/%i",istate3,specimen.GetMax()-1);
      typewriter.glPrint(600,600, "F5     <change sounds>");
      typewriter.glPrint(600,616, "WHEEL  <toggle filename>");
      typewriter.glPrint(600,632, "F3     <change type>");
      typewriter.glPrint(600,648, "RETURN <INPUT>");
      typewriter.glPrint(600,664, "alt-S  <SAVE>");

      if(specimen.GetPic(istate3)!=0)
      {
        glPushMatrix();
        glTranslatef(400.0,540.0,0.0);

        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0,1.0,1.0);

        glBegin(GL_POLYGON);
          glVertex3f(0,0,0.0);
          glVertex3f(192,0,0.0);
          glVertex3f(192,192,0.0);
          glVertex3f(0,192,0.0);
        glEnd();
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, specimen.GetPic(istate3));
        glBegin(GL_POLYGON);
          glTexCoord2f(0.0,0.0);	glVertex3f(0,0,0.0);
          glTexCoord2f(1.0,0.0);	glVertex3f(192,0,0.0);
          glTexCoord2f(1.0,1.0);	glVertex3f(192,192,0.0);
          glTexCoord2f(0.0,1.0);	glVertex3f(0,192,0.0);
        glEnd();
        glPopMatrix();
      }
      else
      {
        glColor3fv(rgfheader);
        typewriter.glPrint(370,620,"NO FILE");
      }

      break;
    case 2:
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528,"Gizmo file:");
      typewriter.glPrint(0,544,"%s",rgcloader.c_str());
      typewriter.glPrint(0,576,"Pick a Gizmo type:");
      glColor3fv(rgfedit);
      switch(istate3)
      {
      case 0:
        typewriter.glPrint(32,592,"%i) player",istate3);
        break;
      case 1:
        typewriter.glPrint(32,592,"%i) rat",istate3);
        break;
      case 2:
        typewriter.glPrint(32,592,"%i) mill",istate3);
        break;
      case 3:
        typewriter.glPrint(32,592,"%i) stain",istate3);
        break;
      case 4:
        typewriter.glPrint(32,592,"%i) bug",istate3);
        break;
      case 5:
        typewriter.glPrint(32,592,"%i) lightning bug",istate3);
        break;
      case 6:
        typewriter.glPrint(32,592,"%i) dragon",istate3);
        break;
      default:
        typewriter.glPrint(32,592,"%i) undefined",istate3);
        break;
      }
      glColor3fv(rgfadvice);
      typewriter.glPrint(600,600, "WHEEL <gizmo type>");
      typewriter.glPrint(16,732, "See manual.txt for type definitions.");
      break;
    case 3:  //edit sounds
//see Gizmo.h to know what the sounds mean
      PaintGizInfo(1);
      glColor3fv(rgfadvice);
      typewriter.glPrint(16,748, "Now you're entering sound filenames.");
      typewriter.glPrint(600,584,"filename %i/%i",istate3,SOUNDTOTAL-1);
      switch(istate3)
      {
      case 0:
        typewriter.glPrint(350,600, "PAIN");
        break;
      case 1:
        typewriter.glPrint(350,600, "DEATH");
        break;
      case 2:
        typewriter.glPrint(350,600, "ATTACK");
        break;
      default:
        typewriter.glPrint(350,600, "UNDEFINED");
        break;
      }
      typewriter.glPrint(600,616, "WHEEL  <toggle filename>");
      typewriter.glPrint(600,648, "RETURN <INPUT>");
      typewriter.glPrint(600,664, "alt-S  <SAVE>");
      break;
    default:
      glColor3f(1.0,0.0,0.0);
      typewriter.glPrint(384,384,"MESSED UP");
      typewriter.glPrint(0,576,"istate2:");
      typewriter.glPrint(0,592,"%i",istate2);
      break;
    }
    break;
///////////////////////////////////////////////////istate==15//////////////////////////////////////////////////////////////
///////////////////////////////////////////////add gizmos///////////////////////////////////////////////////////////////
  case 15:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
icemap.drawgiz(0,fx,fy,false,mWidth,mHeight,subWidth,subHeight);
    icemap.drawstore();

    glDisable(GL_BLEND);

    DrawBackDrop(ftrash);

    glEnable(GL_TEXTURE_2D);

    switch(istate3)
    {
    case 0:
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528-int(ftrash),"Gizmo %i: ",istate2);
      glColor3fv(rgfheader);

      icemap.MonsterTaxi(istate2);
      typewriter.glPrint(0,544-int(ftrash),icemap.GetMonsterName().c_str());

      typewriter.glPrint(0,576-int(ftrash),"Spawn point:");
      glColor3fv(rgfedit);
      if(icemap.GetMonsterBoxSize()>0)
        typewriter.glPrint(16,592-int(ftrash),"(%i,%i)",
                              int(icemap.MonsterHor())/16,
                              int(icemap.MonsterVert())/16);
      glColor3fv(rgfheader);
      typewriter.glPrint(0,624-int(ftrash),"Spawn type:");
      glColor3fv(rgfedit);
      if(icemap.GetMonsterBoxSize()>0)
      {
        switch(icemap.GetSpawnType())
        {
        case 0:
          typewriter.glPrint(0,640-int(ftrash),"%i) normal",icemap.GetSpawnType());
          break;
        case 1:
          typewriter.glPrint(0,640-int(ftrash),"%i) 10 gizmos",icemap.GetSpawnType());
          break;
        case 2:
          typewriter.glPrint(0,640-int(ftrash),"%i) 100 gizmos!",icemap.GetSpawnType());
          break;
        case 3:
          typewriter.glPrint(0,640-int(ftrash),"%i) 1000 GIZMOS!!!",icemap.GetSpawnType());
          glColor3f(0.0f,1.0f,0.0f);
          break;
        case 4:
          typewriter.glPrint(0,640-int(ftrash),"%i) 10000 GIZMOS!!!",icemap.GetSpawnType());
          glColor3fv(rgfadvice);
          typewriter.glPrint(0,656-int(ftrash)," Good luck.");
          break;
        default:
          typewriter.glPrint(16,640-int(ftrash),"%i) undefined",icemap.GetSpawnType());
          break;
        }
      }
      glColor3fv(rgfadvice);
      typewriter.glPrint(16,732-int(ftrash), "Use PGUP/PGDN");
      //gizreturn already set above
      if(icemap.GetMonsterPic()!=0)
      {
        glPushMatrix();
        glTranslatef(400.0,540.0-ftrash,0.0);

        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0,1.0,1.0);

        glBegin(GL_POLYGON);
          glVertex3f(0,0,0.0);
          glVertex3f(192,0,0.0);
          glVertex3f(192,192,0.0);
          glVertex3f(0,192,0.0);
        glEnd();
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, icemap.GetMonsterPic());
        glBegin(GL_POLYGON);
          glTexCoord2f(0.0,0.0);	glVertex3f(0,0,0.0);
          glTexCoord2f(1.0,0.0);	glVertex3f(192,0,0.0);
          glTexCoord2f(1.0,1.0);	glVertex3f(192,192,0.0);
          glTexCoord2f(0.0,1.0);	glVertex3f(0,192,0.0);
        glEnd();
        glPopMatrix();

        glColor3fv(rgfadvice);
        typewriter.glPrint(600,584-int(ftrash),"F2     <Spawn point>");
        typewriter.glPrint(600,600-int(ftrash),"WHEEL  <Spawn type>");
        typewriter.glPrint(600,616-int(ftrash),"Delete <Zap it>");
        typewriter.glPrint(600,632-int(ftrash), "alt-S  <SAVE>");
      }
      else
      {
        glColor3fv(rgfheader);
        typewriter.glPrint(370,620-int(ftrash),"NO GIZMOS");
      }
      glColor3fv(rgfadvice);
      typewriter.glPrint(600,648-int(ftrash),"+      <Add a gizmo>");
      break;
    case 1:
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528-int(ftrash),"New gizmo: ");
      glColor3fv(rgfedit);
      typewriter.glPrint(160-16*(rgcloader.length()),544-int(ftrash),rgcloader.c_str());
      typewriter.glPrint(160,544-int(ftrash),".giz");
      glColor3fv(rgfadvice);
      typewriter.glPrint(16,732-int(ftrash), "You have to enter a legit .giz file and");
      typewriter.glPrint(16,748-int(ftrash), "hit enter before I'll add it.");
      break;
    }

    glDisable(GL_TEXTURE_2D);
    drawhero();
    break;
///////////////////////////////////////////////////istate==16//////////////////////////////////////////////////////////////
///////////////////////////////////////////////pick spawn point///////////////////////////////////////////////////////////////
  case 16:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
icemap.drawgiz(0,fx,fy,false,mWidth,mHeight,subWidth,subHeight);
    icemap.drawstore();

    glDisable(GL_TEXTURE_2D);
    mdrawhero();
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    drawblocks(icemap,fx,fy,mWidth,mHeight);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    break;
///////////////////////////////////////////////////istate==17//////////////////////////////////////////////////////////////
///////////////////////////////////////////////add layers///////////////////////////////////////////////////////////////
  case 17:
    //istate2==which layer
    glEnable(GL_TEXTURE_2D);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);

    DrawBackDrop(ftrash);


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),544-int(ftrash),rgcloader.c_str());
      typewriter.glPrint(160,544-int(ftrash),".ani");
    glColor3fv(rgfheader);
    typewriter.glPrint(0,576-int(ftrash),"Layer type:");
    typewriter.glPrint(0,592-int(ftrash),"%i",icemap.AniLayerType(istate2));

    glColor3fv(rgfheader);
    switch(istate2)
    {
    case 0:
      typewriter.glPrint(0,528-int(ftrash),"waterlayer");
      break;
    case 1:
      typewriter.glPrint(0,528-int(ftrash),"skylayer");
      break;
    }


    glColor3fv(rgfedit);

    glColor3fv(rgfadvice);
    typewriter.glPrint(16,732-int(ftrash), "Use PGUP/PGDN");
    typewriter.glPrint(16,748-int(ftrash), "Note: Just read the manual.txt");

    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(300.0,540.0-ftrash,0.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, icemap.GetAniLayerPic(istate2));
    glBegin(GL_POLYGON);
      glTexCoord2f(0.0,0.0);	glVertex3f(0,0,0.0);
      glTexCoord2f(1.0,0.0);	glVertex3f(256,0,0.0);
      glTexCoord2f(1.0,1.0);	glVertex3f(256,192,0.0);
      glTexCoord2f(0.0,1.0);	glVertex3f(0,192,0.0);
    glEnd();
    glPopMatrix();

    glColor3fv(rgfadvice);
    typewriter.glPrint(600,616-int(ftrash),"RETURN <INPUT>");
    typewriter.glPrint(600,632-int(ftrash),"Delete <Zap it>");
    typewriter.glPrint(600,648-int(ftrash),"alt-S  <SAVE>");

    glDisable(GL_TEXTURE_2D);
    drawhero();
    break;
///////////////////////////////////////////////////istate==18//////////////////////////////////////////////////////////////
///////////////////////////////////////////////edit anibox's///////////////////////////////////////////////////////////////
  case 18:
     //istate2: 0==choose an anibox file
             // 1==edit image names    (uses istate3)
             // 2==pick animation type (uses istate4)
             // 3==pick # of images    (uses istate3)
             // 4==change loop #
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    switch(istate2)
    {
    case 0:  //choosing an animation file
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528,"Animation Box:");
      glColor3fv(rgfedit);
      typewriter.glPrint(160-16*(rgcloader.length()),544,rgcloader.c_str());
      typewriter.glPrint(160,544,".ani");
      glColor3fv(rgfadvice);
      typewriter.glPrint(16,748, "Enter an Anibox file.  (F2 to exit)");//  (Type only matters for new gizmos.)");
      typewriter.glPrint(200,150, "icecubeflower's ANIBOX EDITOR 3000");
      typewriter.glPrint(250,182, "\"it'll edit yer anibox's\"");
      break;
    case 1:  //editing image names in anibox file  (uses istate3)
    case 4:  //change loop #
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528,"Animation file:");
      typewriter.glPrint(0,544,anitest.GetName().c_str());
      typewriter.glPrint(0,576,"Anibox type:");
      typewriter.glPrint(0,624,"file:");
      switch(anitest.GetType())
      {
      case 0:
        typewriter.glPrint(32,592,"%i) standard",anitest.GetType());
        if(istate2==1)
          glColor3fv(rgfedit);
        typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
        typewriter.glPrint(160,640,".jpg");
        break;
      default:
        typewriter.glPrint(32,592,"%i) undefined",anitest.GetType());
        glColor3fv(rgfedit);
        typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
        typewriter.glPrint(160,640,".jpg");
        break;
      }
      if(istate2==1)
        glColor3fv(rgfheader);
      else
        glColor3fv(rgfedit);
      typewriter.glPrint(0,672,"Loop image: %i",anitest.GetLoop());
      glColor3fv(rgfadvice);
      typewriter.glPrint(16,748, "Now you're entering filenames.");
      typewriter.glPrint(600,584,"filename %i/%i",istate3,anitest.GetSize()-1);
      typewriter.glPrint(600,616, "WHEEL  <toggle filename>");
      //typewriter.glPrint(600,632, "F3     <change type>");
      typewriter.glPrint(600,632, "F6     <change loop #>");
      typewriter.glPrint(600,648, "RETURN <INPUT>");
      typewriter.glPrint(600,664, "alt-S  <SAVE>");

      if(anitest.Getpic(istate3)!=0)
      {
        PaintSpecimen(anitest.Getpic(istate3));
      }
      else
      {
        glColor3fv(rgfheader);
        typewriter.glPrint(370,620,"NO FILE");
      }

      break;
    case 2:  //choose anibox type  (uses istate4)
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528,"Animation file:");
      typewriter.glPrint(0,544,"%s",rgcloader.c_str());
      typewriter.glPrint(0,576,"Pick an animation type:");
      glColor3fv(rgfedit);
      switch(istate4)
      {
      case 0:
        typewriter.glPrint(32,592,"%i) standard",istate4);
        break;
      default:
        typewriter.glPrint(32,592,"%i) undefined",istate4);
        break;
      }
      glColor3fv(rgfadvice);
      typewriter.glPrint(600,600, "WHEEL <animation type>");
      typewriter.glPrint(16,732, "See manual.txt for type definitions.");
      break;
    case 3:   //pick # of images (uses istate3)
      glColor3fv(rgfheader);
      typewriter.glPrint(0,528,"Animation file:");
      typewriter.glPrint(0,544,"%s",rgcloader.c_str());
      typewriter.glPrint(0,576,"Pick an animation type:");
      switch(istate4)
      {
      case 0:
        typewriter.glPrint(32,592,"%i) standard",istate4);
        break;
      default:
        typewriter.glPrint(32,592,"%i) undefined",istate4);
        break;
      }
      glColor3fv(rgfedit);
      typewriter.glPrint(0,634,"How many jpg files?:");
      typewriter.glPrint(32,650,"%i",istate3);
      glColor3fv(rgfadvice);
      typewriter.glPrint(600,600, "WHEEL <number of jpg's>");
      break;
    default:
      glColor3f(1.0,0.0,0.0);
      typewriter.glPrint(384,384,"MESSED UP");
      typewriter.glPrint(0,576,"istate2:");
      typewriter.glPrint(0,592,"%i",istate2);
      break;
    }
    break;
///////////////////////////////////////////////istate == 19//////////////////////////////////////////////////////////
////////////////////////////////////////////change music///////////////////////////////////////////////////////
  case 19:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(fmap);
    drawmap(icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);

    glDisable(GL_BLEND);

    DrawBackDrop(ftrash);

    glEnable(GL_TEXTURE_2D);

    glColor3fv(rgfheader);
    typewriter.glPrint(150,528,"What song you want to play?: ");
    glColor3fv(rgfedit);
    typewriter.glPrint(700-16*(rgcloader.length()),544,rgcloader.c_str());
    typewriter.glPrint(700,544,".mid");

    glColor3fv(rgfadvice);
    typewriter.glPrint(600,648, "RETURN <INPUT>");
    typewriter.glPrint(600,664, "alt-S  <SAVE>");
    typewriter.glPrint(16,732,  "Play a midi.");

    glDisable(GL_TEXTURE_2D);
    drawhero();
    break;
  default:
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.0,1.0,1.0);
    typewriter.glPrint(512,384, "messed UP");
    typewriter.glPrint(512,400,"%i",istate);
    glDisable(GL_TEXTURE_2D);
    break;

  }//switch (istate)

  /////////////delete this////////////////////////////////
  /*int ix=0;
  glEnable(GL_TEXTURE_2D);
  picbox.Reset();
  while(picbox.End()==false)
  {
     typewriter.glPrint(0,ix,"%i",picbox.GetNum());
     typewriter.glPrint(50,ix,picbox.GetName().c_str());
     picbox.Next();
     ix+=16;
   }*/

     glEnable(GL_TEXTURE_2D);
     typewriter.glPrint(700,400,"hero.fhor==%f",hero.GetHor());
     typewriter.glPrint(700,416,"hero.fvert==%f",hero.GetVert());
     typewriter.glPrint(700,432,"fx==%f",fx);
     typewriter.glPrint(700,448,"fy==%f",fy);
////////////////////////////////////////////////////////////


  //drawfade(0==top left, 1==top right, 2==bottom right 3==bottom left)
  if(ifade>0)
  {
    switch(istate)
    {
    case 0:  //main menu
      if(hero.GetVert()>768*icemap.Get_Rows()-192&&hero.GetHor()<512)
        drawfade(2);
      else
        drawfade(3);
      break;
    case 8:  //block edit
      if(hero.GetVert()>768*icemap.Get_Rows()-192)
        drawfade(0);
      else
        drawfade(3);
      break;
    case 9:  //mouse edit
      if(hero.GetVert()>768*icemap.Get_Rows()-192)
        drawfade(0);
      else
        drawfade(3);
      break;
    case 10:
      if(hero.GetVert()>768*icemap.Get_Rows()-192)
        drawfade(0);
      else
        drawfade(3);
      break;
    case 11:
      break;
    case 12:
      break;
    case 13:
      if(hero.GetVert()>768*hackmap.Get_Rows()-192)
        drawfade(0);
      else
        drawfade(3);
      break;
    case 14:
      break;
    case 15:        //add gizmos
      if(hero.GetVert()>768*icemap.Get_Rows()-384&&hero.GetHor()<512)
        drawfade(2);
      else if(hero.GetVert()>768*icemap.Get_Rows()-384)
        drawfade(3);
      else if(hero.GetHor()<512)
        drawfade(1);
      else
        drawfade(0);
      break;
    case 16:
      drawfade(3);
      break;
    }
  }
  SDL_GL_SwapBuffers();
}

void EditBox::DrawBackDrop(float &ftrash)
{
  if(hero.GetVert()>768.0f*float(icemap.Get_Rows())-384.0f)
    ftrash=512.0f;
  else
    ftrash=0.0f;

  glDisable(GL_TEXTURE_2D);
  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_POLYGON);
    glVertex3f(0.0f,512.0f-ftrash,0.0f);
    glVertex3f(1024.0f,512.0f-ftrash,0.0f);
    glVertex3f(1024.0f,768.0f-ftrash,0.0f);
    glVertex3f(0.0f,768.0f-ftrash,0.0f);
  glEnd();
}

void EditBox::PaintSpecimen(int ipic)
{
  glPushMatrix();
  glTranslatef(400.0,540.0,0.0);

  glDisable(GL_TEXTURE_2D);
  glColor3f(1.0,1.0,1.0);

  glBegin(GL_POLYGON);
    glVertex3f(0,0,0.0);
    glVertex3f(192,0,0.0);
    glVertex3f(192,192,0.0);
    glVertex3f(0,192,0.0);
  glEnd();
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, ipic);
  glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);	glVertex3f(0,0,0.0);
    glTexCoord2f(1.0,0.0);	glVertex3f(192,0,0.0);
    glTexCoord2f(1.0,1.0);	glVertex3f(192,192,0.0);
    glTexCoord2f(0.0,1.0);	glVertex3f(0,192,0.0);
  glEnd();
  glPopMatrix();
}

void EditBox::PaintGizInfo(int iswitch)
{
  glColor3fv(rgfheader);
  typewriter.glPrint(0,528,"Gizmo file:");
  typewriter.glPrint(0,544,specimen.GetName().c_str());
  typewriter.glPrint(0,576,"Gizmo type:");
  typewriter.glPrint(0,624,"file:");
  switch(specimen.GetType())
  {
  case 0:
    typewriter.glPrint(32,592,"%i) player",specimen.GetType());
    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
    break;
  case 1:
    typewriter.glPrint(32,592,"%i) rat",specimen.GetType());
    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
    break;
  case 2:
    typewriter.glPrint(32,592,"%i) mill",specimen.GetType());
    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
    break;
  case 3:
    typewriter.glPrint(32,592,"%i) stain",specimen.GetType());
    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
    break;
  case 4:
    typewriter.glPrint(32,592,"%i) bug",specimen.GetType());
    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
    break;
  case 5:
    typewriter.glPrint(32,592,"%i) lightning bug",specimen.GetType());
    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
    break;
  case 6:
    typewriter.glPrint(32,592,"%i) dragon",specimen.GetType());
    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
    break;
  default:
    typewriter.glPrint(32,592,"%i) undefined",specimen.GetType());
    glColor3fv(rgfedit);
    typewriter.glPrint(160-16*(rgcloader.length()),640,rgcloader.c_str());
    break;
  }

  switch(iswitch)
  {
  case 0:
    typewriter.glPrint(160,640,".png");
    break;
  case 1:
    typewriter.glPrint(160,640,".wav");
    break;
  }
}
