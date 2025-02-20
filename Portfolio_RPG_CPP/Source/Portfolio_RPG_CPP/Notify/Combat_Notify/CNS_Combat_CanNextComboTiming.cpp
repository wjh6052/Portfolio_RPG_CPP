#include "CNS_Combat_CanNextComboTiming.h"
#include "../../Global.h"

#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"



FString UCNS_Combat_CanNextComboTiming::GetNotifyName_Implementation() const
{
	return "NextComboTiming";
}

void UCNS_Combat_CanNextComboTiming::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	ownerCharacter->GetCombatComponent()->Current_Combat->bCanNextComboTiming = true;
}

void UCNS_Combat_CanNextComboTiming::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	
	ownerCharacter->GetCombatComponent()->Current_Combat->bCanNextComboTiming = false;
}
