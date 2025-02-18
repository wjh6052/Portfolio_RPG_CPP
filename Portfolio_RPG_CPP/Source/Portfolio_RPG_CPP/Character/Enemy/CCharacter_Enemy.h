#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_Base.h"
#include "CCharacter_Enemy.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_Enemy : public ACCharacter_Base
{
	GENERATED_BODY()

public:
	ACCharacter_Enemy();

//protected:
//	virtual void BeginPlay() override;
//
//
//public:
//	virtual void Tick(float DeltaTime) override;
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
