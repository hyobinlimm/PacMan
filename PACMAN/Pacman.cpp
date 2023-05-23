#include "Pacman.h"

#include "Hydra_Engine.h"
#include "Hydra_Time.h"
#include "Sound.h"

#include <queue>


/// <summary>
/// -1 = "─", -2 = "│", -3 = "┌", -4 = "┐", -5 = "└", -6 = "┘", -7 = 고스트 집 입구
///  1 = 먹이, 2 = 고스트 바꾸는 먹이,  7 = 워프 
/// 10 = 팩맨, 11~14 = 고스트
/// </summary>
int g_MapArr[HIGH][WIDTH] =
{ { -3,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -4},
	{ -2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  -2},
	{ -2,   2,  -3,  -1,  -1,  -4,   0,  -3,  -4,   0,  -3,  -1,  -1,  -1,  -1,  -1,  -1,  -4,   0,  -3,  -4,   0,  -3,  -1,  -1,  -4,   2,  -2},
	{ -2,   0,  -5,  -1,  -4,  -2,   0,  -2,  -2,   0,  -5,  -1,  -1,  -4,  -3,  -1,  -1,  -6,   0,  -2,  -2,   0,  -2,  -3,  -1,  -6,   0,  -2},
	{ -2,   0,   0,   0,  -2,  -2,   0,  -2,  -2,   0,   0,   0,   0,  -2,  -2,   0,   0,   0,   0,  -2,  -2,   0,  -2,  -2,   0,   0,   0,  -2},
	{ -5,  -1,  -4,   0,  -2,  -2,   0,  -2,  -2,   0,  -3,  -4,   0,  -2,  -2,   0,  -3,  -4,   0,  -2,  -2,   0,  -2,  -2,   0,  -3,  -1,  -6},
	{  0,   0,  -2,   0,  -2,  -2,   0,  -2,  -2,   0,  -2,  -2,   0,  -2,  -2,   0,  -2,  -2,   0,  -2,  -2,   0,  -2,  -2,   0,  -2,   0,   0},
	{ -1,  -1,  -6,   0,  -5,  -6,   0,  -5,  -6,   0,  -2,  -2,   0,  -5,  -6,   0,  -2,  -2,   0,  -5,  -6,   0,  -5,  -6,   0,  -5,  -1,  -1},
	{  7,   0,   0,   0,   0,   0,   0,   0,   0,   0,  -2,  -2,   0,   0,   0,   0,  -2,  -2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7},
	{ -1,  -1,  -4,   0,  -3,  -1,  -1,  -1,  -4,   0,  -2,  -5,  -1,  -1,  -1,  -1,  -6,  -2,   0,  -3,  -1,  -1,  -1,  -4,   0,  -3,  -1,  -1},
	{ -3,  -1,  -6,   0,  -5,  -1,  -1,  -1,  -6,   0,  -5,  -1,  -1,  -1,  -1,  -1,  -1,  -6,   0,  -5,  -1,  -1,  -1,  -6,   0,  -5,  -1,  -4},
	{ -2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  -2},
	{ -2,   0,  -3,  -1,  -1,  -4,   0,  -3,  -4,   0,  -3,  -1,  -1,  -7,  -7,  -1,  -1,  -4,   0,  -3,  -4,   0,  -3,  -1,  -1,  -4,   0,  -2},
	{ -2,   0,  -2,  -3,  -1,  -6,   0,  -2,  -2,   0,  -2,   0,   0,   0,   0,   0,   0,  -2,   0,  -2,  -2,   0,  -5,  -1,  -4,  -2,   0,  -2},
	{ -2,   0,  -2,  -2,   0,   0,   0,  -2,  -2,   0,  -2,   0,   0,   0,   0,   0,   0,  -2,   0,  -2,  -2,   0,   0,   0,  -2,  -2,   0,  -2},
	{ -2,   0,  -2,  -2,   0,  -3,  -1,  -6,  -2,   0,  -2,   0,   0,   0,   0,   0,   0,  -2,   0,  -2,  -5,  -1,  -4,   0,  -2,  -2,   0,  -2},
	{ -2,   0,  -5,  -6,   0,  -5,  -1,  -1,  -6,   0,  -5,  -1,  -1,  -1,  -1,  -1,  -1,  -6,   0,  -5,  -1,  -1,  -6,   0,  -5,  -6,   0,  -2},
	{ -2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  -2},
	{ -2,   0,  -3,  -1,  -1,  -1,  -4,   0,  -3,  -1,  -1,  -4,   0,  -3,  -4,   0,  -3,  -1,  -1,  -4,   0,  -3,  -1,  -1,  -1,  -4,   0,  -2},
	{ -2,   0,  -2,  -3,  -1,  -1,  -6,   0,  -2,  -3,  -1,  -6,   0,  -2,  -2,   0,  -5,  -1,  -4,  -2,   0,  -5,  -1,  -1,  -4,  -2,   0,  -2},
	{ -2,   0,  -2,  -2,   0,   0,   0,   0,  -2,  -2,   0,   0,   0,  -2,  -2,   0,   0,   0,  -2,  -2,   0,   0,   0,   0,  -2,  -2,   0,  -2},
	{ -2,   0,  -2,  -2,   0,  -3,  -4,   0,  -2,  -2,   0,  -3,  -1,  -6,  -5,  -1,  -4,   0,  -2,  -2,   0,  -3,  -4,   0,  -2,  -2,   0,  -2},
	{ -2,   0,  -5,  -6,   0,  -2,  -2,   0,  -5,  -6,   0,  -5,  -1,  -1,  -1,  -1,  -6,   0,  -5,  -6,   0,  -2,  -2,   0,  -5,  -6,   0,  -2},
	{ -2,   2,   0,   0,   0,  -2,  -2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  -2,  -2,   0,   0,	0,   2,  -2},
	{ -5,  -1,  -1,  -4,   0,  -2,  -5,  -1,  -1,  -1,  -1,  -4,   0,  -3,  -4,   0,  -3,  -1,  -1,  -1,  -1,  -6,  -2,   0,  -3,  -1,  -1,  -6},
	{ -3,  -1,  -1,  -6,   0,  -5,  -1,  -1,  -1,  -1,  -1,  -6,   0,  -2,  -2,   0,  -5,  -1,  -1,  -1,  -1,  -1,  -6,   0,  -5,  -1,  -1,  -4},
	{ -2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  -2,  -2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  -2},
	{ -2,   0,  -3,  -1,  -1,  -4,   0,	 -3,  -4,   0,  -3,  -1,  -1,  -6,  -5,  -1,  -1,  -4,   0,  -3,  -4,   0,  -3,  -1,  -1,  -4,   0,  -2},
	{ -2,   0,  -5,  -1,  -1,  -6,   0,	 -2,  -2,   0,  -5,  -1,  -1,  -1,  -1,  -1,  -1,  -6,   0,  -2,  -2,   0,  -5,  -1,  -1,  -6,   0,  -2},
	{ -2,   0,   0,   0,   0,   0,   0,  -2,  -2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  -2,  -2,   0,   0,   0,   0,   0,   0,  -2},
	{ -5,  -1,  -1,  -1,  -1, -1,  -1,  -6,  -5,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -6,  -5,  -1,  -1,  -1,  -1,  -1,  -1,  -6},
};

