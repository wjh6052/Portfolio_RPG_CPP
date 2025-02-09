#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_Base.h"
#include "../../Components/CharacterComp/PlayerComp/CFlightComponent.h"
#include "../../Components/CharacterComp/PlayerComp/CWidgetComponent.h"
#include "../../Components/CharacterComp/PlayerComp/CInteractionComponent.h"
#include "CCharacter_Player.generated.h"


UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_Player : public ACCharacter_Base
{
	GENERATED_BODY()
	

public:
	ACCharacter_Player();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

public:
	//Get
	FORCEINLINE class UCFlightComponent* GetFlightComponent() const { return FlightComponent; }
	FORCEINLINE class UCWidgetComponent* GetWidgetComponent() const { return WidgetComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE class UCInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }


public:
	virtual void OnMoveForward(float InAxis) override;
	virtual void OnMoveRight(float InAxis) override;

	virtual void OnJump() override;
	virtual void OffJump() override;

	void OnWalk();
	void OnRun();
	void OffRun();
	void OnSprint();
	void OffSprint();

	void OnInventory();
	void OnInteraction();


	void OnCameraZoom(float InAxis) override;




	//Actor Component
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCFlightComponent> FlightComponent;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCWidgetComponent> WidgetComponent;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCInteractionComponent> InteractionComponent;

private:
	// 달리기
	void RunDelay();

	int Run = 0;
	FTimerHandle RunTimer;
};
