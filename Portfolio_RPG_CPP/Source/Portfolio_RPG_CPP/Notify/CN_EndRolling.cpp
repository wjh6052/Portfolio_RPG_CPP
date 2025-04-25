#include "CN_EndRolling.h"
#include "../Global.h"
#include "../Character/CCharacter_Base.h"



FString UCN_EndRolling::GetNotifyName_Implementation() const
{
	return "EndRolling";
}


void UCN_EndRolling::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());


	ownerCharacter->GetCombatComponent()->EndRolling();
}
