#include "CCharacter_Enemy.h"
#include "../../../Global.h"
#include "../../../AnimInstance/CAnimInstance_Base.h"
#include "../../../Widgets/EnemyUI/CW_EnemyHpBar.h"
#include "../../../Datas/DA/DA_MapIcon.h"


#include "Components/WidgetComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"



ACCharacter_Enemy::ACCharacter_Enemy()
{
	// StatComp를 위한 캐릭터 태그
	CharacterType = ECharacterType::Enemy;

	TSubclassOf<UCAnimInstance_Base> animInstanceClass;
	CHelpers::GetClass<UCAnimInstance_Base>(&animInstanceClass, "AnimBlueprint'/Game/AnimInstance/Enemy/ABP_Enemy_Mannequins'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);


	CHelpers::CreateSceneComponent<UWidgetComponent>(this, &HPBarWidget, "HPBarWidget", RootComponent);

	TSubclassOf<class UCW_EnemyHpBar> enemyHpBar_Class;
	CHelpers::GetClass<UCW_EnemyHpBar>(&enemyHpBar_Class, "WidgetBlueprint'/Game/Widgets/EnemyUI/CWB_EnemyHpBar'");
	 
	HPBarWidget->SetWidgetClass(enemyHpBar_Class);

	HPBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 150.f));

}

void ACCharacter_Enemy::BeginPlay()
{
	Super::BeginPlay();

	CW_EnemyHpBar = Cast<UCW_EnemyHpBar>(HPBarWidget->GetWidget());

	// AI이름 설정
	UEnum* enemyEnum = Cast<UEnum>(StaticEnum<EEnemyName>());

	// UEnum을 통해 GetDisplayNameTextByValue 호출
	if (enemyEnum)
	{
		CW_AIName->SetAIName(enemyEnum->GetDisplayNameTextByValue(static_cast<int32>(EnemyName)).ToString());
	}


	// 맵에 표시될 아이콘 설정
	if (CGameInstance->MapIcon_DA != nullptr)
	{
		MapIconComponent->SetSprite(CGameInstance->MapIcon_DA->Enemy_Sprite);
	}
}

void ACCharacter_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// HPBar 셋팅
	if (CW_EnemyHpBar)
	{
		CW_EnemyHpBar->UpdataHpBar(GetStatComponent()->GetCurrentStat().HP_Max, GetStatComponent()->GetCurrentStat().HP);

		
		
		
		HPBarWidget->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(HPBarWidget->GetComponentLocation(), GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation()));
	}
}