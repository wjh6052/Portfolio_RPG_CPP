#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CNS_Combat_AssassinSkill_1.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCNS_Combat_AssassinSkill_1 : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;




	UPROPERTY(EditAnywhere, Category = "RushLength")
		float RushLength = 500;

	UPROPERTY(EditAnywhere, Category = "RushLength")
		bool RushLengthTest = false;

	TArray<class AActor*> TargetArr;

};
