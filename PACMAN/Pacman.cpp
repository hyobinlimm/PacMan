#include "Pacman.h"

#include "Hydra_Engine.h"
#include "Hydra_Time.h"
#include "Sound.h"

#include <queue>


/// <summary>
/// -1 = "��", -2 = "��", -3 = "��", -4 = "��", -5 = "��", -6 = "��", -7 = ��Ʈ �� �Ա�
///  1 = ����, 2 = ��Ʈ �ٲٴ� ����,  7 = ���� 
/// 10 = �Ѹ�, 11~14 = ��Ʈ
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

// ���� ���� = 10; ū ���� = 50;
// ��Ʈ�� ������ 200��(�������� ������ x2)

// �Ѹ� �� ��Ʈ 
SPLAYER sPacman;
SPLAYER sBlink;
SPLAYER sPinky;
SPLAYER sInky;
SPLAYER sClyde;

int g_Direction = IDLE;

bool g_IsDie = false; // �׾����� �˻� 

bool g_StateClear = false; // Ŭ���� ����

int g_BoardArr[HIGH][WIDTH]; // = �� + ���� 

int g_CoinCount = 0; // �Ѹ� ���� ���� ī��Ʈ 

// ������ ���� �ð�
int g_GostChangeTime = 0;

// Ű �Է� ���� �ð�
int g_KeyInputChangeTime = 0;

// coin ���� �迭
BOOL g_CopyCoinArr[HIGH][WIDTH];

// ���� �ð�
unsigned int g_InitTime = 0;

int dx[4] = { 0, 0, -1, +1 }; // �� �� �� �� 
int dy[4] = { -1, +1, 0, 0 }; // �� �� �� ��

