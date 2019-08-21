#include "fpsbutton.hpp"

//int FPSButton::mInstances = 0;
//Mix_Chunk* FPSButton::mHoverSound = NULL;

FPSButton::FPSButton(const std::string& caption, AudioBox &soundbox) : Button(caption), mHasMouse(false)
{
  setFrameSize(0);
  boombox=&soundbox;
  
	/*if (mInstances == 0)
	{		
		mHoverSound = Mix_LoadWAV("sound/sound5.wav");
		Mix_VolumeChunk(mHoverSound, 60);
	}
	
	++mInstances;*/
}

FPSButton::~FPSButton()
{
	//--mInstances;

	/*if (mInstances == 0)
	{
		Mix_FreeChunk(mHoverSound);
	}*/
}

void FPSButton::draw(gcn::Graphics* graphics)
{
  if(mHasMouse)
  {
    graphics->setFont(mHighLightFont);
    graphics->drawText(getCaption(),0,0);
  }
  else
  {
    graphics->setFont(getFont());
    graphics->drawText(getCaption(),0,0);
  }
}

void FPSButton::setHighLightFont(gcn::Font* font)
{
  mHighLightFont = font;
}

void FPSButton::mouseEntered(gcn::MouseEvent& mouseEvent)
{
  Button::mouseEntered(mouseEvent);
  if(boombox!=NULL)
    boombox->Playsound("Flame_Whoosh_02.ogg",MIX_MAX_VOLUME/4);
  mHasMouse = true;
}

void FPSButton::mouseExited(gcn::MouseEvent& mouseEvent)
{
    Button::mouseExited(mouseEvent);
	mHasMouse = false;
}
