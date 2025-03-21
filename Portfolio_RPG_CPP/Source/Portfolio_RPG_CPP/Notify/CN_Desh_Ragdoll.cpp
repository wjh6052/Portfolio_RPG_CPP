#include "CN_Desh_Ragdoll.h"
#include "../Global.h"
#include "../Character/CCharacter_Base.h"


FString UCN_Desh_Ragdoll::GetNotifyName_Implementation() const
{
	return "Desh_Ragdoll";
}

void UCN_Desh_Ragdoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	ownerCharacter->GetStatComponent()->Desh_Ragdoll();
	
}