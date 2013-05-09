#define BOOST_TEST_MODULE WindowTest
#include <boost\test\included\unit_test.hpp>
#include "2DMath.h"
#include "SDL_App.h"
#include "SDL_FpsCounter.h"
#include "TestTracker.h"
#include <iostream>
#include <memory>

#define DFpsCountTest

#ifdef DFpsCountTest

namespace FpsCountTest
{
	class CFpsCountTest : public SDL_App
	{
		Vector screenDim;
		FpsCounter fpsCounter;
		SDL_Surface* screen;
	public:
		~CFpsCountTest() {}
		bool Init() override 
		{
			screenDim = Vector( 600, 600 );
			if((screen = SDL_SetVideoMode( (int)screenDim.x, (int)screenDim.y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) 
			{
				return false;
			}
			fpsCounter.Init(std::string( "consola.ttf" ));
			return true;
		}

		void Logic() override
		{
			Sleep(250);
			fpsCounter.Logic();
		}

		void Render() override
		{
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			fpsCounter.Render( screen, 0, 0 );
			static int counter=0;
			if ( counter >= 8 )
			{
				BOOST_REQUIRE_EQUAL( fpsCounter.Count(), 4 );
				if ( counter >= 12 )
					Exit();
			}
			counter++;
			SDL_Flip(screen);
		}
	};

	CreateUnitTest( FpsCountTest, "Fps Counter Test" )
	{
		std::unique_ptr<SDL_App> a(new CFpsCountTest); a->Execute();
		std::cout << "Exitting!" << std::endl; std::cin.get();
	}
}
#endif




