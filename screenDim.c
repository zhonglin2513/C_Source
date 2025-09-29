#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#pragma comment(lib, "Dxva2.lib")

// 回调函数，用于枚举每个显示器
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM lParam) {
    int brightness = *(int*)lParam;  // 获取亮度值

    DWORD numPhysicalMonitors = 0;
    if (GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &numPhysicalMonitors) && numPhysicalMonitors > 0) {
        PHYSICAL_MONITOR* pMonitors = malloc(sizeof(PHYSICAL_MONITOR) * numPhysicalMonitors);
        if (!pMonitors) return TRUE;

        if (GetPhysicalMonitorsFromHMONITOR(hMonitor, numPhysicalMonitors, pMonitors)) {
            for (DWORD i = 0; i < numPhysicalMonitors; i++) {
                if (!SetMonitorBrightness(pMonitors[i].hPhysicalMonitor, (DWORD)brightness)) {
                    printf("Failed to set brightness for monitor %lu\n", i);
                }
            }
            DestroyPhysicalMonitors(numPhysicalMonitors, pMonitors);
        }
        free(pMonitors);
    }

    return TRUE;  // 继续枚举下一个显示器
}

int main() {
    int brightness;

    printf("Input brightness level (0-100): ");
    if (scanf("%d", &brightness) != 1) {
        printf("Invalid input!\n");
        return 1;
    }

    if (brightness < 0) brightness = 0;
    if (brightness > 100) brightness = 100;

    // 枚举所有显示器并设置亮度
    if (!EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&brightness)) {
        printf("Failed to enumerate monitors.\n");
        return 1;
    }

    printf("Brightness setting completed.\n");
    return 0;
}



