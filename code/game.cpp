#include "game.h"
#include "lib.h"
#include <iostream>

void game::takeInput()
{
    while(SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            userInput.Type = input::QUIT;
            quit = true;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || (event.type == SDL_KEYDOWN &&
		(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && event.key.repeat == 0) )
        {
            userInput.Type = input::PLAY;
        }
		else if  (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0 )
		{
			userInput.Type = input::PAUSE;
		}
		else if ( event.type==SDL_MOUSEBUTTONUP && checkclickpause_resume()==true && isMenu)
        {
            userInput.Type=input::CLICK_PAUSE;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && checkclick_quit()==true && !isMenu && !isLevel && !isMusic)
        {
            userInput.Type = input::CLICK_QUIT;
            quit=true;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && checkclick_level()==true && !isMenu && !isLevel )
        {
            userInput.Type=input::CLICK_LEVEL;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && checkclick_back()==true && (isLevel || isMusic || isHelp) )
        {
            userInput.Type=input::CLICK_BACK;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && checkclick_level_normal()==true && isLevel && !isMenu)
        {
            userInput.Type=input::CLICK_NORMAL;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && checkclick_level_hard()==true && isLevel && !isMenu )
        {
            userInput.Type=input::CLICK_HARD;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && checkclick_music_button()==true && !isMenu && !isMusic)
        {
            userInput.Type=input::CLICK_MUSIC;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && check_music_pressStart()==true && !isMenu && isMusic)
        {
            userInput.Type=input::CLICK_PRESS_START;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && check_music_saveMe()==true && !isMenu && isMusic)
        {
            userInput.Type=input::CLICK_SAVE_ME;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && check_music_windFall()==true && !isMenu && isMusic )
        {
            userInput.Type=input::CLICK_WIND_FALL;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && check_music_foreverBound()==true && !isMenu && isMusic )
        {
            userInput.Type=input::CLICK_FOREVER_BOUND;
        }
        else if (event.type==SDL_MOUSEBUTTONUP && check_help_button()==true && !isMenu && !isHelp)
        {
            userInput.Type=input::CLICK_HELP;
        }

    }
}

game::game()
{
    initGraphic();
    pipe.init();
    sound.init();
    enemy.init();
    land.init();
    rocket.init();
    laser.init();
}

game::~game()
{
    shiba.Free();
    pipe.Free();
    land.Free();
    sound.Free();
    enemy.Free();
    rocket.Free();
    laser.Free();
    free();
    releaseGraphic();
}

void game::releaseGraphic()
{
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool game::initGraphic()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Flappy Doge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void game::display()
{
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
}

void game::renderScoreSmall()
{
	string s = to_string(score);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len - 1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("largeScore/1.png", scaleNumberS-0.05);
		}
		else if (number == 2)
		{
			image.Load("largeScore/2.png", scaleNumberS-0.05);
		}
		else if (number == 3)
		{
			image.Load("largeScore/3.png", scaleNumberS-0.05);
		}
		else if (number == 4)
		{
			image.Load("largeScore/4.png", scaleNumberS-0.05);
		}
		else if (number == 5)
		{
			image.Load("largeScore/5.png", scaleNumberS-0.05);
		}
		else if (number == 6)
		{
			image.Load("largeScore/6.png", scaleNumberS-0.05);
		}
		else if (number == 7)
		{
			image.Load("largeScore/7.png", scaleNumberS-0.05);
		}
		else if (number == 8)
		{
			image.Load("largeScore/8.png", scaleNumberS-0.05);
		}
		else if (number == 9)
		{
			image.Load("largeScore/9.png", scaleNumberS-0.05);
		}
		else
		{
			image.Load("largeScore/0.png", scaleNumberS-0.05);
		}
		image.Render(327 - image.getWidth() * (len - i - 1)*0.95, 264);
	}
	image.free();
}

