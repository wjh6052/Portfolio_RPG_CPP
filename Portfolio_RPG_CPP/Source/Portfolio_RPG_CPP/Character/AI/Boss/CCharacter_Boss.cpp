#include "CCharacter_Boss.h"
#include "../../../Global.h"
#include "../../../Datas/DA/DA_MapIcon.h"


#include "PaperSpriteComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/DecalComponent.h"


ACCharacter_Boss::ACCharacter_Boss()
{
	// StatComp�� ���� ĳ���� �±�
	CharacterType = ECharacterType::Boss;

	CHelpers::CreateActorComponent(this, &AttackRangeDecal, "AttackRangeDecal");

	AttackRangeDecal->SetupAttachment(RootComponent);
	AttackRangeDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f)); // �ٴ� ���ϵ��� ȸ��

	AttackRangeDecal->SetVisibility(false);



	AINameWidget->SetVisibility(false);
}

void ACCharacter_Boss::BeginPlay()
{
	Super::BeginPlay();


	// �ʿ� ǥ�õ� ������ ����
	if (CGameInstance->MapIcon_DA != nullptr)
	{
		MapIconComponent->SetSprite(CGameInstance->MapIcon_DA->Boss_Sprite);
	}

	// ��Ÿ�� ����
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
