#ifndef SDL_FPSCOUNTER_H
#define SDL_FPSCOUNTER_H

#include "SDL_Text.h"
#include "types.h"
#include <string>

class FpsCounter
{
private:
	Text text;
	uint fpsTime1, fpsTime2, fpsCounter, fpsDisplay;
public:
	void Init( std::string& fontName ) 
	{
		fpsCounter = fpsDisplay = 0;

		text.Init();
		SDL_Color c = { 255,255,255 };
		text.SetColor(c);
		text.OpenFont( fontName, 14 );	

		fpsTime1  = SDL_GetTicks();
	}
	void Logic()
	{
		/* calculate time since last update */
		fpsTime2 =  SDL_GetTicks();


		if ( fpsTime2 - fpsTime1 >= 1000 ) 
		{
			fpsTime1 = fpsTime2; 
			fpsDisplay = fpsCounter;
			fpsCounter = 0;
		}
	}
	void Render( SDL_Surface* screen, int x, int y )
	{
		fpsCounter++;
		//if ( fpsTime2 != fpsTime1 )
		{
			std::string s = "fps: " + std::to_string( fpsDisplay ); //(float)fpsCounter/(float)(fpsTime2 - fpsTime1) * (1000.0f-(float)(fpsTime2 - fpsTime1)) );
			text.CreateSolid(s);
			text.Render(screen, 0, 0);
		}
	}
	uint Count() const { return fpsDisplay; }
};

#endif