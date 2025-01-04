#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Datas/DataAsset/CCharacterDataAsset.h"
#include "CStatComponent.generated.h"



//--enum---------------------------------------------------------------------

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idling,
	Rolling,
	Attacking,
	Hitted,
	Groggy,
	Dying
};

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Unarmed,
	Flight,
	Climbing,
	Melee
};

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Stop,
	Walk,
	Joging,
	Run,
	Sprint
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_RPG_CPP_API UCStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatComponent();

protected:
	virtual void BeginPlay() override;



public:
	//get
	FORCEINLINE bool GetSprint() const { return bSprint; }

	FORCEINLINE EStateType GetStateType() const { return StateType; }
	FORCEINLINE EStatusType GetStatusType() const { return StatusType; }
	FORCEINLINE ESpeedType GetSpeedType() const { return SpeedType; }

	FORCEINLINE class UCCharacterDataAsset* GetCharacterDataAsset() const { return CharacterDataAsset; }


	//set
	FORCEINLINE void SetSprint(bool input) { bSprint = input; }
	FORCEINLINE void SetCanMove(bool input) { bCanMove = input; }

	FORCEINLINE void SetStateType(EStateType input) { StateType = input; }
	FORCEINLINE void SetStatusType(EStatusType input) { StatusType = input; }
	FORCEINLINE void SetSpeedType(ESpeedType input) { SpeedType = input; }


	//Is
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE bool IsSpeedType(ESpeedType input) { return SpeedType == input; }

	FORCEINLINE bool IsState(EStateType input) { return StateType == input; }
	FORCEINLINE bool IsStatus(EStatusType input) { return StatusType == input; }

		
public:
	//Set
	void SetSpeed(ESpeedType input);



private:
	// 기본스텟을 받아옴
	UPROPERTY(EditAnywhere, Category = "Data")
		class UCCharacterDataAsset* InPut_CharacterDataAsset;

	// 스텟을 다룰 변수
	class UCCharacterDataAsset* CharacterDataAsset;


	//현재의 상태를 조절하는 열거형
	EStateType StateType;
	EStatusType StatusType;
	ESpeedType SpeedType;

	bool bSprint = false;
	bool bCanMove = true;


public:
	class ACCharacter_Base* OwnerCharacter;

};
