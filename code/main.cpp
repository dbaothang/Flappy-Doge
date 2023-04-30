
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

    isLevel = 0;
    isHard = 0;
    isMenu = 0;
    isPause = 0;
    isDark = 0;
    isMusic = 0;
    is_press_start = 1;
    is_save_me = 0;
    is_wind_fall = 0;
    is_forever_bound = 0;
    bool isSound = 1;


    while(!g.isQuit())
    {
        frameStart = SDL_GetTicks();
        if (!isHard)
        {
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

                    if (!isDark)
                    {
                        g.renderBackground();
                    }
                    else
                    {
                        g.renderBackgroundNight();
                    }
                    g.pipe.render();
                    g.land.render();
                    g.shiba.render();
//                    g.enemy.render(isPause);
//                    g.explode.render(isPause);
//                    g.rocket.render();
                    g.renderScoreLarge();
                    g.sound.lg2Music();
                    g.sound.turn_on_off_music(isPause);

                    if (!isPause)
                    {
                        g.shiba.update_pipe(g.get_Pipe_Width(), g.get_Pipe_Height(), isHard);
                        g.pipe.update(isHard);
                        g.land.update();
//                        g.enemy.update();
//                        g.rocket.update();
//                        g.explode.update();
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
                            g.sound.checkSound(isMenu);
                            g.userInput.Type = game::input::NONE;
                        }
                    }
                    g.display();
            }
        }

     if(isHard)
     {
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

                if (!isDark)
                {
                    g.renderBackground();
                }
                else
                {
                    g.renderBackgroundNight();
                }
                g.pipe.render();
                g.land.render();
                g.laser.render();
                g.shiba.render();
                g.enemy.render(isPause);
                g.explode.render(isPause);
                g.rocket.render();
                g.renderScoreLarge();


                g.sound.lg2Music();
                g.sound.turn_on_off_music(isPause);

                if (!isPause)
                {
                    g.shiba.update_pipe(g.get_Pipe_Width(), g.get_Pipe_Height(), isHard);
                    g.shiba.update_threat(g.get_Enemy_Width(), g.get_Enemy_Height(), g.get_Rocket_Width(), g.get_Rocket_Height(), g.get_Explode_Width(), g.get_Explode_Height());
                    g.pipe.update(isHard);
                    g.land.update();
                    g.enemy.update();
                    g.rocket.update();
                    g.explode.update();
                    g.pause();
                }
                else
                {
                    g.resume();
                    g.renderPauseTab();
                    g.renderScoreSmall();
                    if(!isHard)
                    {
                        g.renderBestScore();
                    }
                    if(isHard)
                    {
                        g.render_BestScore_Hard();
                    }
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
                        g.sound.checkSound(isMenu);
                        g.userInput.Type = game::input::NONE;
                    }
                }
                g.display();
             }
     }

     if (g.isDie())
        {
            if (isMenu) {
//                    g.enemy.reset();
//                    g.rocket.reset();
//                    g.explode.reset_boom();
//                    g.shiba.reset();
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

                if(!isLevel)
                {
                    if (!isDark)
                    {
                        g.renderBackground();
                    }
                    else
                    {
                        g.renderBackgroundNight();
                    }
//                    g.pipe.render();
//                    g.enemy.render(isPause);
                }
//                g.rocket.render();
                g.pipe.render();
//                g.enemy.render(isPause);
                g.land.render();
//                g.explode.render(isPause);
                if (isMenu)
                {
                    if(isHard)
                    {
                        g.explode.render(isPause);
                        g.rocket.render();
                        g.enemy.render(isPause);
                        g.explode.render(isPause);
                        g.rocket.render();
                        g.enemy.render(isPause);
                        g.laser.render();

                        g.enemy.reset();
                        g.rocket.reset();
                        g.explode.reset_boom();
                        g.shiba.reset();
                        g.laser.reset();

                        g.sound.stopMusic();
                        g.shiba.render();
                        g.shiba.fall(isHard);
                        g.renderGameOver();
                        g.renderMedal();
                        g.renderScoreSmall();
                        g.render_BestScore_Hard();
                        g.replay();
                    }
                    if(!isHard)
                    {
                        g.sound.stopMusic();
                        g.shiba.render();
                        g.shiba.fall(isHard);
                        g.renderGameOver();
                        g.renderMedal();
                        g.renderScoreSmall();
                        g.renderBestScore();
                        g.replay();
                    }

                }
                else
                {
                    if(g.userInput.Type==game::input::CLICK_HELP)
                    {
                        isHelp = 1;
                        g.userInput.Type = game::input::NONE;
                    }

                    if(g.userInput.Type==game::input::CLICK_MUSIC)
                    {
                        isMusic = 1;
                        g.userInput.Type = game::input::NONE;
                    }

                    if( g.userInput.Type==game::input::CLICK_LEVEL )
                    {
                        isLevel = 1;
                        g.userInput.Type = game::input::NONE;
                    }

                    if(!isLevel && !isMusic && isHelp)
                    {
                        g.render_help_back_ground();
                        g.renderBack();
                        if(g.userInput.Type==game::input::CLICK_BACK)
                        {
                            isHelp = 0;
                            g.userInput.Type=game::input::NONE;
                        }
                    }

                    if(!isLevel && isMusic && !isHelp )
                    {
                        g.render_back_ground_music();
                        g.renderBack();
                        g.render_music_pressStart();
                        g.render_music_saveMe();
                        g.render_music_windFall();
                        g.render_music_foreverBound();
                        g.render_tick_music(is_press_start, is_save_me, is_wind_fall, is_forever_bound);
                        g.sound.changeMusic(is_press_start, is_save_me, is_wind_fall, is_forever_bound);

                        if(g.userInput.Type==game::input::CLICK_PRESS_START)
                        {
                            is_press_start=1;
                            is_save_me=0;
                            is_wind_fall=0;
                            is_forever_bound=0;
                            g.userInput.Type = game::input::NONE;
                        }
                        if(g.userInput.Type==game::input::CLICK_SAVE_ME)
                        {
                            is_press_start=0;
                            is_save_me=1;
                            is_wind_fall=0;
                            is_forever_bound=0;
                            g.userInput.Type = game::input::NONE;
                        }
                        if(g.userInput.Type==game::input::CLICK_WIND_FALL)
                        {
                            is_press_start=0;
                            is_save_me=0;
                            is_wind_fall=1;
                            is_forever_bound=0;
                            g.userInput.Type = game::input::NONE;
                        }
                        if(g.userInput.Type==game::input::CLICK_FOREVER_BOUND)
                        {
                            is_press_start=0;
                            is_save_me=0;
                            is_wind_fall=0;
                            is_forever_bound=1;
                            g.userInput.Type = game::input::NONE;
                        }

                        if(g.userInput.Type==game::input::CLICK_BACK)
                        {
                            isMusic = 0;
                            g.userInput.Type=game::input::NONE;
                        }
                    }

                    if(isLevel && !isMusic && !isHelp)
                    {
                        g.render_back_ground_level();
                        g.renderBack();
                        g.render_level_normal();
                        g.render_level_hard();
                        g.renderTick(isHard);

                        if(g.userInput.Type==game::input::CLICK_NORMAL)
                        {
                            isHard=0;
                            g.userInput.Type=game::input::NONE;
                        }

                        if(g.userInput.Type==game::input::CLICK_HARD)
                        {
                            isHard=1;
                            g.userInput.Type=game::input::NONE;
                        }

                        if(g.userInput.Type==game::input::CLICK_BACK)
                        {
                            isLevel = 0;
                            g.userInput.Type=game::input::NONE;
                        }

                    }
                    if(!isLevel && !isMusic && !isHelp)
                    {
//                        g.enemy.reset();
//                        g.rocket.reset();
//                        g.explode.reset_boom();
//                        g.shiba.reset();
                        g.rocket.init();
                        g.laser.init();
                        g.explode.init();
                        g.land.init();
                        g.enemy.init();
                        g.pipe.init();
//                        if(isSound)
//                        {
//                             g.sound.init(is_press_start, is_save_me, is_wind_fall, is_forever_bound);
//                             isSound = 0;
//                        }
                        g.shiba.init(isDark,isHard);
                        g.shiba.render();
                        g.renderMessage();
                        g.renderLevel();
                        g.render_music_button();
                        g.render_help_button();
                        g.renderquit();
                        g.replay();
                        g.sound.check_lgMusic();

                        if (g.userInput.Type == game::input::PLAY&&g.checkReplay())
                        {
                            g.sound.play_button_play();
                            g.Restart();
                            g.sound.playMusic();
                            isMenu = 1;
                            g.sound.lg1Music();
                            g.userInput.Type = game::input::NONE;
                        }
                    }
//                    g.land.update();
                }
                g.display();
            }
//            g.enemy.init();
//            g.pipe.init();
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