int g_CoinArr[HIGH][WIDTH] =
{ {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
	{  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0},
	{  0,   2,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   2,   0},
	{  0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0},
	{  0,   1,   1,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   0,   0,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   1,   1,   0},
	{  0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0},
	{  0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0},
	{  0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0},
	{  0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   1,   1,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0},
	{  0,   0,   0,   1,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   1,   0,   0,   0},
	{  0,   0,   0,   1,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   1,   0,   0,   0},
	{  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0},
	{  0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0},
	{  0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0},
	{  0,   1,   0,   0,   1,   1,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   1,   1,   0,   0,   1,   0},
	{  0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0},
	{  0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0},
	{  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0},
	{  0,   1,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   1,   0},
	{  0,   1,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   1,   0},
	{  0,   1,   0,   0,   1,   1,   1,   1,   0,   0,   1,   1,   1,   0,   0,   1,   1,   1,   0,   0,   1,   1,   1,   1,   0,   0,   1,   0},
	{  0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0},
	{  0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0},
	{  0,   2,   1,   1,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   1,	1,   2,   0},
	{  0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0},
	{  0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0},
	{  0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0},
	{  0,   1,   0,   0,   0,   0,   1,	  0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0},
	{  0,   1,   0,   0,   0,   0,   1,	  0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0},
	{  0,   1,   1,   1,   1,   1,   1,   0,   0,   1,   1,   1,   1,   0,   1,   1,   1,   1,   1,   0,   0,   1,   1,   1,   1,   1,   1,   0},
	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
};

// 코인 점수 = 10; 큰 코인 = 50;
// 고스트를 먹으면 200점(연속으로 먹을시 x2)

// 팩맨 과 고스트 
SPLAYER sPacman;
SPLAYER sBlink;
SPLAYER sPinky;
SPLAYER sInky;
SPLAYER sClyde;

int g_Direction = IDLE;

bool g_IsDie = false; // 죽었는지 검사 

bool g_StateClear = false; // 클리어 여뷰

int g_BoardArr[HIGH][WIDTH]; // = 맵 + 코인 

int g_CoinCount = 0; // 팩맨 먹은 코인 카운트 

// 아이템 먹은 시간
int g_GostChangeTime = 0;

// 키 입력 받은 시간
int g_KeyInputChangeTime = 0;

// coin 유무 배열
BOOL g_CopyCoinArr[HIGH][WIDTH];

// 시작 시간
unsigned int g_InitTime = 0;

int dx[4] = { 0, 0, -1, +1 }; // 상 하 좌 우 
int dy[4] = { -1, +1, 0, 0 }; // 상 하 좌 우

// 게임 처음 시작시 coin 초기화
void CopyCoinInit()
{
	for (int i = 0; i < HIGH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (g_CoinArr[i][j] == 1 || g_CoinArr[i][j] == 2)
			{
				g_CopyCoinArr[i][j] = true;

				// 맵에 뿌려진 코인 수 세기
				++g_CoinCount;
			}
			else
			{
				g_CopyCoinArr[i][j] = false;
			}

		}
	}
}

