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



	// ��ؽ��� 2�� ��ų�� ������ ���� ������� ������� ���ϵ��� ����
	// ������ ���� ����Ʈ

	if (CurrentSkillCooldowns[1] < 0.00001f)
	{
		TArray<AActor*> outHits;
		outHits.Add(OwnerCharacter);

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // ĳ���� ����

		TArray<FHitResult> HitResult;

		bool bhit = UKismetSystemLibrary::SphereTraceMultiForObjects(
			OwnerCharacter->GetWorld(),
			OwnerCharacter->GetActorLocation(),
			OwnerCharacter->GetActorLocation(),
			600.0f,
			ObjectTypes,
			false, // Complex Trace ����
			outHits, // ������ ���� ����Ʈ
			EDrawDebugTrace::ForOneFrame, // ����� ����� �ɼ�
			HitResult,
			true // ���� �浹 �˻� ����	
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