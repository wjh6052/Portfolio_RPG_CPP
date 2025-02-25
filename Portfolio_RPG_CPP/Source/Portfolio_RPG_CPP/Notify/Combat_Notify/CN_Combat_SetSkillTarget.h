#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CN_Combat_SetSkillTarget.generated.h"





UCLASS()
class PORTFOLIO_RPG_CPP_API UCN_Combat_SetSkillTarget : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceLength = 700;

	UPROPERTY(EditAnywhere, Category = "Trace")
		FVector TraceSize = FVector(50, 50, 50);

	UPROPERTY(EditAnywhere, Category = "Trace")
		bool TraceTest = false;
};
