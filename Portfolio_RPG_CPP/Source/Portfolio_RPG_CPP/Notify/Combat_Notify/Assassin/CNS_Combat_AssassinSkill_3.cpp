#include "CNS_Combat_AssassinSkill_3.h"
#include "../../../Global.h"

#include "../../../Character/CCharacter_Base.h"
#include "../../../Object/Combat/CCombat_Base.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"


FString UCNS_Combat_AssassinSkill_3::GetNotifyName_Implementation() const
{
	return "AssassinSkill_3";
}


void UCNS_Combat_AssassinSkill_3::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());


	
	if (ownerCharacter->GetCombatComponent()->Current_Combat->SkillSingleTarget == nullptr)
	{
		TArray<ACCharacter_Base*> targetCharacterArr;
		ACCharacter_Base* targetCharacter = nullptr;

		for (AActor* target : ownerCharacter->GetCombatComponent()->Current_Combat->SkillTargetArr)
		{
			targetCharacterArr.Add(Cast<ACCharacter_Base>(target));
		}


		for (int i = 0; i < targetCharacterArr.Num(); i++)
		{
			if (i == 0)
			{
				targetCharacter = targetCharacterArr[i];
			}
			// HP가 가장 많은 적을 선택
			else if(targetCharacter->GetStatComponent()->GetPlayerData().Stat.HP < targetCharacterArr[i]->GetStatComponent()->GetPlayerData().Stat.HP)
			{
				targetCharacter = targetCharacterArr[i];
			}

		}

		if (targetCharacter)
			ownerCharacter->GetCombatComponent()->Current_Combat->SkillSingleTarget = targetCharacter;

	}

	// 적의 위치로 이동

	if(ownerCharacter->GetCombatComponent()->Current_Combat->SkillSingleTarget)
		ownerCharacter->GetCombatComponent()->Current_Combat->MoveTarget(ownerCharacter->GetCombatComponent()->Current_Combat->SkillSingleTarget, TargetForward, TargetRight, TargetUp, bNotMove, bNotTurn);




}


void UCNS_Combat_AssassinSkill_3::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());



	// 적에게 데미지 주기
	if (ownerCharacter->GetCombatComponent()->Current_Combat->SkillSingleTarget)
		ownerCharacter->GetCombatComponent()->Current_Combat->DamagesTarget(ownerCharacter->GetCombatComponent()->Current_Combat->SkillSingleTarget);
	
}


