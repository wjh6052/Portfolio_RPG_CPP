#include "CCombat_Melee_Assassin.h"
#include "../../../Global.h"
#include "../../../Character/Player/CCharacter_Player.h"
#include "../../../Widgets/CWMain.h"
#include "../../../Widgets/GameplayUI/CWGameplayUI.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"


ACCombat_Melee_Assassin::ACCombat_Melee_Assassin()
{

}


void ACCombat_Melee_Assassin::BeginPlay()
{
	Super::BeginPlay();


}

void ACCombat_Melee_Assassin::CooldownTick()
{
	Super::CooldownTick();



	// 어쌔신의 2번 스킬이 주위에 적이 없을경우 사용하지 못하도록 설정
	// 무시할 액터 리스트

	if (CurrentSkillCooldowns[1] < 0.00001f)
	{
		TArray<AActor*> outHits;
		outHits.Add(OwnerCharacter);

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // 캐릭터 포함

		TArray<FHitResult> HitResult;

		bool bhit = UKismetSystemLibrary::SphereTraceMultiForObjects(
			OwnerCharacter->GetWorld(),
			OwnerCharacter->GetActorLocation(),
			OwnerCharacter->GetActorLocation(),
			600.0f,
			ObjectTypes,
			false, // Complex Trace 여부
			outHits, // 무시할 액터 리스트
			EDrawDebugTrace::ForOneFrame, // 디버그 드로잉 옵션
			HitResult,
			true // 실제 충돌 검사 여부	
		);

		if (bhit)
		{
			for (FHitResult hit : HitResult)
			{
				ACCharacter_Base* ch = Cast<ACCharacter_Base>(hit.GetActor());

				if (ch && OwnerCharacter->IsCharacterType(ECharacterType::Enemy))
				{
					bOnSkill[1] = true;
				}
			}
		}
		else
		{
			bOnSkill[1] = false;

		}


		Cast<ACCharacter_Player>(OwnerCharacter)->GetWidgetComponent()->GetMainWidget()->GetGameplayUI()->SetIconOpacity(!bOnSkill[1], ECombatType::Assassin, 1);
	}
}