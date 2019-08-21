#include "icegame.h"

ResolutionListModel::ResolutionListModel()
{
  // Get available fullscreen/hardware modes
  modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
  isize=0;
  while(modes[isize])
    isize+=1;
}

int ResolutionListModel::getNumberOfElements()
{
  return isize;
}

std::string ResolutionListModel::getElementAt(int i)
{
  //more than likely this is a really dumb way to do this but I don't care right now
  if(i<isize)
  {
    converter.str("");
    converter<<modes[i]->w;
    translation=converter.str();
    translation+="x";
    converter.str("");
    converter<<modes[i]->h;
    translation+=converter.str();

    return translation;
  }
  else
  {
    return std::string("");
  }
}

void GameBox::initGui()
{
  mOpenGLGraphics = new gcn::OpenGLGraphics();
  mOpenGLGraphics->setTargetPlane(mWidth, mHeight);
  mOpenGLImageLoader = new gcn::OpenGLSDLImageLoader();
  gcn::Image::setImageLoader(mOpenGLImageLoader);

  mSDLInput = new gcn::SDLInput();
//try/catch?  YES
  mFont = new gcn::ImageFont(Pathfinder::Image_Path+"techyfontbig2.png"," abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
  mHighLightFont = new gcn::ImageFont(Pathfinder::Image_Path+"techyfontbighighlight.png",
                   " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
  mWhiteFont = new gcn::ImageFont(Pathfinder::Image_Path+"techyfontwhite.png"," abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%@`'*#=[]\"");
  gcn::Widget::setGlobalFont(mWhiteFont);  //what is this line?

  mTop = new gcn::Container();
  mTop->setOpaque(false);
  mMain = new gcn::Container();
  mMain->setOpaque(false);
  mTop->add(mMain);

  mSingleplayButton = new FPSButton("PLAY DEMO 2.5",boombox);
  mOptionsButton = new FPSButton("OPTIONS",boombox);
  mAboutButton = new FPSButton("ABOUT",boombox);
  mQuitButton = new FPSButton("QUIT",boombox);

  mSingleplayButton->setHighLightFont(mHighLightFont);
  mSingleplayButton->adjustSize();
  mSingleplayButton->setActionEventId("play");
  mSingleplayButton->addActionListener(this);
  mSingleplayButton->setFont(mFont);
  mSingleplayButton->adjustSize();
  mMain->add(mSingleplayButton);/////////////
  mOptionsButton->setHighLightFont(mHighLightFont);
  mOptionsButton->adjustSize();
  mOptionsButton->setActionEventId("options");
  mOptionsButton->addActionListener(this);
  mOptionsButton->setFont(mFont);
  mOptionsButton->adjustSize();
  mMain->add(mOptionsButton);////////////
  mAboutButton->setHighLightFont(mHighLightFont);
  mAboutButton->adjustSize();
  mAboutButton->setActionEventId("about");
  mAboutButton->addActionListener(this);
  mAboutButton->setFont(mFont);
  mAboutButton->adjustSize();
  mMain->add(mAboutButton);/////////////
  mQuitButton->setHighLightFont(mHighLightFont);
  mQuitButton->adjustSize();
  mQuitButton->setActionEventId("quit");
  mQuitButton->addActionListener(this);
  mQuitButton->setFont(mFont);
  mQuitButton->adjustSize();
  mMain->add(mQuitButton);

	mWebLabel = new gcn::Label("www.icecubeflower.com");
	mWebLabel->setFont(mWhiteFont);
	mWebLabel->adjustSize();
	mMain->add(mWebLabel);

  //gcn::OpenGLImage* image;  //wtf?

  mBoxImage = gcn::Image::load("Data/Images/box.png");

  mGui = new gcn::Gui();
  mGui->setGraphics(mOpenGLGraphics);
  mGui->setInput(mSDLInput);

  mGui->setTop(mTop);

  initOptions();
  initAbout();

  mTop->setDimension(gcn::Rectangle(0, 0, mWidth, mHeight));
  mMain->setDimension(gcn::Rectangle(0, 0, mWidth, mHeight));
  mOptions->setDimension(gcn::Rectangle(0, 0, mWidth, mHeight));
  mAbout->setDimension(gcn::Rectangle(0, 0, mWidth, mHeight));

  mSingleplayButton->setPosition(mWidth/8, mHeight/8);
  mOptionsButton->setPosition(mWidth/8, mHeight/8+40);
  mAboutButton->setPosition(mWidth/8, mHeight/8+80);
  mQuitButton->setPosition(mWidth/8, mHeight/8 +120);
  mOptionsBoxIcon->setPosition(mWidth/2 - 300, mHeight/2 - 150);
  mAboutBoxIcon->setPosition(mWidth/2 - 300, mHeight/2 - 150);
  mOptionsLabel->setPosition(mWidth/2 + 150, mHeight/2 - 145);
  mAboutLabel->setPosition(mWidth/2 + 150, mHeight/2 - 145);
  mFullScreen->setPosition(mWidth/2 - 200, mHeight/2 -100);
  mResolution->setPosition(mWidth/2 - 90, mHeight/2 -70);
  mResolutionLabel->setPosition(mWidth/2 -200, mHeight/2-70);
  mOptionsBackButton->setPosition(mWidth/2 - 290, mHeight/2 + 180);
  mAboutBackButton->setPosition(mWidth/2 - 290, mHeight/2 + 180);

  mAboutText->setPosition(mWidth/2 - 285, mHeight/2 - 120);

  mWebLabel->setPosition(30, mHeight-30);
}

void GameBox::cleanGui()
{
  cleanOptions();
  cleanAbout();

  delete mSDLInput;

  delete mFont;
  delete mHighLightFont;

  delete mGui;
  delete mOpenGLGraphics;
  delete mOpenGLImageLoader;

  delete mTop;
  delete mMain;
  delete mSingleplayButton;
  delete mOptionsButton;
  delete mAboutButton;
  delete mQuitButton;

  delete mBoxImage;
  delete mWhiteFont;

  delete mWebLabel;
}

void GameBox::action(const gcn::ActionEvent& actionEvent)
{
  std::ifstream infile;
  std::string rgcfilename;

  if(actionEvent.getId()=="play")
  {
    mMain->setVisible(false);

    infile.open("Data/Save1/save1.sav");

    infile>>rgcfilename;
    infile>>rgcfilename;

    icemap->Loadmap(rgcfilename, false,picbox);
    if(icemap->Get_Columns()*16<mWidth)
      subWidth=icemap->Get_Columns()*16;
    else
      subWidth=mWidth;
    if(icemap->Get_Rows()*16<mHeight)
      subHeight=icemap->Get_Rows()*16;
    else
      subHeight=mHeight;

    //icemap->Music(boombox);
    infile>>rgcfilename;

    infile.close();   //the mapname is stored in rgcfilename so reopen it later

    //open the gizmo file
    hero.Gizgen(rgcfilename,1024.0f,1024.0f,picbox);
    setfx();
    setfy();

    dval=5;
    istate=10;
    elticko=SDL_GetTicks();

    boombox.Playsound("button.wav");
  }
  else if (actionEvent.getId()=="options")
  {
    boombox.Playsound("button.wav");
    //Mix_PlayChannel(-1, mChooseSound, 0);
    mMain->setVisible(false);
    mOptions->setVisible(true);
  }
  else if(actionEvent.getId()=="fullscreen")
  {
    boombox.Playsound("button.wav");
    AlterVideo();
  }
  else if (actionEvent.getId() == "resolution")
  {
    boombox.Playsound("button.wav");
    AlterVideo();
  }
  else if (actionEvent.getId() == "back")
  {
    boombox.Playsound("button.wav");
    mMain->setVisible(true);
    mAbout->setVisible(false);
    //mMultiplay->setVisible(false);
    mOptions->setVisible(false);
  }
  else if (actionEvent.getId() == "about")
  {
    boombox.Playsound("button.wav");
    mMain->setVisible(false);
    mAbout->setVisible(true);
  }
  else if (actionEvent.getId() == "quit")
  {
    boombox.Playsound("button.wav");
    done=1;
  }
}

/////////////////////////////options menu///////////////////////////////////////////////////////
void GameBox::initOptions()
{
  int ix;

	mOptions = new gcn::Container();
	mOptions->setVisible(false);
	mOptions->setOpaque(false);
	mTop->add(mOptions);

	mOptionsBoxIcon = new gcn::Icon(mBoxImage);
	mOptions->add(mOptionsBoxIcon);

	mOptionsLabel = new gcn::Label("OPTIONS");
	mOptionsLabel->setFont(mWhiteFont);
	mOptionsLabel->adjustSize();
	mOptions->add(mOptionsLabel);

	mFullScreen = new FPSCheckBox("Fullscreen");
	mFullScreen->setFont(mWhiteFont);
	mFullScreen->adjustSize();
	mFullScreen->setBackgroundColor(0x01172e);
	mFullScreen->setForegroundColor(0xffffff);
	mFullScreen->setBaseColor(0x01172e);
	mFullScreen->setActionEventId("fullscreen");
	mFullScreen->addActionListener(this);
	mFullScreen->setSelected(mHaveFullscreen);
	mOptions->add(mFullScreen);

	mResolutionScrollArea = new gcn::ScrollArea();
	mResolutionScrollArea->setBackgroundColor(0x001172e);
	mResolutionScrollArea->setForegroundColor(0x01172e);
	mResolutionScrollArea->setBaseColor(0x01172e);

	mResolutionListBox = new gcn::ListBox();
	mResolutionListBox->setBackgroundColor(0x01172e);
	mResolutionListBox->setForegroundColor(0x01172e);
	mResolutionListBox->setBaseColor(0x022f55);
	mResolutionListBox->setSelectionColor(0x1222c);

	mResolutionListModel = new ResolutionListModel();
	mResolution = new gcn::DropDown(mResolutionListModel,mResolutionScrollArea,mResolutionListBox);
	mResolution->setWidth(200);
	mResolution->setBackgroundColor(0x022f55);
	mResolution->setForegroundColor(0x022f55);
	mResolution->setBaseColor(0x01172e);
	mResolution->setSelectionColor(0x022f55);

        ix=0;
        while(ix<mResolutionListModel->getNumberOfElements())
        {
          if(mResolutionListModel->modes[ix]->w==mWidth&&mResolutionListModel->modes[ix]->h==mHeight)
          {
            mResolution->setSelected(ix);
            ix=mResolutionListModel->getNumberOfElements();
          }
          ix+=1;
        }

	mResolution->setActionEventId("resolution");
	mResolution->addActionListener(this);
	mOptions->add(mResolution);

	mResolutionLabel = new gcn::Label("Resolution");
	mOptions->add(mResolutionLabel);

	mOptionsBackButton = new FPSButton("Back",boombox);
	mOptionsBackButton->setHighLightFont(mHighLightFont);
	mOptionsBackButton->adjustSize();
	mOptionsBackButton->setActionEventId("back");
	mOptionsBackButton->addActionListener(this);
	mOptionsBackButton->setFont(mFont);
	mOptionsBackButton->adjustSize();
	mOptions->add(mOptionsBackButton);
}

void GameBox::cleanOptions()
{
	delete mOptionsBoxIcon;
	delete mOptionsBackButton;
	delete mResolutionLabel;
//	delete mVolumeLabel;
//	delete mVolumePercent;
//	delete mVolume;
	delete mResolutionListBox;
	delete mResolutionScrollArea;
	delete mResolutionListModel;
	delete mResolution;
	delete mFullScreen;
	delete mOptionsLabel;
	delete mOptions;
}

void GameBox::initAbout()
{
  mAbout = new gcn::Container();
  mAbout->setVisible(false);
  mAbout->setOpaque(false);
  mTop->add(mAbout);

  mAboutBoxIcon = new gcn::Icon(mBoxImage);
  mAbout->add(mAboutBoxIcon);

  mAboutLabel = new gcn::Label("ABOUT");
  mAboutLabel->setFont(mWhiteFont);
  mAboutLabel->adjustSize();
  mAbout->add(mAboutLabel);

  mAboutText = new gcn::TextBox("ESC - takes you back to this menu.\n"
                                "ARROW KEYS - run around\n"
                                "L-CTRL - run/walk\n"
                                "L-ALT - attack\n"
                                "+/- NUMPAD - cheat, grow, shrink, walk through walls\n\n"
                                "Thanks to GUICHAN http://guichan.sourceforge.net\n\n"
                                "PROGRAMMING: icecubeflower\n"
                                "ART: icecubeflower / stolen from internet\n"
                                "MUSIC: JazzMint6\n\n"
                                "Coming Soon: 3D characters, weather effects, and more.\n"
                                "Are you a 2D/3D artist?  EMAIL: icecubeflower@yahoo.com");
  mAboutText->setFont(mWhiteFont);
  mAboutText->setOpaque(false);
  mAboutText->setEditable(false);
  mAboutText->setFrameSize(0);
  mAbout->add(mAboutText);

  mAboutBackButton = new FPSButton("Back",boombox);
  mAboutBackButton->setHighLightFont(mHighLightFont);
  mAboutBackButton->adjustSize();
  mAboutBackButton->setActionEventId("back");
  mAboutBackButton->addActionListener(this);
  mAboutBackButton->setFont(mFont);
  mAboutBackButton->adjustSize();

  mAbout->add(mAboutBackButton);
}

void GameBox::cleanAbout()
{
  delete mAboutBoxIcon;
  delete mAboutText;
  delete mAboutLabel;
  delete mAbout;
}

void GameBox::AlterVideo()
{
  if(mResolutionListModel->modes[mResolution->getSelected()]->w!=mWidth||mResolutionListModel->modes[mResolution->getSelected()]->h!=mHeight)
  {
    mWidth = mResolutionListModel->modes[mResolution->getSelected()]->w;
    mHeight = mResolutionListModel->modes[mResolution->getSelected()]->h;
    mResolutionChange = true;
  }

  if (mFullScreen->isSelected())
  {
    mHaveFullscreen = true;
    screen = SDL_SetVideoMode(mWidth, mHeight, BPP, SDL_OPENGL|SDL_FULLSCREEN);
  }
  else
  {
    mHaveFullscreen = false;
    screen = SDL_SetVideoMode(mWidth,mHeight, BPP, SDL_OPENGL);
  }
  reshape();
  mOpenGLGraphics->setTargetPlane(mWidth, mHeight);
}
