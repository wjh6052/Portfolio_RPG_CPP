#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CN_Combat_SpawnThrowableWeapon.generated.h"





UCLASS()
class PORTFOLIO_RPG_CPP_API UCN_Combat_SpawnThrowableWeapon : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, Category = "SocketName")
		FName SocketName;
};
