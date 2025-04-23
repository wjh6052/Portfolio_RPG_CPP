#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../Character/CCharacter_Base.h"
#include "CN_SetStateType.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCN_SetStateType : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


public:
	UPROPERTY(EditAnywhere)
		EStateType StateType;
};
