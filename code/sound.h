#pragma once
#include <SDL_mixer.h>
#include <string>
#include "lib.h"


using namespace std;

class sound:LTexture
{
public:
    bool init(); // khởi tạo

    void Free(); // giải phóng

    void playBreath(); // tiếng thở khi cho shiba bay

    void playHit(); // tiếng va chạm của shiba

    void playPoint(); // tiếng điểm số

    void changeMusic(bool is_press_start, bool is_save_me, bool is_wind_fall, bool is_forever_bound);
    // hàm thay đổi âm nhạc

    void playMusic(); // chơi nhạc

    void play_button_play(); // âm thanh khi ấn vào nút play

    void renderSound(); // vẽ hình ảnh âm thanh

    bool checkSound(bool isMenu); // xem có tắt_bật âm thanh không

    void checkPause(); // kiểm tra xem người chơi có tạm dừng game không

    void pauseMusic(); // tạm dừng âm nhạc

    void continueMusic(); // tiếp tục âm nhạc

    void stopMusic(); // dừng hẳn âm thanh

    void check_lgMusic(); // xem đã tắt âm thanh và shiba đã chết chưa

    void lg1Music(); // từ cái hàm trên thì sẽ phát nhạc lúc chơi lại game với âm lượng 0

    void lg2Music(); // nếu đã có 2 hàm trên thì kiểm tra đang chơi và đã bật lại âm thanh và biến lg_music

    static int n; // biến để mỗi khi shiba được cộng điểm sẽ có âm thanh

    void dogedie(); // khi shiba chết biến quay trở về ban đầu

    void turn_on_off_music (bool isPause); // bật/tắt âm thanh nhạc

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
