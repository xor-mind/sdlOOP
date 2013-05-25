#ifndef SPRITE_H
#define SPRITE_H

#include "SDL_Surface.h"

class Sprite
{
public:
	Surfaces surfaces;

	uint currentFrame;
	uint delayTime;
	uint startTime;

	bool isBlinking;
	uint blinkingDelay, blinkingStartTime;

public:

	Sprite() : currentFrame( 0 ), blinkingDelay(0), isBlinking( false ) 
	{
		startTime = blinkingStartTime = SDL_GetTicks();
	}
	~Sprite() 
	{
		for ( SDL_Surface* s : surfaces )
			SDL_FreeSurface( s );
	}

	void Update()
	{
		if ( blinkingDelay )
		{
			if ( SDL_GetTicks() - blinkingStartTime > blinkingDelay )
			{
				isBlinking = !isBlinking;
				blinkingStartTime = SDL_GetTicks();
			}
		}

		if ( surfaces.size() > 1) 
			if ( SDL_GetTicks() - startTime >= delayTime ) 
			{
				currentFrame++;
				if ( currentFrame == surfaces.size() )
					currentFrame = 0;
				startTime = SDL_GetTicks();
			}
	}

	void Render( SDL_Surface* dest, int x, int y )
	{
		if ( !isBlinking )
		{
			Surface::OnDraw( dest, surfaces[currentFrame], x, y );
		}
	}

	int Width()  { return surfaces[currentFrame]->w; }
	int Height() { return surfaces[currentFrame]->h; }
};

#endif