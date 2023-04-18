#pragma once

#include "rocket.h"
#include "enemy.h"
#include "doge.h"
#include "pipe.h"
#include "land.h"
#include "sound.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class game:LTexture
{
public:
    struct input
    {
        enum type { QUIT, PLAY, NONE, PAUSE,CLICK_PAUSE, CLICK_QUIT};
        type Type;
    };
    input userInput;
    doge shiba;
    pipe pipe;
    sound sound;
    land land;
    enemy enemy;
    rocket rocket;

public:
    game();

    ~game();

    bool initGraphic();

    bool isQuit()
    {
        return quit;
    }

    bool isDie()
    {
        return die;
    }

    int get_Pipe_Width()
    {
        return pipe.width();
    }

    int get_Pipe_Height()
    {
        return pipe.height();
    }

    int get_Enemy_Width()
    {
        return enemy.width();
    }

    int get_Enemy_Height()
    {
        return enemy.height();
    }

    void takeInput();

    void display();

    void releaseGraphic();

    void renderScoreSmall();

    void renderScoreLarge();

    void renderBestScore();

    void renderMessage();

    void renderBackground();

    void renderBackgroundNight();

    void renderLand();

    void resume();

    void pause();

    bool checkclickpause_resume();

    void renderPauseTab();

    void lightTheme();

    void darkTheme();

    void nextButton();

    bool changeTheme();

    void renderGameOver();

    void renderMedal();

    void replay();

    bool checkReplay();

    void Restart();

    void renderquit();

    bool checkclick_quit();

private:
    const double scaleNumberS = 0.75;
    int bestScore;
};
