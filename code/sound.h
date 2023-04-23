#pragma once
#include <SDL_mixer.h>
#include <string>
#include "lib.h"


using namespace std;

class sound:LTexture
{
public:
    bool init(bool is_press_start, bool is_save_me, bool is_wind_fall, bool is_forever_bound);

    void Free();

    void playBreath();

    void playHit();

    void playPoint();

    void playMusic();

    void play_button_play();

    void renderSound();

    bool checkSound();

    void checkPause();

    void pauseMusic();

    void continueMusic();

    void stopMusic();

    static int n;

    void dogedie();

    void turn_on_off_music (bool isPause);

private:

    const int POS_X = 180;
    const int POS_Y = 267;
    bool isPlay = 0;
    bool check_Pause = 0;
    Mix_Chunk* breath = NULL;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* point = NULL;
    Mix_Chunk* play = NULL;
    Mix_Music* music = NULL;
    string music_path="";

//    Mix_Chunk* drop = NULL;
    SDL_Rect Mute ;
    SDL_Rect Active ;
};