// ���� ó�� ���۽� coin �ʱ�ȭ
void CopyCoinInit()
{
	for (int i = 0; i < HIGH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (g_CoinArr[i][j] == 1 || g_CoinArr[i][j] == 2)
			{
				g_CopyCoinArr[i][j] = true;

				// �ʿ� �ѷ��� ���� �� ����
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

	// ���� ���¿� �Ѹ� ���� �ʱ�ȭ
	g_Direction = IDLE;

	g_IsDie = false;
	g_StateClear = false;

	g_CoinCount = 321;

	// ������ ���� �ð�
	g_GostChangeTime = 0;

	// Ű �Է� ���� �ð�
	g_KeyInputChangeTime = 0;

	g_InitTime = 0;

	PushCoin();

	PlayerInit();

	// ���� ������ �� �ð� 0���� �ʱ�ȭ
	g_InitTime = GetStartTime();
}

#pragma region ĳ���� �ʱ�ȭ

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
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -2)
			{
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -3)
			{
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -4)
			{
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -5)
			{
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -6)
			{
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
			}
			else if (g_BoardArr[y][x] == -7)
			{
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_WHITE);
			}
			else if (g_BoardArr[y][x] == 1)
			{
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_YELLOW);
			}
			else if (g_BoardArr[y][x] == 2)
			{
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_YELLOW);
			}
			else if (g_BoardArr[y][x] == 10)
			{
				LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_YELLOW);
			}
			else if (g_BoardArr[y][x] == 11)
			{
				if (sBlink.m_State == NOMAL)
				{
					LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_RED);
				}
				else
				{
					LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
				}

			}
			else if (g_BoardArr[y][x] == 12)
			{
				if (sPinky.m_State == NOMAL)
				{
					LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_PINK);
				}
				else
				{
					LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
				}
			}
			else if (g_BoardArr[y][x] == 13)
			{
				if (sInky.m_State == NOMAL)
				{
					LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_AQUA);
				}
				else
				{
					LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
				}
			}
			else if (g_BoardArr[y][x] == 14)
			{
				if (sClyde.m_State == NOMAL)
				{
					LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_GREEN);
				}
				else
				{
					LHPutAttrCharEx(x * 2, y, "��", BG_BLACK, FG_BLUE);
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

	// ������ �ѹ� ������ �� �ð�
	unsigned int InGameStartTime = SetEndTime();

	// ó�� ������ �������� �� �ð� - ���� �ѹ� �� �ð�
	int CurrentTime = DeltaTime(g_InitTime, InGameStartTime);
	TimeOutPut(CurrentTime);

	// �� �ð����� ��Ʈ�� ���� üũ
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

	if (GetAsyncKeyState(VK_LEFT) & 8001) //����
	{
		g_KeyInputChangeTime = GetStartTime();

		g_Direction = LEFT;
		EffectsPlay(1);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 8001) //������
	{
		g_KeyInputChangeTime = GetStartTime();

		g_Direction = RIGHT;
		EffectsPlay(1);
	}

	if (GetAsyncKeyState(VK_UP) & 8001) //�� 
	{
		g_KeyInputChangeTime = GetStartTime();

		g_Direction = UP;
		EffectsPlay(1);
	}

	if (GetAsyncKeyState(VK_DOWN) & 8001) //�Ʒ� 
	{
		g_KeyInputChangeTime = GetStartTime();

		g_Direction = DOWN;
		EffectsPlay(1);
	}

	// Ű �Է� ���� ���� ����ð� 
	float keyInputCurrentTime = (float)GetStartTime() - (float)g_KeyInputChangeTime;

	// 0.1�� �ڿ� ��������.
	if ((keyInputCurrentTime / 1000) > 0.1)
	{
		// 0.1�� ������ �� �ٽ� 0.1�ʸ� ��� ���� �ʱ�ȭ.
		g_KeyInputChangeTime = GetStartTime();

		switch (g_Direction)
		{
		case LEFT:
			{
				if (LiftWallDetection(sPacman.m_Position.m_y, sPacman.m_Position.m_x) == true)
				{
					sPacman.m_Position.m_x--;
					// ��Ż�� ź�ٸ�
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
							// �Ѹ��� ��¥�� �׾����� �Լ��� ����������.
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

					// ��Ż�� ź�ٸ�
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
							// �Ѹ��� ��¥�� �׾����� �Լ��� ����������.
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
						// �Ѹ��� ��¥�� �׾����� �Լ��� ����������.
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
						// �Ѹ��� ��¥�� �׾����� �Լ��� ����������.
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

#pragma region ����ó���Լ�
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

		// ���� ī��� ����
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

		// ���� ī��� ����
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

		// ��Ʈ�� ��ȭ�� ���۵� �ð�
		// �ð��� �缭 7�ʰ� ������ ���� ��������.
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
	printf("���� ���� : %d ", sPacman.m_Score);
}

void LifeOutput(int posY, int posX)
{
	LHLocateCursor(posY, posX);
	printf("���� ������ : %d", sPacman.m_Life + 1);
	//LHLocateCursor(0, 34);
	//printf("���� ���� : %d", g_CoinCount);
}


/// <summary>
/// �������� Ŭ���� �Ͽ�����. ���� ���������� ���,,, �ϴ��� ����� �ص�.
/// 
/// </summary>
int StageClear()
{
	g_StateClear = true;

	return 0;
}

/// <summary>
/// �Ѹ� �׾��� �� �Լ�
/// </summary>
int Die()
{
	system("cls");
	//printf("�Ѹ��� �׾����ϴ�.");
	EffectsPlay(2);
	g_IsDie = true;


	return 0;
}

/// <summary>
/// ��Ʈ�� �浹 �� ������ ����, ��ġ �ʱ�ȭ
/// </summary>
int CrashGhost()
{
	// ��Ʈ ���°� Nomal�̸�
	if (sPacman.m_State == NOMAL)
	{
		// ��Ʈ�鿡�� ����
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
				// ���Ϳ��� ����
				/// ���� ������ �̵��ؾ���.
				Die();
			}
		}
	}
	else // ��Ʈ ���°� FEARFUL �̸�
	{
		if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sBlink.m_Position.m_y][sBlink.m_Position.m_x])
		{
			// ��Ʈ�� ����
			sPacman.m_Score += 200;

			CreateBlink();

			return true;
		}
		else if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sPinky.m_Position.m_y][sPinky.m_Position.m_x])
		{
			// ��Ʈ�� ����
			sPacman.m_Score += 200;

			CreatePinky();

			return true;
		}
		else if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sInky.m_Position.m_y][sInky.m_Position.m_x])
		{
			// ��Ʈ�� ����
			sPacman.m_Score += 200;

			CreateInky();

			return true;
		}
		else if (g_BoardArr[sPacman.m_Position.m_y][sPacman.m_Position.m_x] == g_BoardArr[sClyde.m_Position.m_y][sClyde.m_Position.m_x])
		{
			// ��Ʈ�� ����
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
	if (IsDestination(blink.m_y, blink.m_x, pacman)) return false; // �̹� ��Ƹ���. ������ �ʿ� X

	std::priority_queue<Node> _openList;
	bool g_CloseList[HIGH][WIDTH] = { 0, }; // �ִܰŸ��� ��� ���� 

	// ���� �Ÿ��� ���� �迭 �ʱ�ȭ 
	std::vector<vector<Node>> _mapNode(HIGH, std::vector<Node>(WIDTH));

	for (int i = 0; i < HIGH; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			_mapNode[i][j].F = _mapNode[i][j].G = _mapNode[i][j].H = INF;

			_mapNode[i][j].parentPos = { -1, -1 };
		}
	}

	// �������� ������ node�� �־���. 
	const int _srtY = blink.m_y;
	const int _srtX = blink.m_x;

	_mapNode[_srtY][_srtX].F = _mapNode[_srtY][_srtX].G = _mapNode[_srtY][_srtX].H = 0.0f;
	_mapNode[_srtY][_srtX].myPos = blink;
	_mapNode[_srtY][_srtX].parentPos = { _srtX, _srtY }; // �θ� ����.  

	_openList.push(_mapNode[_srtY][_srtX]); // start node�� openList�� ����. 

	while (!_openList.empty()) // openlist�� ���������� 
	{
		// 1. _openList �� H���� ���� ���� node�� ����. 
		// 2. ���� node�� closeNode�� ǥ��. 
		// 3. ���� node�� 4������ �˻� -> _openList push
		// 4. �ִܰŸ��� ���Ҷ����� �ݺ�

		Node temp = _openList.top();
		_openList.pop();

		g_CloseList[temp.myPos.m_y][temp.myPos.m_x] = true; // �ѹ� ���ٰ� ǥ�� 

		for (int i = 0; i < 4; ++i) // closeList ǥ�õ� node�� 4���� �˻�. 
		{
			const int _ny = temp.myPos.m_y + dy[i];
			const int _nx = temp.myPos.m_x + dx[i];

			if (WallDetection(_ny, _nx) && !g_CloseList[_ny][_nx]) // ���� ����°�? ����/��? // �ѹ��� ���� ���� ���ΰ�?
			{
				// �������� -> �������������� ������
				const auto _parentNode = _mapNode[temp.myPos.m_y][temp.myPos.m_x];

				const float _tempG = _parentNode.G + 1.0f;
				const float _tempH = GetHeuristic(_ny, _nx, pacman.m_y, pacman.m_x);
				const float _tempF = _tempG + _tempH;

				if (_tempF < _mapNode[_ny][_nx].F) // �˻��� ���� �ְų� ����, ���� F���� �۴ٸ�?
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
				else if (IsDestination(_ny, _nx, pacman)) // �����ߴٸ�? 
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

	// ���� ��带 closeList �־��ش�.
	g_closeList.push_back(startCell);

	bool Finding = true;

	while (Finding)
	{
		const auto _cell = g_closeList.at(g_closeList.size() - 1);

		// �������� ����� ������ openList�� �־��ش�.
		//FindNodePush(board, _cell.myPos, end);

		for (int i = 0; i < 4; ++i)
		{
			const int _y = _cell.myPos.m_y + dy[i];
			const int _x = _cell.myPos.m_x + dx[i];

			if (_y == end.m_y && _x == end.m_x) // ã�Ҵ�. 
			{
				Finding = false;
				break;
			}

			// �迭�� ������ ����ٸ� �ѱ�. 
			if (!WallDetection(_y, _x) && !GhostDetection(_y, _x) && visitMap[_y][_x]) continue;

			// ����� node��� openList�� �ֱ�.
			const auto parent = g_closeList[g_closeList.size() - 1];

			Node newCell{};

			newCell.G = parent.G + 1; // �迭�̱⶧���� ��ĭ�� �̵�
			newCell.H = GetHeuristic(_y, _x, end.m_y, end.m_x); // ��Ÿ��� ������ ���� �Ÿ� ������ ���
			newCell.F = newCell.G + newCell.H; // �Ÿ� �ջ�. 

			newCell.myPos.m_x = _x;
			newCell.myPos.m_y = _y;

			newCell.parentPos.m_x = _cell.myPos.m_x;
			newCell.parentPos.m_x = _cell.myPos.m_y;

			//newCell.parentCell = &(g_closeList[g_closeList.size() - 1]);

			g_openList.push(newCell);
		}

		if (Finding == false) break; // ã�Ҵٸ� while�� Ż��.

		// �켱���� ť�� ž�� close�� �־���. ����? �Ÿ��� ���� ª�ٰ� �ǴܵǾ��� ����.
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

	// ��Ÿ����� ������ ���� heuristic �� ����.
	return static_cast<float>(sqrt((nowY * nowY) + (nowX * nowX)));
}
