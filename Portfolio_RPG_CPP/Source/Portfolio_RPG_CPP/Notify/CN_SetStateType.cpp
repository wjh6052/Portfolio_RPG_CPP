#include "CN_SetStateType.h"
#include "../Global.h"

FString UCN_SetStateType::GetNotifyName_Implementation() const
{
	return "SetStateType";
}
void UCN_SetStateType::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	ownerCharacter->GetStatComponent()->SetStateType(StateType);
}
