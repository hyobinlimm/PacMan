#pragma once

#include <windows.h>

// ó�� �ð� �ʱ�ȭ
int GetStartTime();

// ������ �ð� �ʱ�ȭ
int SetEndTime();

// �� ���� ���� ���� �ɸ� �ð�
int DeltaTime(int startNum, int endNum);

// �ð� ���
void TimeOutPut(int timeNum);

