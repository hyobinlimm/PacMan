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
	/// ���� ���� �Ҷ� �ʿ��� �ʱ�ȭ �Լ��� 

	// ȭ�� ����
	set_screen_size(60, 40);

	// ������ �Լ� ���� ���� �ڵ� �޾ƿ���
	if (Initialize() == FALSE)
	{
		return 0;
	}

	return true; 
}

void GameInit()
{
	// ���� �ʱ�ȭ
	SoundSystem();

	// ���� ���� Ȯ��
	CopyCoinInit();

	// ���� ���� �� ���ӿ� �ʿ��� ��� ���� �ʱ�ȭ
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
				// ȭ�� ����
				/*BgmPlay(0);*/

				// Ÿ��Ʋ�� �׸���.
				TitleDraw();

				// �޴��� �����Ѵ�.
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

					/// ��Ʈ�� �־��� �ڸ�

					// ���⼭ ĳ���͵��� ��ġ üũ

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
				//printf("������ �����մϴ�.");

				exit(0);
			}
			break;
		case GAMESUCCESS:
			{
				system("cls");

				printf("���������� Ŭ�����Ͽ����ϴ�.!");

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