void BoredInitialize()
{
	for (int i = 0; i < HIGH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			g_BoardArr[i][j] = g_MapArr[i][j];
		}
	}

	// 게임 상태와 팩맨 상태 초기화
	g_Direction = IDLE;

	g_IsDie = false;
	g_StateClear = false;

	g_CoinCount = 321;

	// 아이템 먹은 시간
	g_GostChangeTime = 0;

	// 키 입력 받은 시간
	g_KeyInputChangeTime = 0;

	g_InitTime = 0;

	PushCoin();

	PlayerInit();

	// 게임 시작할 때 시간 0으로 초기화
	g_InitTime = GetStartTime();
}

#pragma region 캐릭터 초기화

void PlayerInit()
{
	CreatePacman();
	CreateBlink();
	CreatePinky();
	CreateInky();
	CreateClyde();
}

void CreatePacman()
{
	sPacman.m_SerialNum = PACMAN;
	sPacman.m_State = NOMAL;
	sPacman.m_Position.m_x = 13;
	sPacman.m_Position.m_y = 29;
	sPacman.m_Life = 2;
	sPacman.m_Score = 0;
	DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 0, 0, sPacman.m_SerialNum);

}

void CreateBlink()
{
	sBlink.m_SerialNum = BLINK;
	sBlink.m_State = NOMAL;
	sBlink.m_Position.m_x = 12;
	sBlink.m_Position.m_y = 14;
	DrawUnits(sBlink.m_Position.m_y, sBlink.m_Position.m_x, 0, 0, sBlink.m_SerialNum);
}

void CreatePinky()
{
	sPinky.m_SerialNum = PINKY;
	sPinky.m_State = NOMAL;
	sPinky.m_Position.m_x = 13;
	sPinky.m_Position.m_y = 14;
	DrawUnits(sPinky.m_Position.m_y, sPinky.m_Position.m_x, 0, 0, sPinky.m_SerialNum);

}

void CreateInky()
{
	sInky.m_SerialNum = INKY;
	sInky.m_State = NOMAL;
	sInky.m_Position.m_x = 14;
	sInky.m_Position.m_y = 14;
	DrawUnits(sInky.m_Position.m_y, sInky.m_Position.m_x, 0, 0, sInky.m_SerialNum);

}

void CreateClyde()
{
	sClyde.m_SerialNum = CLYDE;
	sClyde.m_State = NOMAL;
	sClyde.m_Position.m_x = 15;
	sClyde.m_Position.m_y = 14;
	DrawUnits(sClyde.m_Position.m_y, sClyde.m_Position.m_x, 0, 0, sClyde.m_SerialNum);

}

#pragma endregion

void PushCoin()
{
	for (int i = 0; i < HIGH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (g_CopyCoinArr[i][j])
			{
				g_BoardArr[i][j] = g_CoinArr[i][j];
			}
		}
	}
}

