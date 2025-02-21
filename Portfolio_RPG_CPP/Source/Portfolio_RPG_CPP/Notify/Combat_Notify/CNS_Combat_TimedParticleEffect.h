#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState_TimedParticleEffect.h"
#include "CNS_Combat_TimedParticleEffect.generated.h"





UCLASS()
class PORTFOLIO_RPG_CPP_API UCNS_Combat_TimedParticleEffect : public UAnimNotifyState_TimedParticleEffect
{
	GENERATED_BODY()
	
public:
	void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);

};