void game::renderScoreLarge()
{
    string s = to_string(score);
	signed char len = s.length();
	LTexture image;

	for (signed char i = 0; i < len; i++)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("largeScore/1.png", 1);
		}
		else if (number == 2)
		{
			image.Load("largeScore/2.png", 1);
		}
		else if (number == 3)
		{
			image.Load("largeScore/3.png", 1);
		}
		else if (number == 4)
		{
			image.Load("largeScore/4.png", 1);
		}
		else if (number == 5)
		{
			image.Load("largeScore/5.png", 1);
		}
		else if (number == 6)
		{
			image.Load("largeScore/6.png", 1);
		}
		else if (number == 7)
		{
			image.Load("largeScore/7.png", 1);
		}
		else if (number == 8)
		{
			image.Load("largeScore/8.png", 1);
		}
		else if (number == 9)
		{
			image.Load("largeScore/9.png", 1);
		}
		else
		{
			image.Load("largeScore/0.png", 1);
		}
		image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 100);
	}
	image.free();
}

void game::renderBestScore()
{
	ifstream fileIn("bestScore/bestScore.txt");
	fileIn >> bestScore;
	ofstream fileOut("bestScore/bestScore.txt", ios::trunc);

	if (score > bestScore)
	{
		bestScore = score;
	}
	string s = to_string(bestScore);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len-1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("largeScore/1.png", scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load("largeScore/2.png", scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load("largeScore/3.png", scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load("largeScore/4.png", scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load("largeScore/5.png", scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load("largeScore/6.png", scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load("largeScore/7.png", scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load("largeScore/8.png", scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load("largeScore/9.png", scaleNumberS);
		}
		else
		{
			image.Load("largeScore/0.png", scaleNumberS);
		}
		image.Render(327 - image.getWidth()*(len-i-1)*0.95, 315);
	}
	image.free();

	fileOut << bestScore;
	fileIn.close();
	fileOut.close();
}

void game :: render_BestScore_Hard()
{
    ifstream fileIn("bestScore/best_Score_Hard.txt");
	fileIn >> best_Score_Hard;
	ofstream fileOut("bestScore/best_Score_Hard.txt", ios::trunc);

	if (score > best_Score_Hard)
	{
		best_Score_Hard = score;
	}
	string s = to_string(best_Score_Hard);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len-1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("largeScore/1.png", scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load("largeScore/2.png", scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load("largeScore/3.png", scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load("largeScore/4.png", scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load("largeScore/5.png", scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load("largeScore/6.png", scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load("largeScore/7.png", scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load("largeScore/8.png", scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load("largeScore/9.png", scaleNumberS);
		}
		else
		{
			image.Load("largeScore/0.png", scaleNumberS);
		}
		image.Render(327 - image.getWidth()*(len-i-1)*0.95, 315);
	}
	image.free();

	fileOut << best_Score_Hard;
	fileIn.close();
	fileOut.close();
}

void game::renderMessage()
{
	LTexture image;
	image.Load("image/message.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
	image.free();
}

void game::renderBackground()
{
	LTexture image;
	image.Load("image/background.jpg", 1);
	image.Render(0, 0);
	image.free();
}

void game::renderBackgroundNight()
{
	LTexture image;
	image.Load("image/background-night.jpg", 1);
	image.Render(0, 0);
	image.free();
}

//void game::renderLand()
//{
//	LTexture image;
//	image.Load("image/land.png", 1);
//	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, SCREEN_HEIGHT- image.getHeight());
//	image.free();
//}

void game::resume()
{
	LTexture image;
	image.Load("image/resume.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void game::pause()
{
	LTexture image;
	image.Load("image/pause.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

bool game::checkclickpause_resume()
{
    if(isMenu)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if ((x > SCREEN_WIDTH - 50 && x < SCREEN_WIDTH - 50+26)  && (y >20 && y < 20+28))
        {
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}
void game::renderPauseTab()
{
	LTexture image;
	image.Load("image/pauseTab.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 230);
	image.free();
}

void game::lightTheme()
{
	LTexture image;
	image.Load("image/shiba.png", 0.8);
	image.Render(173, 315);
	image.free();
}

void game::darkTheme()
{
	LTexture image;
	image.Load("image/shiba-dark.png", 0.8);
	image.Render(173, 315);
	image.free();
}

void game::nextButton()
{
	LTexture image;
	image.Load("image/nextRight.png", 1);
	image.Render(214, 322);
	image.Load("image/nextLeft.png", 1);
	image.Render(160, 322);
	image.free();
}

bool game::changeTheme()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (((x > 214 && x < 214+13)  || (x > 160 && x < 160 + 13)) && (y > 322 && y < 322 + 16))
	{
		return true;
	}
	return false;
}

void game::renderGameOver()
{
	LTexture image;
	image.Load("image/gameOver.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150);
	image.free();
}

void game::renderMedal()
{
        LTexture image;

        if (score > 20 && score <= 50)
        {
            image.Load("medal/silver.png", scaleNumberS);
        }
        else if (score > 50)
        {
            image.Load("medal/gold.png", scaleNumberS);
        }
        else
        {
            image.Load("medal/honor.png", scaleNumberS);
        }
        image.Render(157, 270);

        image.free();


}

void game::replay()
{
    if(!checkReplay())
    {
        LTexture image;
        image.Load("image/replay.png", 1);
        image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 400);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/replay.png", 1.2);
        image.Render((SCREEN_WIDTH - image.getWidth()) / 2-3, 400-4);
        image.free();
    }

}

bool game::checkReplay()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 100) / 2 && y > 400 && y < 400 + 60)
	{
		return true;
	}
	return false;
}

void game::Restart()
{
    die = false;
    score = 0;
    shiba.resetTime();
}

void game::renderquit()
{
    if(!checkclick_quit())
    {
        LTexture image;
        image.Load("image/quit_button.png",1);
        image.Render(15,530);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/quit_button.png",1.2);
        image.Render(15-5,530-5);
        image.free();
    }

}

bool game::checkclick_quit()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 15 && x < 125 && y > 530 && y < 600)
	{
		return true;
	}
	return false;
}

void game :: renderLevel()
{
    if(!checkclick_level())
    {
        LTexture image;
        image.Load("image/level_button.png",1);
        image.Render(190,530);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/level_button.png",1.2);
        image.Render(190-5,530-5);
        image.free();
    }
}

bool game :: checkclick_level()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 190 && x < 300 && y > 530 && y < 600)
	{
		return true;
	}
	return false;
}

void game :: render_back_ground_level()
{
    LTexture image;
	image.Load("image/space_back_ground.png", 1);
	image.Render(0, 0);
	image.free();
}

void game :: renderBack()
{

        if(!checkclick_back())
        {
            LTexture image;
            image.Load2("image/back.png", 0.6);
            image.Render(20, 20);
            image.free();
        }
        else
        {
            LTexture image;
            image.Load2("image/back.png", 0.8);
            image.Render(20-5, 20-5);
            image.free();
        }

}

bool game :: checkclick_back()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 20 && x < 120 && y > 20 && y < 98)
	{
		return true;
	}
	return false;
}

void game :: render_level_normal()
{
    if(!checkclick_level_normal())
    {
        LTexture image;
        image.Load("image/level_normal.png", 1);
        image.Render( (SCREEN_WIDTH-image.getWidth())/2, 100);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/level_normal.png", 1.2);
        image.Render((SCREEN_WIDTH-image.getWidth())/2-10, 100-10);
        image.free();
    }
}

bool game :: checkclick_level_normal()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 125 && x < 125 + 250 && y > 100 && y < 190)
	{
		return true;
	}
	return false;
}


void game :: render_level_hard()
{
    if(!checkclick_level_hard())
    {
        LTexture image;
        image.Load("image/level_hard.png", 1);
        image.Render( (SCREEN_WIDTH-image.getWidth())/2, 250);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/level_hard.png", 1.2);
        image.Render((SCREEN_WIDTH-image.getWidth())/2-10, 250-10);
        image.free();
    }
}

bool game :: checkclick_level_hard()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 125 && x < 125 + 250 && y > 250 && y < 340)
	{
		return true;
	}
	return false;
}

void game :: renderTick(bool isHard)
{
    if(!isHard)
    {
        LTexture image;
        image.Load("image/tick.png", 1);
        image.Render( 375, 100);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/tick.png", 1);
        image.Render( 375, 250);
        image.free();
    }
}

void game :: render_music_button()
{
     if(!checkclick_music_button())
    {
        LTexture image;
        image.Load2("image/music_button.png", 1);
        image.Render( 435, 15);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load2("image/music_button.png", 1.2);
        image.Render(435-5, 15-5);
        image.free();
    }
}

bool game :: checkclick_music_button()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 435 && x < 435+52 && y > 15 && y < 15 + 51)
	{
		return true;
	}
	return false;
}

void game :: render_back_ground_music()
{
    LTexture image;
	image.Load("image/music_background.png", 1);
	image.Render(0, 0);
	image.free();
}

void game :: render_music_pressStart()
{
    if(!check_music_pressStart())
    {
        LTexture image;
        image.Load("image/music_press_start.png", 1);
        image.Render( 100, 30);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/music_press_start.png", 1.2);
        image.Render(100-10, 30-10);
        image.free();
    }
}

bool game :: check_music_pressStart()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 100 && x < 100+250 && y > 30 && y < 30 + 80)
	{
		return true;
	}
	return false;
}

void game :: render_music_saveMe()
{
    if(!check_music_saveMe())
    {
        LTexture image;
        image.Load("image/music_save_me.png", 1);
        image.Render(100, 130);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/music_save_me.png", 1.2);
        image.Render(100-10, 130-10);
        image.free();
    }
}

bool game :: check_music_saveMe()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 100 && x < 100+250 && y > 130 && y < 130 + 80)
	{
		return true;
	}
	return false;
}

