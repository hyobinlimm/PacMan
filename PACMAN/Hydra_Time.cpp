#include "Hydra_Time.h"
#include "Hydra_Engine.h"

int GetStartTime()
{
	unsigned long StartTime = GetTickCount64();

	return StartTime;
}

int SetEndTime()
{
	unsigned long EndTime = GetTickCount64();

	return EndTime;
}

int DeltaTime(int startNum, int endNum)
{
	int startTime = startNum;
	int endTime = endNum;

	int deltaTime = endTime - startTime;

	return (deltaTime / 1000);
}

void TimeOutPut(int timeNum)
{
	LHLocateCursor(0, 35);

	printf("%d", timeNum);
}
