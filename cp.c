
#include "funcDef.h"
#include "funcDef.c"


int main(){
    FILETIME idleTime, kernelTime, userTime;
    FILETIME prevIdleTime, prevKernelTime, prevUserTime;

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    // nineMultiply();
    // 获取初始 CPU 时间
    if (!GetSystemTimes(&prevIdleTime, &prevKernelTime, &prevUserTime)) {
        printf("GetSystemTimes failed.\n");
        return 1;
    }

    Sleep(1000); // 等待 1 秒

    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        printf("GetSystemTimes failed.\n");
        return 1;
    }

    double cpuLoad = CalculateCPULoad(idleTime, kernelTime, userTime,
                                      prevIdleTime, prevKernelTime, prevUserTime);
    printf("CPU usague is : %.2f%%\n", cpuLoad);
       
    if (!GlobalMemoryStatusEx(&memInfo)) {
        printf("Read memory info failed.\n");
        return 1;
    }

    // 内存单位：字节
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
    DWORDLONG availPhysMem = memInfo.ullAvailPhys;
    DWORDLONG usedPhysMem = totalPhysMem - availPhysMem;

    double usedPercent = (double)usedPhysMem / totalPhysMem * 100.0;

    printf("totalPhysMemory: %llu MB\n", totalPhysMem / 1024 / 1024);
    printf("availPhysMemory: %llu MB\n", availPhysMem / 1024 / 1024);
    printf("usedPhysMemory: %llu MB\n", usedPhysMem / 1024 / 1024);
    printf("memoryUsage: %.2f%%\n", usedPercent);

    // Beep(750,1000);
    // Sleep(500);
    // Beep(1000,1000);
    // PlaySound(TEXT("SystemExit"), NULL, SND_ALIAS);
    // 可以用双反斜杠或者正斜杠
    // PlaySound(TEXT("C:\\Windows\\Media\\chimes.wav"), NULL, SND_FILENAME | SND_SYNC);

    // if (!PlaySound(TEXT("C:\\Windows\\Media\\Alarm01.wav"), NULL, SND_FILENAME | SND_ASYNC)) {
    //         printf("play sound failed, please check the source path.\n");
    //         return 1;
    //     }
    char windir[MAX_PATH];
    GetWindowsDirectoryA(windir, MAX_PATH);
    char wavPath[MAX_PATH];
    sprintf(wavPath, "%s\\Media\\Alarm01.wav", windir);

    if (!PlaySoundA(wavPath, NULL, SND_FILENAME | SND_SYNC)) {
        printf("Play sound failed!\n");
        return 1;
    }

    return 0;
}