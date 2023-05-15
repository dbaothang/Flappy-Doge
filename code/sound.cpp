
#include "sound.h"
#include <stdio.h>
#include <iostream>
#include <string>

int sound :: n = 0;
bool sound::init()
{


    breath_path = "sound/sfx_breath.wav";
    hit_path = "sound/sfx_bonk.wav";
    sound_path = "sound/sound.png";
    point_path = "sound/sfx_point.wav";
    music_path = "sound/press_start_music.mp3";
    play_path= "sound/button_play.wav";

    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        music = Mix_LoadMUS( music_path.c_str());
        if( music == NULL )
        {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
        }


        breath = Mix_LoadWAV( breath_path.c_str() );
        if ( breath == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        play= Mix_LoadWAV( play_path.c_str() );
        if ( play == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        hit = Mix_LoadWAV( hit_path.c_str() );
        if (hit == NULL)
        {
            printf( "Failed to load chord! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
        point = Mix_LoadWAV( point_path.c_str() );
        if ( point == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }


        if (!Load(sound_path))
        {
            return false;
        }

        Active.x = 0; Active.y = 0; Active.w = getWidth(); Active.h = getHeight() / 2;
        Mute.x = 0; Mute.y = getHeight() / 2; Mute.w = getWidth(); Mute.h = getHeight() / 2;
//        isPlay = true;
    }
    return success;
}

void sound::Free()
{
    free();

    Mix_FreeChunk(breath);
    breath = NULL;
    Mix_FreeChunk(hit);
    hit = NULL;
    Mix_FreeChunk(point);
    point = NULL;
    Mix_FreeChunk(play);
    play = NULL;
    Mix_FreeMusic(music);
    music = NULL;

    Mix_Quit();
}

void sound :: changeMusic(bool is_press_start, bool is_save_me, bool is_wind_fall, bool is_forever_bound)
{
    if(is_press_start)
    {
        music_path = "sound/press_start_music.mp3";
    }
    if(is_save_me)
    {
        music_path = "sound/Save_Me.mp3";
    }
    if(is_wind_fall)
    {
        music_path = "sound/windfall.mp3";
    }
    if(is_forever_bound)
    {
        music_path = "sound/forever_Bound.mp3";
    }
    music = Mix_LoadMUS( music_path.c_str());
    if( music == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void sound :: playMusic ()
{
    if(isPlay)
    {
        Mix_PlayMusic( music, -1 );
        Mix_VolumeMusic(60);
    }
}

void sound :: checkPause()
{
    check_Pause=abs(1-check_Pause);
}

void sound :: pauseMusic()
{
    if(check_Pause) {Mix_PauseMusic();}
}

void sound :: continueMusic()
{
    if(!check_Pause) {Mix_ResumeMusic();}
}

void sound :: stopMusic()
{
    if(die) {Mix_HaltMusic();}
}


void sound :: check_lgMusic()
{
    if(!isPlay && die)
    {
        lg_music=1;
    }
}

void sound :: lg1Music ()
{
    if(lg_music && isMenu )
    {
        Mix_VolumeMusic(0);
        Mix_PlayMusic( music, -1 );
    }
}

void sound :: lg2Music()
{
    if(isPlay && !isPause && lg_music)
    {
        Mix_VolumeMusic(60);
        lg_music = 0;
    }
}

void sound::playBreath()
{
    if (isPlay)
    {
        Mix_PlayChannel( -1, breath, 0 );
    }
}

void sound::playHit()
{
    if (isPlay)
    {
       Mix_PlayChannel(-1, hit, 0);
    }
}

void sound:: playPoint()
{
    if(isPlay)
    {
        if(score>n)
        {
            Mix_PlayChannel(-1, point, 0);
            n++;
        }
    }
}

void sound::play_button_play()
{
    if (isPlay)
    {
        Mix_PlayChannel(-1, play, 0);
    }
}

void sound::dogedie()
{
    n=0;
}

void sound :: turn_on_off_music (bool isPause)
{
    if( !isPlay && isPause && turn_off )
    {
        Mix_VolumeMusic(0);
        turn_off = 0;
        turn_on = 1;
    }
    if( isPlay && !isPause && turn_on)
    {
        Mix_VolumeMusic(60);
        turn_off = 1;
        turn_on = 0;
    }
}

void sound::renderSound()
{
    if (isPlay)
    {
        Render(POS_X, POS_Y, 0, &Active);
    }
    else
    {
        Render(POS_X, POS_Y, 0, &Mute);
    }
}

bool sound::checkSound(bool isMenu)
{

        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > POS_X && x < POS_X + getWidth() &&
            y > POS_Y && y < POS_Y + getHeight() && isMenu )
        {
            isPlay = !isPlay;
            return true;
        }
        return false;
}