void DrawBoard()
{
	for (int y = 0; y < HIGH; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (g_BoardArr[y][x] == -1)
			{
				LHPutAttrCharEx(x * 2, y, "─", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -2)
			{
				LHPutAttrCharEx(x * 2, y, "│", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -3)
			{
				LHPutAttrCharEx(x * 2, y, "┌", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -4)
			{
				LHPutAttrCharEx(x * 2, y, "┐", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -5)
			{
				LHPutAttrCharEx(x * 2, y, "└", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -6)
			{
				LHPutAttrCharEx(x * 2, y, "┘", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -7)
			{
				LHPutAttrCharEx(x * 2, y, "─", BG_BLACK, FG_WHITE);
			}
			else if (g_BoardArr[y][x] == 1)
			{
				LHPutAttrCharEx(x * 2, y, "·", BG_BLACK, FG_YELLOW);
			}
			else if (g_BoardArr[y][x] == 2)
			{
				LHPutAttrCharEx(x * 2, y, "⊙", BG_BLACK, FG_YELLOW);
			}
			else if (g_BoardArr[y][x] == 10)
			{
				LHPutAttrCharEx(x * 2, y, "●", BG_BLACK, FG_YELLOW);
			}
			else if (g_BoardArr[y][x] == 11)
			{
				if (sBlink.m_State == NOMAL)
				{
					LHPutAttrCharEx(x * 2, y, "♠", BG_BLACK, FG_RED);
				}
				else
				{
					LHPutAttrCharEx(x * 2, y, "♠", BG_BLACK, FG_BLUE);
				}

			}
			else if (g_BoardArr[y][x] == 12)
			{
				if (sPinky.m_State == NOMAL)
				{
					LHPutAttrCharEx(x * 2, y, "♠", BG_BLACK, FG_PINK);
				}
				else
				{
					LHPutAttrCharEx(x * 2, y, "♠", BG_BLACK, FG_BLUE);
				}
			}
			else if (g_BoardArr[y][x] == 13)
			{
				if (sInky.m_State == NOMAL)
				{
					LHPutAttrCharEx(x * 2, y, "♠", BG_BLACK, FG_AQUA);
				}
				else
				{
					LHPutAttrCharEx(x * 2, y, "♠", BG_BLACK, FG_BLUE);
				}
			}
			else if (g_BoardArr[y][x] == 14)
			{
				if (sClyde.m_State == NOMAL)
				{
					LHPutAttrCharEx(x * 2, y, "♠", BG_BLACK, FG_GREEN);
				}
				else
				{
					LHPutAttrCharEx(x * 2, y, "♠", BG_BLACK, FG_BLUE);
				}
			}
			else
			{
				LHPutAttrCharEx(x * 2, y, "  ", BG_BLACK, FG_WHITE);
			}

		}
		setColor(WHITE);
		printf("\n");

	}

	LifeOutput(0, 32);
	ScoreOutput(0, 33);

	// 루프를 한번 돌았을 때 시간
	unsigned int InGameStartTime = SetEndTime();

	// 처음 게임을 시작했을 때 시간 - 루프 한번 돈 시간
	int CurrentTime = DeltaTime(g_InitTime, InGameStartTime);
	TimeOutPut(CurrentTime);

	// 매 시간마다 고스트의 상태 체크
	int g_GostReleaseTime = (GetStartTime() / 1000);

	if (g_GostReleaseTime - g_GostChangeTime > 8)
	{
		sBlink.m_State = ReleaseGostState(sBlink.m_State);
		sPinky.m_State = ReleaseGostState(sPinky.m_State);
		sInky.m_State = ReleaseGostState(sInky.m_State);
		sClyde.m_State = ReleaseGostState(sClyde.m_State);
		sPacman.m_State = ReleaseGostState(sPacman.m_State);
	}

}

void DrawUnits(int posY, int posX, int dirY, int dirX, int serialNum)
{
	g_BoardArr[posY - dirY][posX - dirX] = 0;
	g_BoardArr[posY][posX] = serialNum;
}

void Process_Pacman()
{
	CursorView(false);

	if (GetAsyncKeyState(VK_LEFT) & 8001) //왼쪽
	{
		g_KeyInputChangeTime = GetStartTime();

		g_Direction = LEFT;
		EffectsPlay(1);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 8001) //오른쪽
	{
		g_KeyInputChangeTime = GetStartTime();

		g_Direction = RIGHT;
		EffectsPlay(1);
	}

	if (GetAsyncKeyState(VK_UP) & 8001) //위 
	{
		g_KeyInputChangeTime = GetStartTime();

		g_Direction = UP;
		EffectsPlay(1);
	}

	if (GetAsyncKeyState(VK_DOWN) & 8001) //아래 
	{
		g_KeyInputChangeTime = GetStartTime();

		g_Direction = DOWN;
		EffectsPlay(1);
	}

	// 키 입력 받은 후의 경과시간 
	float keyInputCurrentTime = (float)GetStartTime() - (float)g_KeyInputChangeTime;

	// 0.1초 뒤에 움직여라.
	if ((keyInputCurrentTime / 1000) > 0.1)
	{
		// 0.1초 움직인 후 다시 0.1초를 재기 위해 초기화.
		g_KeyInputChangeTime = GetStartTime();

		switch (g_Direction)
		{
		case LEFT:
			{
				if (LiftWallDetection(sPacman.m_Position.m_y, sPacman.m_Position.m_x) == true)
				{
					sPacman.m_Position.m_x--;
					// 포탈을 탄다면
					if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == 7)
					{
						sPacman.m_Position.m_y = 8;
						sPacman.m_Position.m_x = 26;

						DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 0, 25, sPacman.m_SerialNum);
					}
					else
					{
						OverlapCoin(sPacman.m_Position.m_y, sPacman.m_Position.m_x);

						if (CrashGhost() != false)
						{
							// 팩맨이 진짜로 죽었으면 함수를 빠져나오자.
							if (g_IsDie == false)
							{
								DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 0, -1, sPacman.m_SerialNum);
							}
							else
							{
								break;
							}
						}
						else
						{
							DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 0, 0, sPacman.m_SerialNum);
						}
					}
				}
			}
			break;

		case RIGHT:
			{
				if (RightWallDetection(sPacman.m_Position.m_y, sPacman.m_Position.m_x) == true)
				{
					sPacman.m_Position.m_x++;

					// 포탈을 탄다면
					if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == 7)
					{
						sPacman.m_Position.m_y = 8;
						sPacman.m_Position.m_x = 1;

						DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 0, -25, sPacman.m_SerialNum);
					}
					else
					{
						OverlapCoin(sPacman.m_Position.m_y, sPacman.m_Position.m_x);

						if (CrashGhost() != false)
						{
							// 팩맨이 진짜로 죽었으면 함수를 빠져나오자.
							if (g_IsDie == false)
							{
								DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 0, 1, sPacman.m_SerialNum);
							}
							else
							{
								break;
							}
						}
						else
						{
							DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 0, 0, sPacman.m_SerialNum);
						}
					}
				}
			}
			break;
		case UP:
			{
				if (TopWallDetection(sPacman.m_Position.m_y, sPacman.m_Position.m_x) == true)
				{
					sPacman.m_Position.m_y--;
					OverlapCoin(sPacman.m_Position.m_y, sPacman.m_Position.m_x);

					if (CrashGhost() != false)
					{
						// 팩맨이 진짜로 죽었으면 함수를 빠져나오자.
						if (g_IsDie == false)
						{
							DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, -1, 0, sPacman.m_SerialNum);
						}
						else
						{
							break;
						}
					}
					else
					{
						DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 0, 0, sPacman.m_SerialNum);
					}
				}
			}
			break;
		case DOWN:
			{
				if (BottomWallDetection(sPacman.m_Position.m_y, sPacman.m_Position.m_x) == true)
				{
					sPacman.m_Position.m_y++;
					OverlapCoin(sPacman.m_Position.m_y, sPacman.m_Position.m_x);


					if (CrashGhost() != false)
					{
						// 팩맨이 진짜로 죽었으면 함수를 빠져나오자.
						if (g_IsDie == false)
						{
							DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 1, 0, sPacman.m_SerialNum);
						}
						else
						{
							break;
						}
					}
					else
					{
						DrawUnits(sPacman.m_Position.m_y, sPacman.m_Position.m_x, 0, 0, sPacman.m_SerialNum);
					}
				}
			}
			break;
		}
	}
}

