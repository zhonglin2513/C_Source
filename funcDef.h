
#ifndef FUNCDEF_H
#define FUNCDEF_H
#include <stdio.h>
#include <windows.h>
#include <stdint.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")  // 链接多媒体库


double CalculateCPULoad(FILETIME idleTime, FILETIME kernelTime, FILETIME userTime,
                        FILETIME prevIdleTime, FILETIME prevKernelTime, FILETIME prevUserTime) {
    ULONGLONG idle = ((ULONGLONG)idleTime.dwHighDateTime << 32) | idleTime.dwLowDateTime;
    ULONGLONG kernel = ((ULONGLONG)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime;
    ULONGLONG user = ((ULONGLONG)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime;

    ULONGLONG prevIdle = ((ULONGLONG)prevIdleTime.dwHighDateTime << 32) | prevIdleTime.dwLowDateTime;
    ULONGLONG prevKernel = ((ULONGLONG)prevKernelTime.dwHighDateTime << 32) | prevKernelTime.dwLowDateTime;
    ULONGLONG prevUser = ((ULONGLONG)prevUserTime.dwHighDateTime << 32) | prevUserTime.dwLowDateTime;

    ULONGLONG sys = (kernel - prevKernel) + (user - prevUser);
    ULONGLONG idleDiff = idle - prevIdle;

    return (double)(sys - idleDiff) * 100.0 / sys;
}
long calcSum(int32_t n);
void nineMultiply();

#endif // FUNCDEF_H