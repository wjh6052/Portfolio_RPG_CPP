#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_Base.h"
#include "CCharacter_Inventory.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_Inventory : public ACCharacter_Base
{
	GENERATED_BODY()
	
public:
	ACCharacter_Inventory();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	//Scene Component
	UPROPERTY(EditAnywhere, Category = Camera)
		class USpotLightComponent* SpotLight;



};
