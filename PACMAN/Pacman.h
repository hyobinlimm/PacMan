#pragma once
#include <windows.h>

using namespace std; 

#define WIDTH 28
#define HIGH 31
#define INF 1e9

enum e_Direction
{
	IDLE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct SPOSITION
{
	int m_x;
	int m_y;
};

struct SPLAYER
{
	int m_SerialNum;

	int m_State;
	
	SPOSITION m_Position;

	int m_Life;
	int m_Score;

};

enum e_Units
{
	PACMAN = 10,
	BLINK, // ����
	PINKY, // ��ũ
	INKY,  // ���
	CLYDE  // ������? ��� ?
};

enum e_State
{
	NOMAL = 20,
	FEARFUL
};

/// �ʿ��� ������

extern bool g_IsDie;
extern bool g_StateClear;

// A-star�� �ʿ��� ����
struct Node
{
	float F;	// G + H
	float G;	// ������ -> ������ �Ÿ�
	float H;	// ������ -> ������ �Ÿ�(������)

	SPOSITION myPos; 
	SPOSITION parentPos;

	bool operator < (const Node& i) const { return i.F < F; }
};

// coin ���� �迭 init
void CopyCoinInit();

// ���忡 ����ֱ�
void BoredInitialize();

// �Ѹ� �� ��Ʈ �ʱ�ȭ
void PlayerInit();
void CreatePacman();
void CreateBlink();
void CreatePinky();
void CreateInky();
void CreateClyde();

// Coint �ִ� �Լ� 
void PushCoin();

// Bored�� �÷��� ��� �� �׸���
void DrawBoard();

// bored �ٽ� �׸���
void DrawUnits(int posY, int posX, int dirY, int dirX, int serialNum);

// ��ü ó�� �Լ�(Ű �Է�, �̵�, �� üũ ��)
void Process_Pacman();
void Process_Ghost();

/// �� ����ó�� �Լ�
// ���ʺ� ��� ����
bool LiftWallDetection(int posY, int posX);
// �����ʺ� ��� ����
bool RightWallDetection(int posY, int posX);
// ���ʺ� ��� ����
bool TopWallDetection(int posY, int posX);
// �Ʒ��� ��� ����
bool BottomWallDetection(int posY, int posX);

bool WallDetection(int posY, int posX);
// ��Ʈ�� �ִ��� ������. 
bool GhostDetection(int posY, int posX);

// ���� ������ score + 10
void OverlapCoin(int posY, int posX);

// ū ������ ������ ��Ʈ ���� ��ȭ
int ChangeGostState(int GostState);

// �ٲ� ��Ʈ ��ȭ ����
int ReleaseGostState(int GostState);

// ���ھ� ���� ���
void ScoreOutput(int posY, int posX);

// ���� ���� 
int StageClear();

// ������ ���
void LifeOutput(int posY, int posX);

int Die();

// ��Ʈ�� �÷��̾� �浹
int CrashGhost();

// �Ѹ��� �׾����� Ȯ��
void IsDead();

/// A-star�� �ʿ��� �Լ���
// ��Ű ��ã�� �˰��� A*
// ������ : ��ũ ��ġ / ������ : �Ѹ� ��ġ 
bool AStar(SPOSITION blink, SPOSITION pacman, int (*boardArr)[28]); 
SPOSITION AStar_ver2(SPOSITION start, SPOSITION end, int (*boardArr)[28]); 

bool IsDestination(int posY, int posX, SPOSITION end); // ��������

float GetHeuristic(int nowY, int nowX, int endY, int endX); // heuristic�� ����