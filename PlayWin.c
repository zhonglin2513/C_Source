#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <signal.h>
#pragma comment(lib, "winmm.lib") // MSVC 可用，gcc 可忽略

volatile int keepRunning = 1;

// Ctrl+C 信号处理函数
void intHandler(int dummy) {
    keepRunning = 0;
}

int main() {
    // 注册 Ctrl+C 信号
    signal(SIGINT, intHandler);
    // signal(SIGABRT, intHandler);


    // keepRunning = 0;
    // 获取 Windows 系统目录
    char windir[MAX_PATH];
    GetWindowsDirectoryA(windir, MAX_PATH);

    // 构造 WAV 文件路径
    char wavPath[MAX_PATH];
    sprintf(wavPath, "%s\\Media\\chimes.wav", windir);

    printf("loop playback %s, press Ctrl+C to stop...\n", wavPath);

    while (keepRunning) {
        // 异步播放 WAV 文件
        if (!PlaySoundA(wavPath, NULL, SND_FILENAME | SND_ASYNC)) {
            printf("play sound failed, please check the source path.\n");
            return 1;
        }

        Sleep(2000); // 等待 2 秒，可根据 WAV 长度调整
    }

    // 停止播放
    PlaySoundA(NULL, NULL, 0);

    printf("\n stopped \n");
    return 0;
}