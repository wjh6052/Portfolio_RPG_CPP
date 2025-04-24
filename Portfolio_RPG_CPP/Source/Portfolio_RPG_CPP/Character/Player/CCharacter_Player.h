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
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE class UCWidgetComponent* GetWidgetComponent() const { return WidgetComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE class UCInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }


public:
	void OnTest1();
	void OnTest2();

	virtual void OnMoveForward(float InAxis) override;
	virtual void OnMoveRight(float InAxis) override;

	virtual void OnJump() override;
	virtual void OffJump() override;

	virtual void OnHorizontalLook(float InAxis) override;
	virtual void OnVerticalLook(float InAxis) override;


	void OnWalk();
	void OnRun();
	void OffRun();
	void OnSprint();
	void OffSprint();

	void OnInventory();
	void OnInteraction();


	void OnCameraZoom(float InAxis) override;

	void OnWeaponChoice();
	void OffWeaponChoice();


	void OnAttack();
	void OnSkill_1();
	void OnSkill_2();
	void OnSkill_3();




public:
	//Scene Component
	UPROPERTY(EditAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = Camera)
		class UCameraComponent* Camera;






public:
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



protected:
	class ACMapCamera* Minimap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector MiniMapLocation = FVector(0, 0, 250);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsLobby = false;
};
