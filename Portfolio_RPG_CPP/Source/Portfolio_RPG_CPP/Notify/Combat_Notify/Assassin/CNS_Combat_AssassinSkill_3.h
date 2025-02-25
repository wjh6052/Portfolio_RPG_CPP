#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CNS_Combat_AssassinSkill_3.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCNS_Combat_AssassinSkill_3 : public UAnimNotifyState
{
	GENERATED_BODY()


public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;




	UPROPERTY(EditAnywhere, Category = "Setting")
		float TargetForward = 0;

	UPROPERTY(EditAnywhere, Category = "Setting")
		float TargetRight = 0;

	UPROPERTY(EditAnywhere, Category = "Setting")
		float TargetUp = 0;

	UPROPERTY(EditAnywhere, Category = "Setting")
		bool bNotMove = false;

	UPROPERTY(EditAnywhere, Category = "Setting")
		bool bNotTurn = false;
};
