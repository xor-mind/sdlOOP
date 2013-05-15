// various rendering routines
#ifndef VIDEO_H
#define VIDEO_H

// ad_todo: move this file to my sdlOOP library
#include "SDL.h"
#include "Rectangle.h"

class SDL_Video
{
public:
	SDL_Surface* screen;
	SDL_Rect clipRect;
public:

	void setPixel(int x,int y,int r,int g,int b)
	{
		if( x >= 0 && x < screen->clip_rect.w && y >= 0 && y < screen->clip_rect.h )
                ((Uint32*)screen->pixels)[y*screen->pitch/4+x]=SDL_MapRGB(screen->format,r,g,b);
	}
	void verticalLine(int y1,int y2,int x)
	{
        for(int i=y1;i<=y2;i++)
                setPixel(x,i,255,255,255);
	}
	void horizontalLine(int x1,int x2,int y)
	{
			for(int i=x1;i<=x2;i++)
					setPixel(i,y,255,255,255);
	}
	void renderPerimiter(SDL_Rect* rec)
	{
        verticalLine(rec->y,rec->y+rec->h,rec->x);
        verticalLine(rec->y,rec->y+rec->h,rec->x+rec->w);
        horizontalLine(rec->x,rec->x+rec->w,rec->y);
        horizontalLine(rec->x,rec->x+rec->w,rec->y+rec->h);
	}
	void renderPerimiter(UsefulMath::Rectangle* rec)
	{
        verticalLine( rec->top, rec->bottom, rec->left );
        verticalLine( rec->top, rec->bottom, rec->right );
        horizontalLine( rec->left, rec->right, rec->top );
        horizontalLine(rec->left, rec->right, rec->bottom );
	}
};
#endif