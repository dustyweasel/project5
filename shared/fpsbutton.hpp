#ifndef __fpsbutton_hpp__
#define __fpsbutton_hpp__

#include <guichan.hpp>
#include <string>
//#include <SDL/SDL.h>
//#include <SDL/SDL_mixer.h>
#include "soundmaster.h"

class FPSButton : public gcn::Button
{
public:
	FPSButton(const std::string& caption, AudioBox &soundbox);
	~FPSButton();

	void setHighLightFont(gcn::Font* font);

	void draw(gcn::Graphics* graphics);
	void mouseEntered(gcn::MouseEvent& mouseEvent);
	void mouseExited(gcn::MouseEvent& mouseEvent);

private:
	gcn::Font* mHighLightFont;
	bool mHasMouse;
        AudioBox *boombox;
	//static Mix_Chunk* mHoverSound;
	// Keep track of instances to be able to free the sound
	//static int mInstances;
};

#endif
