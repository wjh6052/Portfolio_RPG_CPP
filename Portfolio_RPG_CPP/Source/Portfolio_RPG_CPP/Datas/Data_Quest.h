#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Data_Character.h"
#include "Data_Quest.generated.h"


//---------------------------Enum---------------------------------------------


UENUM(BlueprintType)
enum class EQuestState : uint8  // 퀘스트의 상태
{
	NotStarted		UMETA(DisplayName = "시작 전"),
	InProgress		UMETA(DisplayName = "진행 중"),
	Completed		UMETA(DisplayName = "완료됨")

};




//---------------------------struct---------------------------------------------


USTRUCT(BlueprintType)
struct FQuestDetails_Monster	// 퀘스트 요구 몬스터
{
	GENERATED_BODY()
public:
	// 잡아야 하는 몬스터의 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EEnemyName EnemyName;

	// 잡아야 하는 몬스터의 수
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 KillCount;

	// 현재 잡은 보스의 수
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentKillCount;
};



USTRUCT(BlueprintType)
struct FQuestDetails_Boss	// 퀘스트 요구 보스
{
	GENERATED_BODY()

public:
	// 잡아야 하는 보스의 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EBossName BossName;

	// 잡아야 하는 보스의 수
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 KillCount;

	// 현재 잡은 보스의 수
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentKillCount;
};



USTRUCT(BlueprintType)
struct FQuestDetails	// 퀘스트 내용
{
	GENERATED_BODY()

public:
	// 몬스터를 잡을 것을 요구
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bRequireMonsterKill; 

	// 퀘스트 요구 몬스터
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bRequireMonsterKill"))
		TArray<FQuestDetails_Monster> MonsterTargets;



	// 보스를 잡을 것을 요구 
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bRequireBossKill;  

	// 퀘스트 요구 보스
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bRequireBossKill"))
		TArray<FQuestDetails_Boss> BossTargets;



	// 아이템을 요구
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bRequireItemCollection;  

	// 퀘스트 요구 아이템
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bRequireItemCollection"))
		TArray<FItemType> RequiredItems;



	// 돈을 요구
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bRequireMoney;  

	// 돈의 액수  
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bRequireMoney"))
		int32 MoneyAmount;  
};


USTRUCT(BlueprintType)
struct FQuestReward		// 퀘스트 보상
{
	GENERATED_BODY()

public:
	// 보상으로 지급할 아이템 종류
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FItemType> RewardItems;

	// 보상으로 지급할 돈
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ClampMin = "0"))
		int32 RewardGold = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ClampMin = "0"))
		int32 RewardExe = 0;
};

//---------------------------DataTable---------------------------------------------

USTRUCT(BlueprintType)
struct FQuest_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 퀘스트 ID 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestSetting")
		int32 QuestID;  

	// 퀘스트 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestSetting")
		FString QuestName;    

	// 퀘스트 설명
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestSetting")
		FString QuestDescription;  


	// 퀘스트 내용
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestDetails")
		FQuestDetails QuestDetails; 


	// 퀘스트 보상
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestReward")
		FQuestReward QuestReward;


	// 현제 퀘스트의 상황
	UPROPERTY(BlueprintReadWrite)
		EQuestState QuestState;

	// 퀘스트를 준 NPC이름
	UPROPERTY(BlueprintReadWrite)
		FString NPCName;
};























UCLASS()
class PORTFOLIO_RPG_CPP_API UData_Quest : public UObject
{
	GENERATED_BODY()
	
};
