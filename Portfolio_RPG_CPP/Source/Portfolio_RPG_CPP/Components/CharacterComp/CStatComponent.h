#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Datas/Data_Character.h"
#include "CStatComponent.generated.h"



//--enum---------------------------------------------------------------------

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idling			UMETA(DisplayName = "대기중"),
	Rolling			UMETA(DisplayName = "구르기"),
	Attacking		UMETA(DisplayName = "공격 중"),
	Hitted			UMETA(DisplayName = "피격됨"),
	Groggy			UMETA(DisplayName = "기절"),
	Dying			UMETA(DisplayName = "사망"),
	Alert			UMETA(DisplayName = "경계 중")
};

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Unarmed		UMETA(DisplayName = "평상시"),
	Flight		UMETA(DisplayName = "비행"),
	Climbing	UMETA(DisplayName = "등반"),
	Combat		UMETA(DisplayName = "전투")
};

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Stop		UMETA(DisplayName = "정지"),
	Walk		UMETA(DisplayName = "걷기"),
	Joging		UMETA(DisplayName = "조깅"),
	Run			UMETA(DisplayName = "달리기"),
	Sprint		UMETA(DisplayName = "전력질주")
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
	void PlayerDataSetting();
	void EnemyDataSetting();
	void BossDataSetting();
	void NPCDataSetting();




public:

	bool AddDamage(float InDamage);


	void SetGroggy(float GroggyTime);
	FTimerHandle TimerHandle_Groggy;


public:
	//get
	FORCEINLINE bool GetSprint() const { return bSprint; }

	FORCEINLINE EStateType GetStateType() const { return StateType; }
	FORCEINLINE EStatusType GetStatusType() const { return StatusType; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE ESpeedType GetSpeedType() const { return SpeedType; }

	FORCEINLINE FStat GetCurrentStat() const { return CurrentStat; }

	FORCEINLINE FPlayer_DataTable GetPlayerData() const { return Player_Data; }
	FORCEINLINE FEnemy_DataTable GetEnemyData() const { return Enemy_Data; }
	FORCEINLINE FBoss_DataTable GetBossData() const { return Boss_Data; }

	


	//set
	FORCEINLINE void SetSprint(bool input) { bSprint = input; }

	void SetStateType(EStateType input);
	FORCEINLINE void SetStatusType(EStatusType input) { StatusType = input; }

	UFUNCTION(BlueprintCallable)
		void SetSpeed(ESpeedType input);


	FORCEINLINE void SetCurrentStat(FStat input) { CurrentStat = input; }

	FORCEINLINE void SetPlayerData(FPlayer_DataTable input) { Player_Data = input; }
	FORCEINLINE void SetEnemyData(FEnemy_DataTable input) { Enemy_Data = input; }
	FORCEINLINE void SetBossData(FBoss_DataTable input) { Boss_Data = input; }


	//Is
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE bool IsSpeedType(ESpeedType input) { return SpeedType == input; }

	FORCEINLINE bool IsState(EStateType input) { return StateType == input; }
	FORCEINLINE bool IsStatus(EStatusType input) { return StatusType == input; }



public:
	void Desh_Ragdoll();

	FTimerHandle RagdollTimerHandle;

private:
	// 현제 스텟
	FStat CurrentStat;


	// 
	FPlayer_DataTable Player_Data;
	FEnemy_DataTable Enemy_Data;
	FBoss_DataTable Boss_Data;


	//
	EStateType StateType;
	EStatusType StatusType;
	ESpeedType SpeedType;


	bool bCanMove = true;
	bool bSprint = false;


public:
	class UCGameInstance* CGameInstance;


	class ACCharacter_Base* OwnerCharacter_Base;

	class ACCharacter_Player* OwnerACCharacter_Player;
	class ACCharacter_Enemy* OwnerCharacter_Enemy;

	class ACCharacter_NPC* OwnerACCharacter_NPC;

};
