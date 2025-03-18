#include "CN_Combat_Skill_TargetGroggy.h"

#include "../../Global.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"

#include "Animation/AnimMontage.h"



FString UCN_Combat_Skill_TargetGroggy::GetNotifyName_Implementation() const
{
	return "Skill_TargetGroggy";
}

void UCN_Combat_Skill_TargetGroggy::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	ACCharacter_Base* characterOwner = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(characterOwner);



	if (bSingleTarget)
	{
		TArray<ACCharacter_Base*> targetCharacterArr;

		for (AActor* targetarr : characterOwner->GetCombatComponent()->Current_Combat->SkillTargetArr)
		{
			if (!!targetarr)
			{
				targetCharacterArr.Add(Cast<ACCharacter_Base>(targetarr));
			}
		}

		for (ACCharacter_Base* targetarr : targetCharacterArr)
		{
			targetarr->GetStatComponent()->SetGroggy(GroggyTime);
		}

	}
	else
	{
		ACCharacter_Base* targetCharacter = Cast<ACCharacter_Base>(characterOwner->GetCombatComponent()->Current_Combat->SkillSingleTarget);

		if (!!targetCharacter)
		{
			targetCharacter->GetStatComponent()->SetGroggy(GroggyTime);
		}
	}
	
}