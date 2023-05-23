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
	BLINK, // 빨강
	PINKY, // 핑크
	INKY,  // 블루
	CLYDE  // 오렌지? 노랑 ?
};

enum e_State
{
	NOMAL = 20,
	FEARFUL
};

/// 필요한 변수들

extern bool g_IsDie;
extern bool g_StateClear;

// A-star에 필요한 변수
struct Node
{
	float F;	// G + H
	float G;	// 시작점 -> 현재점 거리
	float H;	// 현재점 -> 도착점 거리(추측값)

	SPOSITION myPos; 
	SPOSITION parentPos;

	bool operator < (const Node& i) const { return i.F < F; }
};

// coin 유무 배열 init
void CopyCoinInit();

// 보드에 집어넣기
void BoredInitialize();

// 팩맨 과 고스트 초기화
void PlayerInit();
void CreatePacman();
void CreateBlink();
void CreatePinky();
void CreateInky();
void CreateClyde();

// Coint 넣는 함수 
void PushCoin();

// Bored에 올려진 모든 것 그리기
void DrawBoard();

// bored 다시 그리기
void DrawUnits(int posY, int posX, int dirY, int dirX, int serialNum);

// 객체 처리 함수(키 입력, 이동, 벽 체크 등)
void Process_Pacman();
void Process_Ghost();

/// 벽 예외처리 함수
// 왼쪽벽 통과 금지
bool LiftWallDetection(int posY, int posX);
// 오른쪽벽 통과 금지
bool RightWallDetection(int posY, int posX);
// 위쪽벽 통과 금지
bool TopWallDetection(int posY, int posX);
// 아래벽 통과 금지
bool BottomWallDetection(int posY, int posX);

bool WallDetection(int posY, int posX);
// 고스트가 있는지 피하자. 
bool GhostDetection(int posY, int posX);

// 코인 먹으면 score + 10
void OverlapCoin(int posY, int posX);

// 큰 코인을 먹으면 고스트 상태 변화
int ChangeGostState(int GostState);

// 바뀐 고스트 변화 해제
int ReleaseGostState(int GostState);

// 스코어 점수 출력
void ScoreOutput(int posY, int posX);

// 게임 종료 
int StageClear();

// 라이프 출력
void LifeOutput(int posY, int posX);

int Die();

// 고스트와 플레이어 충돌
int CrashGhost();

// 팩맨이 죽었는지 확인
void IsDead();

/// A-star에 필요한 함수들
// 블링키 길찾기 알고리즘 A*
// 시작점 : 블링크 위치 / 도착점 : 팩맨 위치 
bool AStar(SPOSITION blink, SPOSITION pacman, int (*boardArr)[28]); 
SPOSITION AStar_ver2(SPOSITION start, SPOSITION end, int (*boardArr)[28]); 

bool IsDestination(int posY, int posX, SPOSITION end); // 도착여뷰

float GetHeuristic(int nowY, int nowX, int endY, int endX); // heuristic값 추출