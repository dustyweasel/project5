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

#include "icegame.h"

void GameBox::draw()
{
std::fstream outfile;//delete this
  bool btemp=false;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  switch(istate)
  {
//////////////////////////////////////  istate==0  main menu  /////////////////////////////////////////////////////////
  case 0:
    glColor3f(1.0f,1.0f,1.0f);
    glBindTexture(GL_TEXTURE_2D, statbox[4]);  //stars
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPushMatrix();
    glTranslatef(0.0f,5.0f,0.0f);
    glRotatef(float(elticko)/2000.0f*2.0f,0.0f,1.0f,0.0f);
    glRotatef(90,1.0f,0.0f,0.0f);
    gluCylinder(quadratic,10.0,10.0,10.0,64,64);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, statbox[5]);  //planet
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //glColor3f(0.4f,1.0f,0.7f);
    glPushMatrix();
    glTranslatef(0.7,-0.4,-3.0);
    glRotatef(90,0.0, 1.0, 0.0);
    glRotatef(float(elticko)/2000.0f*5.0f,0.0, 1.0, 0.0);
    glRotatef(90,1.0, 0.0, 0.0);
    gluSphere(quadratic, 1.0, 60, 60);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, statbox[6]);  //sun
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPushMatrix();
    glRotatef(float(elticko)/2000.0f*-2.0f+30.0f,0.0, 1.0, 0.0);  glTranslatef(0.0f,0.0f,-5.0f);
    glRotatef(90,0.0, 1.0, 0.0);
    glRotatef(float(elticko)/2000.0f*5.0f,0.0, 1.0, 0.0);
    glRotatef(90,1.0, 0.0, 0.0);
    gluSphere(quadratic, 0.03125, 60, 60);
    glPopMatrix();

    glPushMatrix();
    mGui->draw();
    glPopMatrix();
    break;
//////////////////////////////////////              istate==1  main game     /////////////////////////////////////////////////////////
  case 1:
  case 4:
  case 11:
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0f, float(mWidth), float(mHeight), 0.0f, -1.0f, 1.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();



     glEnable(GL_TEXTURE_2D);
     glEnable(GL_BLEND);
     glColor3fv(nature.rgfmap);
     #ifdef PROGRAMMER
     if(istate==4)
     {
        glColor3f(0.8f,0.8f,0.8f);
        btemp=true;
     }
     #endif
     drawmap(*icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
     icemap->drawgiz(1,fx,fy,btemp,mWidth,mHeight,subWidth,subHeight);
     icemap->drawgiz(0,fx,fy,btemp,mWidth,mHeight,subWidth,subHeight);

     glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
     glEnable(GL_TEXTURE_2D);

     glPushMatrix();
     herotranslate();
     drawhero();
     glPopMatrix();
     glColor3fv(nature.rgfmap);
     icemap->drawstore();

     if(icemap->GetLayer(1)!=0)
        drawmap2(*icemap,fx,fy,float(mWidth),float(mHeight));
     //nature.Rain();

     glEnable(GL_TEXTURE_2D);
     glColor3f(1.0f,1.0f,1.0f);
     drawhearts();

     if(istate==11)
     {
       glColor3f(0.0f,1.0f,0.0f);
       typewriter.glPrint(440,384,"GAME OVER");
     }

//all garbage goes here plus two other spots, one in paintgiz and one in painthero
//undefine PROGRAMMER in switchmaster to compile a release version
     #ifdef PROGRAMMER
     #ifdef VAULTCHECK
     picbox->Reset();//imagereturn=picbox->imagehead;
     ix=0;
     while(picbox->End()==false)
     {
        typewriter.glPrint(ix/768*512,ix%768,"%i,%s",picbox->GetNum(),picbox->GetName().c_str());
        picbox->Next();
        ix+=16;
     }
     #else

     if(istate==4)
     {
        drawbombs(*icemap,fx,fy);
        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f,1.0f,0.0f,1.0f);
        typewriter.glPrint(0,212,"hero.GetSize()=%f", hero.GetSize());
        typewriter.glPrint(0,228,"hero.GetHor()=%f", hero.GetHor());
        typewriter.glPrint(0,244,"hero.GetVert()=%f", hero.GetVert());
        typewriter.glPrint(0,260,"hero.GetPic()=%i", hero.GetPic());
        typewriter.glPrint(0,276,"hero.GetState()=%i", hero.GetState());
        typewriter.glPrint(0,292,"fx=%f",fx);
        typewriter.glPrint(0,308,"fy=%f",fy);
        typewriter.glPrint(0,324,"istate=%i", istate);
        //typewriter.glPrint(0,308,"tester=%i", tester);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE);   //this does awesome ghost effect
        glDisable(GL_TEXTURE_2D);
        drawblocks(*icemap,fx,fy,mWidth,mHeight);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
     }
     #endif
     #endif
