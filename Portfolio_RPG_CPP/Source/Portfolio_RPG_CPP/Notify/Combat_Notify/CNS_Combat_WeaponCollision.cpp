#include "CNS_Combat_WeaponCollision.h"
#include "../../Global.h"

#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"



FString UCNS_Combat_WeaponCollision::GetNotifyName_Implementation() const
{
	return "WeaponCollision";
}

void UCNS_Combat_WeaponCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	ownerCharacter->GetCombatComponent()->Current_Combat->SetWeaponCollision(true);
}

void UCNS_Combat_WeaponCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());


	ownerCharacter->GetCombatComponent()->Current_Combat->SetWeaponCollision(false);
}
