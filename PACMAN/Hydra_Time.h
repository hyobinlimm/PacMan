#pragma once

#include <windows.h>

// 처음 시간 초기화
int GetStartTime();

// 마지막 시간 초기화
int SetEndTime();

// 한 루프 도는 동안 걸린 시간
int DeltaTime(int startNum, int endNum);

// 시간 출력
void TimeOutPut(int timeNum);