void Process_Ghost()
{
	auto result = AStar_ver2(sBlink.m_Position, sPacman.m_Position, g_BoardArr);
}

#pragma region 예외처리함수
bool LiftWallDetection(int posY, int posX)
{
	if (g_BoardArr[posY][posX - 1] == -1 ||
		g_BoardArr[posY][posX - 1] == -2 ||
		g_BoardArr[posY][posX - 1] == -3 ||
		g_BoardArr[posY][posX - 1] == -4 ||
		g_BoardArr[posY][posX - 1] == -5 ||
		g_BoardArr[posY][posX - 1] == -6)
	{
		return false;
	}

	return true;
}

bool RightWallDetection(int posY, int posX)
{
	if (g_BoardArr[posY][posX + 1] == -1 ||
		g_BoardArr[posY][posX + 1] == -2 ||
		g_BoardArr[posY][posX + 1] == -3 ||
		g_BoardArr[posY][posX + 1] == -4 ||
		g_BoardArr[posY][posX + 1] == -5 ||
		g_BoardArr[posY][posX + 1] == -6)
	{
		return false;
	}

	return true;
}

bool TopWallDetection(int posY, int posX)
{
	if (g_BoardArr[posY - 1][posX] == -1 ||
		g_BoardArr[posY - 1][posX] == -2 ||
		g_BoardArr[posY - 1][posX] == -3 ||
		g_BoardArr[posY - 1][posX] == -4 ||
		g_BoardArr[posY - 1][posX] == -5 ||
		g_BoardArr[posY - 1][posX] == -6)
	{
		return false;
	}

	return true;
}

