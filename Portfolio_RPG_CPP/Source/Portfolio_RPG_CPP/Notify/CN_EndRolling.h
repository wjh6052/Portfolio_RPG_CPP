#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CN_EndRolling.generated.h"


UCLASS()
class PORTFOLIO_RPG_CPP_API UCN_EndRolling : public UAnimNotify
{
	GENERATED_BODY()
	

public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
