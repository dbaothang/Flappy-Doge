#pragma once
#include <SDL_mixer.h>
#include <string>
#include "lib.h"


using namespace std;

class sound:LTexture
{
public:
    bool init();

    void Free();

    void playBreath();

    void playHit();

    void playPoint();

    void changeMusic(bool is_press_start, bool is_save_me, bool is_wind_fall, bool is_forever_bound);

    void playMusic();

    void play_button_play();

    void renderSound();

    bool checkSound(bool isMenu);

    void checkPause();

    void pauseMusic();

    void continueMusic();

    void stopMusic();

    void check_lgMusic();

    void lg1Music();

    void lg2Music();

    static int n;

    void dogedie();

    void turn_on_off_music (bool isPause);

private:

    const int POS_X = 180;
    const int POS_Y = 267;
    bool isPlay = 1;
    bool check_Pause = 0;
    bool lg_music = 0;
    bool turn_on = 0;
    bool turn_off = 1;

    Mix_Chunk* breath = NULL;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* point = NULL;
    Mix_Chunk* play = NULL;
    Mix_Music* music = NULL;
    string music_path="";
    string breath_path="";
    string hit_path="";
    string sound_path="";
    string point_path="";
    string play_path="";

//    Mix_Chunk* drop = NULL;
    SDL_Rect Mute ;
    SDL_Rect Active ;
};
