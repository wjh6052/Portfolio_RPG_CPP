#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Datas/Data_Character.h"
#include "../Components/CharacterComp/CStatComponent.h"
#include "../Components/CharacterComp/CCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CCharacter_Base.generated.h"






UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	ACCharacter_Base();


protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//Get
	FORCEINLINE class USkeletalMeshComponent* GetMainMesh() { return Main_SkeletalMesh; }
	FORCEINLINE class USkeletalMeshComponent* GetOutLineMesh() { return OutLine_SkeletalMesh; }
	FORCEINLINE ECharacterType GetCharacterType() const { return CharacterType; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE class UCStatComponent* GetStatComponent() const { return StatComponent; }
	FORCEINLINE class UCCombatComponent* GetCombatComponent() const { return CombatComponent; }

	//Set


	//IS
	FORCEINLINE bool IsMovementMode(EMovementMode input) { return input == GetCharacterMovement()->MovementMode; }


protected:
	virtual void OnMoveForward(float InAxis);
	void OnMoveForward_Unarmed(float InAxis);

	virtual void OnMoveRight(float InAxis);
	void OnMoveRight_Unarmed(float InAxis);

	virtual void OnHorizontalLook(float InAxis);
	virtual void OnVerticalLook(float InAxis);
	virtual void OnCameraZoom(float InAxis);


	virtual void OnJump();
	virtual void OffJump();



public:
	//Scene Component
	UPROPERTY(EditAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = Camera)
		class UCameraComponent* Camera;

protected:	
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USkeletalMeshComponent* Main_SkeletalMesh;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USkeletalMeshComponent* OutLine_SkeletalMesh;

protected:
		ECharacterType CharacterType;

private:
	//Actor Component
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCStatComponent> StatComponent;	

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCCombatComponent> CombatComponent;
};
