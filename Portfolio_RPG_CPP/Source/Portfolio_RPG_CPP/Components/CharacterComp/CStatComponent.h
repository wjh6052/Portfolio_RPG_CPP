#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Datas/Data_Character.h"
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

	void PlayerDataSetting();
	void EnemyDataSetting();
	void BossDataSetting();


public:
	void SetSpeed(ESpeedType input);
	
public:
	//get
	FORCEINLINE bool GetSprint() const { return bSprint; }

	FORCEINLINE EStateType GetStateType() const { return StateType; }
	FORCEINLINE EStatusType GetStatusType() const { return StatusType; }
	FORCEINLINE ESpeedType GetSpeedType() const { return SpeedType; }

	FORCEINLINE FPlayer_DataTable GetPlayerDataTable() const { return Player_DataTable; }
	FORCEINLINE FEnemy_DataTable GetEnemyDataTable() const { return Enemy_DataTable; }
	FORCEINLINE FBoss_DataTable GetBossDataTable() const { return Boss_DataTable; }


	//set
	FORCEINLINE void SetSprint(bool input) { bSprint = input; }
	FORCEINLINE void SetCanMove(bool input) { bCanMove = input; }

	FORCEINLINE void SetStateType(EStateType input) { StateType = input; }
	FORCEINLINE void SetStatusType(EStatusType input) { StatusType = input; }
	FORCEINLINE void SetSpeedType(ESpeedType input) { SpeedType = input; }

	FORCEINLINE void SetPlayerDataTable(FPlayer_DataTable input) { Player_DataTable = input; }
	FORCEINLINE void SetEnemyDataTable(FEnemy_DataTable input) { Enemy_DataTable = input; }
	FORCEINLINE void SetBossDataTable(FBoss_DataTable input) { Boss_DataTable = input; }


	//Is
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE bool IsSpeedType(ESpeedType input) { return SpeedType == input; }

	FORCEINLINE bool IsState(EStateType input) { return StateType == input; }
	FORCEINLINE bool IsStatus(EStatusType input) { return StatusType == input; }



private:
	// 데이터 테이블
	FPlayer_DataTable Player_DataTable;
	FEnemy_DataTable Enemy_DataTable;
	FBoss_DataTable Boss_DataTable;


	//현재의 상태를 조절하는 열거형
	EStateType StateType;
	EStatusType StatusType;
	ESpeedType SpeedType;


	bool bSprint = false;
	bool bCanMove = true;


public:
	class ACCharacter_Base* OwnerCharacter;

};
