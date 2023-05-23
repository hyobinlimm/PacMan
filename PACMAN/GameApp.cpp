#include "GameApp.h"
#include "Hydra_Engine.h"
#include "Pacman.h"
#include "GameManager.h"
#include "Sound.h"
#include "algorithm"

using namespace std;

enum Scene
{
	TITLE,
	GAMESTART,
	GAMEEXIT,
	GAMESUCCESS,
	GAMEOVER,
};

int g_GameState = TITLE;

int Init()
{
	/// 게임 시작 할때 필요한 초기화 함수들 

	// 화면 고정
	set_screen_size(60, 40);

	// 교수님 함수 쓰기 위한 핸들 받아오기
	if (Initialize() == FALSE)
	{
		return 0;
	}

	return true; 
}

void GameInit()
{
	// 사운드 초기화
	SoundSystem();

	// 코인 개수 확인
	CopyCoinInit();

	// 게임 보드 및 게임에 필요한 모든 조건 초기화
	BoredInitialize();
}

void GameLoop()
{
	while (true)
	{
		GameScene();
	}
}

void GameScene()
{
	switch (g_GameState)
	{
		case TITLE:
			{
				// 화면 음악
				/*BgmPlay(0);*/

				// 타이틀만 그린다.
				TitleDraw();

				// 메뉴를 선택한다.
				int selecnum = MenuDraw();

				g_GameState = selecnum;
			}
			break;

		case GAMESTART:
			{
				system("cls");

				GameInit();

				BgmPlay(0);

				while (true)
				{
					DrawBoard();
					Process_Pacman();
					Process_Ghost();

					/// 고스트가 있었던 자리

					// 여기서 캐릭터들의 위치 체크

					if (g_IsDie == true)
					{
						g_GameState = GAMEOVER;
						break;
					}

					if (g_StateClear == true)
					{
						g_GameState = GAMESUCCESS;
						break;
					}
				}
			}
			break;
		case GAMEEXIT:
			{
				system("cls");
				//printf("게임을 종료합니다.");

				exit(0);
			}
			break;
		case GAMESUCCESS:
			{
				system("cls");

				printf("스테이지를 클리어하였습니다.!");

				sleep(3000);

				g_GameState = GAMESTART;
				system("cls");
			}
			break;
		case GAMEOVER:
			{
				GameOver();
				g_GameState = TITLE;

				system("cls");
			}
			break;

	}
}
