#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CN_Combat_Skill_TargetGroggy.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCN_Combat_Skill_TargetGroggy : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// 단일 타깃
	UPROPERTY(EditAnywhere, Category = "Setting")
		bool bSingleTarget = false;

	// 기절 시간
	UPROPERTY(EditAnywhere, Category = "Setting")
		float GroggyTime = 3;
};
