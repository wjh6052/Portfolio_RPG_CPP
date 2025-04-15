#include "CCharacter_Boss.h"
#include "../../../Datas/DA/DA_MapIcon.h"


#include "PaperSpriteComponent.h"
#include "Components/WidgetComponent.h"



ACCharacter_Boss::ACCharacter_Boss()
{
	// StatComp를 위한 캐릭터 태그
	CharacterType = ECharacterType::Boss;

	AINameWidget->SetVisibility(false);
}

void ACCharacter_Boss::BeginPlay()
{
	Super::BeginPlay();


	// 맵에 표시될 아이콘 설정
	if (CGameInstance->MapIcon_DA != nullptr)
	{
		MapIconComponent->SetSprite(CGameInstance->MapIcon_DA->Boss_Sprite);
	}
}