//glPopMatrix();

     break;
////////////////////////////////////// istate==2  cut scene   /////////////////////////////////////////////////////////
  case 2:
  /*   glEnable(GL_TEXTURE_2D);
     glEnable(GL_BLEND);
     glColor3f(1.0,1.0,1.0);
//terrible coding, fix later

//     if(cutscene[0].isize>0)
//     {
        glBindTexture(GL_TEXTURE_2D, cutscene[0].Getpic());
        glBegin(GL_POLYGON);
           glTexCoord2f(0.0,1.0);	glVertex3f(fx,768,0.0);
           glTexCoord2f(1.0,1.0);	glVertex3f(fx+1024,768,0.0);
           glTexCoord2f(1.0,0.0);	glVertex3f(fx+1024,0,0.0);
           glTexCoord2f(0.0,0.0);	glVertex3f(fx,0,0.0);
        glEnd();
//     }
     glPushMatrix();
     glTranslatef(1024,0,0);
//     if(cutscene[1].isize>0)
//     {
        glBindTexture(GL_TEXTURE_2D, cutscene[1].Getpic());
        glBegin(GL_POLYGON);
           glTexCoord2f(0.0,1.0);	glVertex3f(fx,768,0.0);
           glTexCoord2f(1.0,1.0);	glVertex3f(fx+1024,768,0.0);
           glTexCoord2f(1.0,0.0);	glVertex3f(fx+1024,0,0.0);
           glTexCoord2f(0.0,0.0);	glVertex3f(fx,0,0.0);
        glEnd();
//     }

     glPopMatrix();

     glColor3f(0.0,0.0,0.0);
     switch(istate2)
     {
     case 0:
        break;
     case 1:
        break;
     case 2:
        typewriter.glPrint(300, 400,"OUR 2nd DEMO");
        break;
     case 3:
        typewriter.glPrint(200, 400,"PROGRAMMING: ICECUBEFLOWER");
        break;
     case 4:
        typewriter.glPrint(200, 400,"PROGRAMMING: ICECUBEFLOWER");
        typewriter.glPrint(250, 416,"MUSIC: JAZZMINT6");
        break;
     case 5:
        typewriter.glPrint(200, 400,"PROGRAMMING: ICECUBEFLOWER");
        typewriter.glPrint(250, 416,"MUSIC: JAZZMINT6");
        typewriter.glPrint(150, 432,"EYE-BLEEDING ART: ICECUBEFLOWER");
        break;
     case 6:
        typewriter.glPrint(200, 400,"PROGRAMMING: ICECUBEFLOWER");
        typewriter.glPrint(250, 416,"MUSIC: JAZZMINT6");
        typewriter.glPrint(150, 432,"EYE-BLEEDING ART: ICECUBEFLOWER");
        typewriter.glPrint(100, 448,"ANNOYING SOUND EFFECTS: ICECUBEFLOWER");
        break;
     case 7:
        typewriter.glPrint(150, 400,"WE NEED AN ARTIST.  MORE INFO AT:");
        typewriter.glPrint(180, 416,"http://www.icecubeflower.com");
        break;
     }*/
     break;
