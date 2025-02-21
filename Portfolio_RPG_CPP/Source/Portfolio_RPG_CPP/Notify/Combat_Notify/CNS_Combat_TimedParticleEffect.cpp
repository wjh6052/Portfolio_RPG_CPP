#include "CNS_Combat_TimedParticleEffect.h"
#include "../../Global.h"

#include "../../Character/CCharacter_Base.h"



void UCNS_Combat_TimedParticleEffect::NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	Super::NotifyBegin(ownerCharacter->GetMainMesh(), Animation, TotalDuration, EventReference);
}