void game :: render_music_windFall()
{
    if(!check_music_windFall())
    {
        LTexture image;
        image.Load("image/music_wind_fall.png", 1);
        image.Render(100, 230);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/music_wind_fall.png", 1.2);
        image.Render(100-10, 230-10);
        image.free();
    }
}

bool game :: check_music_windFall()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 100 && x < 100+250 && y > 230 && y < 230 + 80)
	{
		return true;
	}
	return false;
}

void game :: render_music_foreverBound()
{
    if(!check_music_foreverBound())
    {
        LTexture image;
        image.Load("image/music_forever_bound.png", 1);
        image.Render(100, 330);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/music_forever_bound.png", 1.2);
        image.Render(100-10, 330-10);
        image.free();
    }
}

bool game :: check_music_foreverBound()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 100 && x < 100+250 && y > 330 && y < 330 + 80)
	{
		return true;
	}
	return false;
}

void game :: render_tick_music(bool is_press_start, bool is_save_me, bool is_wind_fall, bool is_forever_bound)
{
    if(is_press_start)
    {
        LTexture image;
        image.Load("image/tick.png", 0.9);
        image.Render( 370, 30);
        image.free();
    }
    if(is_save_me)
    {
        LTexture image;
        image.Load("image/tick.png", 0.9);
        image.Render( 370, 130);
        image.free();
    }
    if(is_wind_fall)
    {
        LTexture image;
        image.Load("image/tick.png", 0.9);
        image.Render( 370, 230);
        image.free();
    }
    if(is_forever_bound)
    {
        LTexture image;
        image.Load("image/tick.png", 0.9);
        image.Render( 370, 330);
        image.free();
    }
}

void game :: render_help_button()
{
    if(!check_help_button())
    {
        LTexture image;
        image.Load("image/help_button.png",1);
        image.Render(375,530);
        image.free();
    }
    else
    {
        LTexture image;
        image.Load("image/help_button.png",1.2);
        image.Render(375-5,530-5);
        image.free();
    }
}

bool game :: check_help_button()
{
    int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > 375 && x < 375+100 && y > 530 && y < 530 + 70)
	{
		return true;
	}
	return false;
}

void game :: render_help_back_ground()
{
    LTexture image;
    image.Load("image/help_background.png", 1);
    image.Render( 0,0);
    image.free();
}
