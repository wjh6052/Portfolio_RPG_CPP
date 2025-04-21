#include "CCharacter_Boss.h"
#include "../../../Global.h"
#include "../../../Datas/DA/DA_MapIcon.h"


#include "PaperSpriteComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/DecalComponent.h"


ACCharacter_Boss::ACCharacter_Boss()
{
	// StatComp를 위한 캐릭터 태그
	CharacterType = ECharacterType::Boss;

	CHelpers::CreateActorComponent(this, &AttackRangeDecal, "AttackRangeDecal");

	AttackRangeDecal->SetupAttachment(RootComponent);
	AttackRangeDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f)); // 바닥 향하도록 회전

	AttackRangeDecal->SetVisibility(false);



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

	// 쿨타임 설정
	//CurrentSkillCooldownArr = SkillCooldownArr;
}

void ACCharacter_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0;  i < CurrentSkillCooldownArr.Num(); i++)
	{
		if(CurrentSkillCooldownArr[i] > 0)
			CurrentSkillCooldownArr[i] -= DeltaTime;
		CLog::Print(CurrentSkillCooldownArr[i], i);
	}


}

void ACCharacter_Boss::SetAttackRangeDecalSize(FVector InDecalSize)
{
	FVector temp;
	temp.X = InDecalSize.Z;
	temp.Y = InDecalSize.Y;
	temp.Z = InDecalSize.X;


	DecalSize = InDecalSize;
	AttackRangeDecal->DecalSize = temp;
}
