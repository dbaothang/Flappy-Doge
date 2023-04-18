
#include "game.h"
#include "lib.h"
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

const int FPS = 60;
const int frameDelay = 1000 / FPS;

using namespace std;

int main(int argc, char** argv)
{
    Uint32 frameStart;
    int frameTime;
    game g;

    bool isHard = 0;
    bool isMenu = 0;
    bool isPause = 0;
    bool isDark = 0;

    while(!g.isQuit())
    {
        frameStart = SDL_GetTicks();

        if(!g.isDie())
        {
            g.takeInput();
            if (isPause == 0 && g.userInput.Type == game::input::PLAY && !g.checkclickpause_resume())
            {

                g.sound.playBreath();
                g.shiba.resetTime();
                g.userInput.Type = game::input::NONE;
            }

            if(isPause==0)
            {
                g.sound.playPoint();
            }

            if (g.userInput.Type == game::input::PAUSE)
            {
                g.sound.checkPause();
                g.sound.pauseMusic();
                g.sound.continueMusic();
                isPause = abs(1 - isPause);
                g.userInput.Type = game::input::NONE;
            }

            if(g.userInput.Type==game::input::CLICK_PAUSE)
            {
                g.sound.checkPause();
                g.sound.pauseMusic();
                g.sound.continueMusic();

                isPause = abs(1 - isPause);
                g.userInput.Type = game::input::NONE;
            }

            if (!isDark) g.renderBackground();
            else g.renderBackgroundNight();
            g.pipe.render();
            g.land.render();
            g.shiba.render();
            g.enemy.render(isPause);
            g.rocket.render();
            g.renderScoreLarge();

            g.sound.turn_on_off_music(isPause);

            if (!isPause)
            {
                g.shiba.update(g.get_Pipe_Width(), g.get_Pipe_Height(), isHard);
                g.pipe.update();
                g.land.update();
                g.enemy.update();
                g.rocket.update();
                g.pause();
            }
            else
            {
                g.resume();
                g.renderPauseTab();
                g.renderScoreSmall();
                g.renderBestScore();
                g.replay();
                g.sound.renderSound();
                if (!isDark) g.lightTheme();
                else g.darkTheme();
                g.nextButton();
                if (g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isPause = 0;
                        g.sound.checkPause();
                        g.sound.pauseMusic();
                        g.sound.continueMusic();

                    }
                    else if (g.changeTheme())
                    {
                        isDark = abs(1 - isDark);
                        g.shiba.init(isDark,isHard);
                    }
                    g.sound.checkSound();
                    g.userInput.Type = game::input::NONE;
                }
            }
            g.display();
        }

        if (g.isDie())
        {
            if (isMenu) {
                g.sound.playHit();
                g.shiba.render();
                g.sound.dogedie();
            }
            g.userInput.Type = game::input::NONE;
            while(g.isDie() && !g.isQuit())
            {
                g.takeInput();
                if (isMenu == 1 && g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        g.sound.play_button_play();
                        isMenu = 0;
                    }
                    g.userInput.Type = game::input::NONE;
                }
                if (!isDark) g.renderBackground();
                else g.renderBackgroundNight();
                g.pipe.render();
                g.enemy.render(isPause);
                g.land.render();
                if (isMenu)
                {
                    g.sound.stopMusic();
                    g.shiba.render();
                    g.shiba.fall();
                    g.renderGameOver();
                    g.renderMedal();
                    g.renderScoreSmall();
                    g.renderBestScore();
                    g.replay();
                }
                else
                {
                    g.rocket.init();
                    g.land.init();
                    g.enemy.init();
                    g.pipe.init();
                    g.shiba.init(isDark,isHard);
                    g.shiba.render();
                    g.renderMessage();
                    g.renderquit();
                    g.replay();
                    if (g.userInput.Type == game::input::PLAY&&g.checkReplay())
                    {
                        g.sound.play_button_play();
                        g.Restart();
                        isMenu = 1;
                        g.userInput.Type = game::input::NONE;
                        g.sound.playMusic();
                    }
                    g.land.update();
                }
                g.display();
            }
            g.enemy.init();
            g.pipe.init();
        }
        //Limit FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}
