#include "CCharacter_Boss.h"
#include "../../../Datas/DA/DA_MapIcon.h"


#include "PaperSpriteComponent.h"



void ACCharacter_Boss::BeginPlay()
{
	Super::BeginPlay();


	// �ʿ� ǥ�õ� ������ ����
	if (CGameInstance->MapIcon_DA != nullptr)
	{
		MapIconComponent->SetSprite(CGameInstance->MapIcon_DA->Boss_Sprite);
	}
}