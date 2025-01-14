#include "CNS_CanMove.h"
#include "../Global.h"

#include "../Character/CCharacter_Base.h"



FString UCNS_CanMove::GetNotifyName_Implementation() const
{
	return "CanMove";
}

void UCNS_CanMove::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	SaveSpeed = ownerCharacter->GetStatComponent()->GetSpeedType();
	ownerCharacter->GetStatComponent()->SetSpeed(ESpeedType::Stop);
}

void UCNS_CanMove::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	ownerCharacter->GetStatComponent()->SetSpeed(SaveSpeed);

}
