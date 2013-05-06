#ifndef SDL_TEXT_H
#define SDL_TEXT_H

#include "SDL_ttf.h"
#include "SDL_surface.h"
#include <iostream>

class Text
{
	SDL_Surface* text_solid ;
	SDL_Surface* text_shaded ;
	SDL_Surface* text_blended ;
	SDL_Surface* kerning_on ;
	SDL_Surface* outline_width ;
	SDL_Surface* surface;
	TTF_Font* font;
	bool kerning;
	SDL_Color c;
public:
	Text() 
	{
		surface = nullptr;
		text_solid = text_shaded = text_blended = 
			kerning_on = outline_width = NULL;
		kerning = true;
		font = NULL;
	}
	~Text() 
	{
		if ( surface != nullptr )
			SDL_FreeSurface( surface );
	}

	bool Init()
	{
		if (TTF_Init() < 0) {
			std::cerr << "Error: Unable to initialize SDL_ttf" << std::endl;
			return false;
		}

		//text_solid = TTF_RenderText_Solid(font, text.c_str(), red);
		//text_shaded = TTF_RenderText_Shaded(font, text.c_str(), red, blue);
		//text_blended = TTF_RenderText_Blended(font, text.c_str(), red);
		return true;
	}
	bool OpenFont(std::string fontName, int pointSize)
	{
		if (!(font = TTF_OpenFont(fontName.c_str(), pointSize)) ) {
			std::cerr << "Error: Unable to open font" << std::endl;
			return false;
		}
		return true;
	}
	void SetColor(SDL_Color& c)
	{
		this->c = c;
	}
	SDL_Surface* CreateSolid(std::string& s)
	{
		if ( surface != nullptr )
			SDL_FreeSurface( surface );
		return surface = TTF_RenderText_Solid(font, s.c_str(), c);
	}
	void Render(SDL_Surface* s, int x, int y)
	{
		Surface::OnDraw(s, surface, x, y );
	}
	void SetKerning(bool s)
	{
		(s == true) ? TTF_SetFontKerning(font, 1) : TTF_SetFontKerning(font, 0);
	}
	const std::pair<int,int>& TextSize(std::string& s)
	{
		std::pair<int,int> p;
		TTF_SizeText(font, s.c_str(), &p.first, &p.second);
		return p;
	}
};

#endif