//////////////////////////////////////  istate==4   got moved to istate==1   //////////////////////////////////////////////////////
//////////////////////////////////////  istate==5  scroll up   /////////////////////////////////////////////////////////
  case 5:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glColor3fv(nature.rgfmap);

    glPushMatrix();
    glTranslatef(0.0f,masterscroll,0.0f);
    drawmap(*lastmap,fx,0.0f,mWidth,mHeight,subWidth,subHeight);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f,-float(subHeight)+masterscroll,0.0f);
    drawmap(*icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
    herotranslate();
    drawhero();
    glPopMatrix();

    drawhearts();
    break;
//////////////////////////////////////  istate==7  scroll down ////////////////////////////////////////////////////////
  case 7:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glColor3fv(nature.rgfmap);

    glPushMatrix();
    glTranslatef(0.0f,-masterscroll,0.0f);
    drawmap(*lastmap,fx,float(lastmap->Get_Rows()*16-subHeight),mWidth,mHeight,subWidth,subHeight);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f,float(subHeight)-masterscroll,0.0f);
    drawmap(*icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
    herotranslate();
    drawhero();
    glPopMatrix();

    drawhearts();
    break;
//////////////////////////////////////  istate==6  scroll right  /////////////////////////////////////////////////////////
  case 6:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glColor3fv(nature.rgfmap);

    glPushMatrix();
    glTranslatef(-masterscroll,0.0f,0.0f);
    drawmap(*lastmap,float(lastmap->Get_Columns()*16-subWidth),fy,mWidth,mHeight,subWidth,subHeight);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(float(subWidth)-masterscroll,0.0f,0.0f);
    drawmap(*icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
    herotranslate();
    drawhero();
    glPopMatrix();

    drawhearts();
    break;
//////////////////////////////////////   istate == 8    scroll left  ///////////////////////////////////////////////////
  case 8:
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glColor3fv(nature.rgfmap);

    glPushMatrix();
    glTranslatef(masterscroll,0.0f,0.0f);
    drawmap(*lastmap,0.0f,fy,mWidth,mHeight,subWidth,subHeight);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-float(subWidth)+masterscroll,0.0f,0.0f);

    drawmap(*icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
    herotranslate();
    drawhero();
    glPopMatrix();

    drawhearts();
    break;
//////////////////////////////////////  istate==9   cartoon cave link    /////////////////////////////////////////////////////////
  case 9:
     //draw cartoon cave link
     glColor3fv(nature.rgfmap);
     drawmap(*icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
     glPushMatrix();
     herotranslate();
     drawhero();
     glDisable(GL_TEXTURE_2D);
     glColor3f(0.0,0.0,0.0);
     gluDisk(quadratic,dval,1300,25,1);
     glPopMatrix();
     glEnable(GL_TEXTURE_2D);
     break;
//////////////////////////////////////              istate == 10       /////////////////////////////////////////////////////////
  case 10:
     //draw cartoon cave link
     glEnable(GL_TEXTURE_2D);
     glEnable(GL_BLEND);
     glColor3fv(nature.rgfmap);
     drawmap(*icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
     glPushMatrix();
     herotranslate();
     drawhero();
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
     glColor3f(0.0,0.0,0.0);
     gluDisk(quadratic,dval,1300,25,1);
     glPopMatrix();
     break;
  case 12:
     glEnable(GL_TEXTURE_2D);
     glEnable(GL_BLEND);
     glColor3fv(nature.rgfmap);
     drawmap(*icemap,fx,fy,mWidth,mHeight,subWidth,subHeight);
     icemap->drawgiz(1,fx,fy,btemp,mWidth,mHeight,subWidth,subHeight);
     icemap->drawgiz(0,fx,fy,btemp,mWidth,mHeight,subWidth,subHeight);

     glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
     glEnable(GL_TEXTURE_2D);

     glPushMatrix();
     herotranslate();
     drawhero();
     glPopMatrix();
     glColor3fv(nature.rgfmap);
     icemap->drawstore();

     if(icemap->GetLayer(1)!=0)
        drawmap2(*icemap,fx,fy,mWidth,mHeight);
     //nature.Rain();

     glEnable(GL_TEXTURE_2D);
  glColor3f(1.0f,1.0f,0.0f);
     typewriter.glPrint(mWidth/5, 200,"AND THUSLY DID HERMAN SLAY");
   if(istate2>0)
     typewriter.glPrint(mWidth/5, 216,"THE DRAGON MOST FOUL");
   if(istate2>1)
     typewriter.glPrint(mWidth/5, 232,"AND RECOVERED HIS BOTTLE OF MAD DOG 20/20");
   if(istate2>2)
     typewriter.glPrint(mWidth/5, 280,"HE DRANKETH FROM HIS BOTTLE");
   if(istate2>3)
     typewriter.glPrint(mWidth/5, 296,"AND PEACE AND HAPPINESS RETURNED TO THE LAND");
   if(istate2>4)
     typewriter.glPrint(mWidth/5, 312,"OR AT LEAST IT FELT THAT WAY");
   if(istate2>6)
     typewriter.glPrint(mWidth/5, 344,"THE END");

     glColor3f(1.0f,1.0f,1.0f);
     drawhearts();

    break;
  default:
     glColor3f(1.0,0.0,0.0);
     typewriter.glPrint(500, 400,"messed up, istate=%i",istate);
     break;

  }

  SDL_GL_SwapBuffers();
}
