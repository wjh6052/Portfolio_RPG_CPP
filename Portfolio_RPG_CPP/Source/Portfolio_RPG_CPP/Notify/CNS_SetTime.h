#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CNS_SetTime.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCNS_SetTime : public UAnimNotifyState
{
	GENERATED_BODY()
	

public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


	UPROPERTY(EditAnywhere, Category = "Time")
		float SetTime = 1;

};