bool BottomWallDetection(int posY, int posX)
{
	if (g_BoardArr[posY + 1][posX] == -1 ||
		g_BoardArr[posY + 1][posX] == -2 ||
		g_BoardArr[posY + 1][posX] == -3 ||
		g_BoardArr[posY + 1][posX] == -4 ||
		g_BoardArr[posY + 1][posX] == -5 ||
		g_BoardArr[posY + 1][posX] == -6)
	{
		return false;
	}

	return true;
}

bool WallDetection(int posY, int posX)
{
	if (g_BoardArr[posY][posX] == -1 ||
		g_BoardArr[posY][posX] == -2 ||
		g_BoardArr[posY][posX] == -3 ||
		g_BoardArr[posY][posX] == -4 ||
		g_BoardArr[posY][posX] == -5 ||
		g_BoardArr[posY][posX] == -6)
		/*g_BoardArr[posY + 1][posX] == -7*/
	{
		return false;
	}

	return true;
}

bool GhostDetection(int posY, int posX)
{
	if (g_BoardArr[posY][posX] == 11 ||
		g_BoardArr[posY][posX] == 12 ||
		g_BoardArr[posY][posX] == 13 ||
		g_BoardArr[posY][posX] == 14)
	{
		return false;
	}

	return true;
}

#pragma endregion

void OverlapCoin(int posY, int posX)
{
	if (g_BoardArr[posY][posX] == 1)
	{
		sPacman.m_Score += 10;

		// 코인 카운드 감소
		g_CoinCount--;

		g_CopyCoinArr[posY][posX] = false;

		if (g_CoinCount == 0)
		{
			StageClear();
		}
	}
	else if (g_BoardArr[posY][posX] == 2)
	{
		sPacman.m_Score += 50;

		// 코인 카운드 감소
		g_CoinCount--;

		g_CopyCoinArr[posY][posX] = false;

		if (g_CoinCount == 0)
		{
			StageClear();
		}

		sPacman.m_State = ChangeGostState(sBlink.m_State);
		sBlink.m_State = ChangeGostState(sBlink.m_State);
		sPinky.m_State = ChangeGostState(sPinky.m_State);
		sInky.m_State = ChangeGostState(sInky.m_State);
		sClyde.m_State = ChangeGostState(sClyde.m_State);

		// 고스트가 변화가 시작된 시간
		// 시간을 재서 7초가 지난후 해제 시켜주자.
		g_GostChangeTime = (GetStartTime() / 1000);
	}
}

int ChangeGostState(int GostState)
{
	return FEARFUL;
}

int ReleaseGostState(int GostState)
{
	return NOMAL;
}

void ScoreOutput(int posY, int posX)
{
	LHLocateCursor(posY, posX);
	printf("현재 점수 : %d ", sPacman.m_Score);
}

void LifeOutput(int posY, int posX)
{
	LHLocateCursor(posY, posX);
	printf("현재 라이프 : %d", sPacman.m_Life + 1);
	//LHLocateCursor(0, 34);
	//printf("남은 코인 : %d", g_CoinCount);
}


/// <summary>
/// 스테이지 클리어 하였을때. 다음 스테이지가 없어서,,, 일단은 종료로 해둠.
/// 
/// </summary>
int StageClear()
{
	g_StateClear = true;

	return 0;
}

/// <summary>
/// 팩맨 죽었을 때 함수
/// </summary>
int Die()
{
	system("cls");
	//printf("팩맨이 죽었습니다.");
	EffectsPlay(2);
	g_IsDie = true;


	return 0;
}

