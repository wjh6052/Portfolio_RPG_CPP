#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CNS_Combat_SkillFlyEnemy.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCNS_Combat_SkillFlyEnemy : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;



	class ACCharacter_Base* Target;


	FTimerHandle TimerHandle;
};
