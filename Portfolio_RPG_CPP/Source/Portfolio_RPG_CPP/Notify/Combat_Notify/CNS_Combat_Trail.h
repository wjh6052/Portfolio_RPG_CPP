#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState_Trail.h"
#include "CNS_Combat_Trail.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCNS_Combat_Trail : public UAnimNotifyState_Trail
{
	GENERATED_BODY()
	
public:
	void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);



};
