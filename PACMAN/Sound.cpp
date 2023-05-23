#include<iostream>
#include "Sound.h"

using namespace std;
using namespace FMOD;
System* pSystem;
Sound* pSound[6];
Channel* pChannel[1];
Channel* pBgmChannel[1];
/// <summary>
/// ����� : ����ȯ
/// ���� FMOD ���
/// 
/// </summary>

//���� �ý��� �Լ�
void SoundSystem()
{
	System_Create(&pSystem);

	pSystem->init(4, FMOD_INIT_NORMAL, NULL);

	pSystem->createSound("pacman_beginning.wav", FMOD_DEFAULT, NULL, &pSound[0]);
	pSystem->createSound("pacman_chomp.wav", FMOD_DEFAULT, NULL, &pSound[1]);
	pSystem->createSound("pacman_death2.wav", FMOD_DEFAULT, NULL, &pSound[2]);
	/*pSystem->createSound("pacman_beginning.wav", FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &pSound[0]);*/
}
//����Effects �÷���
void EffectsPlay(int Sound_num)
{
	pSystem->playSound(pSound[Sound_num], NULL, 0, pChannel);
}
//����BgmPlay �÷���
void BgmPlay(int Sound_num)
{
	pSystem->playSound(pSound[Sound_num], NULL, 0, pBgmChannel);
}

void Exit()
{
	pSystem->release();
	pSystem->close();
}