#include <stdio.h>
#include "Hydra_Engine.h"
#include "GameApp.h"
#include "Hydra_Time.h"
#include "GameManager.h"
#include "Pacman.h"

// enum 값으로 씬 관리 ?

int main()
{
	// 초기화
	Init();

	// 게임 진행
	GameLoop();

	return 0;
}