/// <summary>
/// 고스트랑 충돌 시 라이프 감소, 위치 초기화
/// </summary>
int CrashGhost()
{
	// 고스트 상태가 Nomal이면
	if (sPacman.m_State == NOMAL)
	{
		// 고스트들에게 잡힘
		if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sBlink.m_Position.m_y][sBlink.m_Position.m_x] ||
			g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sPinky.m_Position.m_y][sPinky.m_Position.m_x] ||
			g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sInky.m_Position.m_y][sInky.m_Position.m_x] ||
			g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sClyde.m_Position.m_y][sClyde.m_Position.m_x])
		{
			if (0 <= sPacman.m_Life)
			{
				if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == BLINK)
				{
					sPacman.m_Life--;

					IsDead();
					sPacman.m_Position.m_x = 13;
					sPacman.m_Position.m_y = 29;

					return false;
				}
				else if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == PINKY)
				{

					sPacman.m_Life--;

					IsDead();
					sPacman.m_Position.m_x = 13;
					sPacman.m_Position.m_y = 29;

					return false;
				}
				else if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == INKY)
				{
					sPacman.m_Life--;

					IsDead();
					sPacman.m_Position.m_x = 13;
					sPacman.m_Position.m_y = 29;

					return false;
				}
				else if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == CLYDE)
				{
					sPacman.m_Life--;

					IsDead();
					sPacman.m_Position.m_x = 13;
					sPacman.m_Position.m_y = 29;

					return false;
				}
			}
			else
			{
				// 몬스터에게 잡힘
				/// 게임 오버로 이동해야함.
				Die();
			}
		}
	}
	else // 고스트 상태가 FEARFUL 이면
	{
		if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sBlink.m_Position.m_y][sBlink.m_Position.m_x])
		{
			// 고스트를 잡음
			sPacman.m_Score += 200;

			CreateBlink();

			return true;
		}
		else if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sPinky.m_Position.m_y][sPinky.m_Position.m_x])
		{
			// 고스트를 잡음
			sPacman.m_Score += 200;

			CreatePinky();

			return true;
		}
		else if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sInky.m_Position.m_y][sInky.m_Position.m_x])
		{
			// 고스트를 잡음
			sPacman.m_Score += 200;

			CreateInky();

			return true;
		}
		else if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sClyde.m_Position.m_y][sClyde.m_Position.m_x])
		{
			// 고스트를 잡음
			sPacman.m_Score += 200;

			CreateClyde();

			return true;
		}
	}
	return true;
}

void IsDead()
{
	for (int i = 0; i < HIGH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (g_BoardArr[i][j] == PACMAN)
			{
				g_BoardArr[i][j] = 0;

				break;
			}
		}
	}
}

bool AStar(SPOSITION blink, SPOSITION pacman, int(*boardArr)[28])
{
	if (IsDestination(blink.m_y, blink.m_x, pacman)) return false; // 이미 잡아먹힘. 조사할 필요 X

	std::priority_queue<Node> _openList;
	bool g_CloseList[HIGH][WIDTH] = { 0, }; // 최단거리를 담는 벡터 

	// 계산된 거리를 넣을 배열 초기화 
	std::vector<vector<Node>> _mapNode(HIGH, std::vector<Node>(WIDTH));

	for (int i = 0; i < HIGH; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			_mapNode[i][j].F = _mapNode[i][j].G = _mapNode[i][j].H = INF;

			_mapNode[i][j].parentPos = { -1, -1 };
		}
	}

	// 시작점의 정보를 node에 넣어줌. 
	const int _srtY = blink.m_y;
	const int _srtX = blink.m_x;

	_mapNode[_srtY][_srtX].F = _mapNode[_srtY][_srtX].G = _mapNode[_srtY][_srtX].H = 0.0f;
	_mapNode[_srtY][_srtX].myPos = blink;
	_mapNode[_srtY][_srtX].parentPos = { _srtX, _srtY }; // 부모 없음.  

	_openList.push(_mapNode[_srtY][_srtX]); // start node를 openList에 넣음. 

	while (!_openList.empty()) // openlist가 없을때까지 
	{
		// 1. _openList 중 H값이 가장 작은 node을 꺼냄. 
		// 2. 꺼낸 node를 closeNode에 표시. 
		// 3. 꺼낸 node의 4방향을 검사 -> _openList push
		// 4. 최단거리를 구할때까지 반복

		Node temp = _openList.top();
		_openList.pop();

		g_CloseList[temp.myPos.m_y][temp.myPos.m_x] = true; // 한번 갔다고 표시 

		for (int i = 0; i < 4; ++i) // closeList 표시된 node의 4방향 검사. 
		{
			const int _ny = temp.myPos.m_y + dy[i];
			const int _nx = temp.myPos.m_x + dx[i];

			if (WallDetection(_ny, _nx) && !g_CloseList[_ny][_nx]) // 맵을 벗어났는가? 길인/가? // 한번도 간적 없는 길인가?
			{
				// 현재지점 -> 도착지점까지의 예측값
				const auto _parentNode = _mapNode[temp.myPos.m_y][temp.myPos.m_x];

				const float _tempG = _parentNode.G + 1.0f;
				const float _tempH = GetHeuristic(_ny, _nx, pacman.m_y, pacman.m_x);
				const float _tempF = _tempG + _tempH;

				if (_tempF < _mapNode[_ny][_nx].F) // 검사한 적은 있거나 없고, 현재 F값이 작다면?
				{
					Node newNode{};

					newNode.G = _tempG;
					newNode.H = _tempH;
					newNode.F = _tempF;

					newNode.myPos = { _ny, _nx };
					newNode.parentPos = { temp.myPos };

					_openList.push(newNode);
					_mapNode[_ny][_nx] = newNode;
				}
				else if (IsDestination(_ny, _nx, pacman)) // 도착했다면? 
				{
					g_CloseList[_ny][_nx] = true;
					return true;
				}
			}
		}
	}

	return false;
}

