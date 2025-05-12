#include "CNS_SetTime.h"
#include "../Global.h"
#include "../Character/CCharacter_Base.h"




FString UCNS_SetTime::GetNotifyName_Implementation() const
{
	return "SetTime";
}


void UCNS_SetTime::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	ownerCharacter->SetGlobalTime(SetTime);
}

void UCNS_SetTime::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());


	ownerCharacter->SetGlobalTime(1);
}
