#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Datas/Data_DataTable.h"
#include "../CGameInstance.h"
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	//Get
	FORCEINLINE class USkeletalMeshComponent* GetMainMesh() { return Main_SkeletalMesh; }
	FORCEINLINE class USkeletalMeshComponent* GetOutLineMesh() { return OutLine_SkeletalMesh; }
	FORCEINLINE ECharacterType GetCharacterType() const { return CharacterType; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE class UCStatComponent* GetStatComponent() const { return StatComponent; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE class UCCombatComponent* GetCombatComponent() const { return CombatComponent; }
	FORCEINLINE class UPaperSpriteComponent* GetMapIconComponent() const { return MapIconComponent; }

	//Set


	//IS
	FORCEINLINE bool IsMovementMode(EMovementMode input) { return input == GetCharacterMovement()->MovementMode; }
	FORCEINLINE bool IsCharacterType(ECharacterType input) { return input == CharacterType; }


public:
	void SetGlobalTime(float InTime);

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
	// 일반적인 마네킹이 아닌 규격을 사용할경우 true
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		bool bOnCustomMesh = false;


	// 인간형이 아닐경우 커스텀 플레이 몽타주를 사용한다
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void CustomPlayAnimMontage(FAnimMontageBase InAnimMontage);

	// 커스텀 플레이 몽타주 스탑
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void CustomMontagePause(const UAnimMontage* Montage);

	// 커스텀 플레이 몽타주 이어서 스타트
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void CustomMontageResume(const UAnimMontage* Montage);


	// 인간형이 아닐경우 커스텀 랙돌
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void CustomDeshRagdoll();




protected:	
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USkeletalMeshComponent* Main_SkeletalMesh;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USkeletalMeshComponent* OutLine_SkeletalMesh;


public:
	// 맵에 표시될 아이콘
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MapIcon")
		class UPaperSpriteComponent* MapIconComponent;




public:
	UPROPERTY(BlueprintReadOnly)
		ECharacterType CharacterType;

private:
	//Actor Component
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCStatComponent> StatComponent;	

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCCombatComponent> CombatComponent;


protected:
	UPROPERTY(BlueprintReadOnly)
		class UCGameInstance* CGameInstance;

};
