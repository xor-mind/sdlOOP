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

	static Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
	{
		//Convert the pixels to 32 bit
		Uint32 *pixels = (Uint32 *)surface->pixels;

		//Get the requested pixel
		return pixels[ ( y * surface->w ) + x ];
	}

	static void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
	{
		//Convert the pixels to 32 bit
		Uint32 *pixels = (Uint32 *)surface->pixels;

		//Set the pixel
		pixels[ ( y * surface->w ) + x ] = pixel;
	}

	static SDL_Surface *flip_surface( SDL_Surface *surface, int flags )
	{
		//Pointer to the soon to be flipped surface
		SDL_Surface *flipped = NULL;

		//If the image is color keyed
		if( surface->flags & SDL_SRCCOLORKEY )
		{
			flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
		}
		//Otherwise
		else
		{
			flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
		}

		//If the surface must be locked
		if( SDL_MUSTLOCK( surface ) )
		{
			//Lock the surface
			SDL_LockSurface( surface );
		}

		//Go through columns
		for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- )
		{
			//Go through rows
			for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- )
			{
				//Get pixel
				Uint32 pixel = get_pixel32( surface, x, y );

				//Copy pixel
				//if( ( flags & FLIP_VERTICAL ) && ( flags & FLIP_HORIZONTAL ) )
				//{
				//	put_pixel32( flipped, rx, ry, pixel );
				//}
				//else if( flags & FLIP_HORIZONTAL )
				{
					put_pixel32( flipped, rx, y, pixel );
				}
				//else if( flags & FLIP_VERTICAL )
				//{
				//	put_pixel32( flipped, x, ry, pixel );
				//}
			}
		}

		//Unlock surface
		if( SDL_MUSTLOCK( surface ) )
		{
			SDL_UnlockSurface( surface );
		}

		//Copy color key
		if( surface->flags & SDL_SRCCOLORKEY )
		{
			SDL_SetColorKey( flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
		}

		//Return flipped surface
		return flipped;
	}

	void verticalLine(int y1,int y2,int x)
	{
        //for(int i=y1;i<=y2;i++)
        //        put_pixel32(x,i,255,255,255);
	}
	void horizontalLine(int x1,int x2,int y)
	{
			//for(int i=x1;i<=x2;i++)
			//		setPixel(i,y,255,255,255);
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