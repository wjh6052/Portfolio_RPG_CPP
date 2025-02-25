#include "CNS_Combat_SkillFlyEnemy.h"
#include "../../Global.h"

#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"



FString UCNS_Combat_SkillFlyEnemy::GetNotifyName_Implementation() const
{
	return "SkillFlyEnemy";
}

void UCNS_Combat_SkillFlyEnemy::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());


	if (ownerCharacter->GetCombatComponent()->Current_Combat->SkillSingleTarget)
	{
		Target = Cast<ACCharacter_Base>(ownerCharacter->GetCombatComponent()->Current_Combat->SkillSingleTarget);

		Target->GetCharacterMovement()->GravityScale = 0.0f;
		ownerCharacter->GetCharacterMovement()->GravityScale = 0.0f;
	}	
}

void UCNS_Combat_SkillFlyEnemy::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());


	if (Target)
	{
		Target->GetCharacterMovement()->GravityScale = 100.0f;
		ownerCharacter->GetCharacterMovement()->GravityScale = 100.0f;
	}

	
}