SPOSITION AStar_ver2(SPOSITION start, SPOSITION end, int(*boardArr)[28])
{
	bool visitMap[HIGH][WIDTH] = { 0, };
	vector<Node> g_closeList;
	priority_queue<Node> g_openList;

	Node startCell;

	startCell.G = 0;
	startCell.H = 0;
	startCell.F = 0;

	startCell.myPos = start;

	startCell.parentPos.m_x = -1;
	startCell.parentPos.m_y = -1;

	//startCell.parentCell = nullptr;

	visitMap[start.m_y][start.m_x] = true;

	// 시작 노드를 closeList 넣어준다.
	g_closeList.push_back(startCell);

	bool Finding = true;

	while (Finding)
	{
		const auto _cell = g_closeList.at(g_closeList.size() - 1);

		// 시작점과 연결된 노드들을 openList에 넣어준다.
		//FindNodePush(board, _cell.myPos, end);

		for (int i = 0; i < 4; ++i)
		{
			const int _y = _cell.myPos.m_y + dy[i];
			const int _x = _cell.myPos.m_x + dx[i];

			if (_y == end.m_y && _x == end.m_x) // 찾았다. 
			{
				Finding = false;
				break;
			}

			// 배열의 범위를 벗어난다면 넘김. 
			if (!WallDetection(_y, _x) && !GhostDetection(_y, _x) && visitMap[_y][_x]) continue;

			// 연결된 node라면 openList에 넣기.
			const auto parent = g_closeList[g_closeList.size() - 1];

			Node newCell{};

			newCell.G = parent.G + 1; // 배열이기때문에 한칸씩 이동
			newCell.H = GetHeuristic(_y, _x, end.m_y, end.m_x); // 피타고라스 정리를 통해 거리 추정값 계산
			newCell.F = newCell.G + newCell.H; // 거리 합산. 

			newCell.myPos.m_x = _x;
			newCell.myPos.m_y = _y;

			newCell.parentPos.m_x = _cell.myPos.m_x;
			newCell.parentPos.m_x = _cell.myPos.m_y;

			//newCell.parentCell = &(g_closeList[g_closeList.size() - 1]);

			g_openList.push(newCell);
		}

		if (Finding == false) break; // 찾았다면 while문 탈출.

		// 우선순위 큐의 탑을 close에 넣어줌. 이유? 거리가 제일 짧다고 판단되었기 때문.
		auto _tmpCell = g_openList.top();
		g_closeList.push_back(_tmpCell);
		visitMap[_tmpCell.myPos.m_y][_tmpCell.myPos.m_x] = true;
		g_openList.pop();
	}

	const auto predictPos = g_closeList.at(g_closeList.size() - 1).myPos; 

	return predictPos;
}

bool IsDestination(int posY, int posX, SPOSITION end)
{
	if (posY == end.m_y && posX == end.m_x) return true;

	return false;
}

float GetHeuristic(int nowY, int nowX, int endY, int endX)
{
	const int _y = endY - nowY;
	const int _x = endX - nowX;

	// 피타고라스의 정리를 통해 heuristic 값 도출.
	return static_cast<float>(sqrt((nowY * nowY) + (nowX * nowX)));
}
