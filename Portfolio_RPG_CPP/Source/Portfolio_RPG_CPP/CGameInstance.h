#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Datas/Data_DataTable.h"
#include "CGameInstance.generated.h"


// 플레이어 데이터 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdata_PlayerData, ECombatType, CombatType);

// 아이템 정보 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdataMaterialItem, EItemUseType, ItemUseType, EStarRating, ItemRating, int, AddCount);

// 돈 정보 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdata_Money, int, AddMoney);


// 퀘스트 정보 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdate_Quest, FQuest_DataTable, NewQuest_DataTable, EQuestDetailsUpdateType, QuestDetailsUpdateType, FString, InName);





UCLASS()
class PORTFOLIO_RPG_CPP_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UCGameInstance();

	virtual void Init() override;

public:

	




// ------------------------------------------------캐릭터 데이터-------------------------------------------------------
public:
	// --------------------플레이어 데이터--------------------
	void PlayerDataTableToArr();
	
	void SettingPlayerDataStats(ECombatType InCombatType);

	void PlayerAddDamage(ECombatType InCombatType, float InDamage);


	UPROPERTY(BlueprintReadWrite)
		TArray<FPlayer_DataTable> Player_Data_Arr;
	UDataTable* Player_DataTable;
	

	// 퀘스트 정보를 델리게이트 한 변수
	UPROPERTY(BlueprintAssignable)
		FUpdata_PlayerData Update_PlayerData;
	
	// 퀘스트 정보를 업데이트할 함수
	UFUNCTION(BlueprintCallable)
		void UpdatePlayerData(ECombatType InCombatType, FPlayer_DataTable InPlayerData);


	// 퀘스트 정보 델리게이트
	FORCEINLINE void TriggerUpdatePlayerData(ECombatType InCombatType) { Update_PlayerData.Broadcast(InCombatType); }




	// --------------------에너미 데이터--------------------
	void EnemyDataTableToArr();
	
	UPROPERTY(BlueprintReadWrite)
		TArray<FEnemy_DataTable> Enemy_Data_Arr;
	UDataTable* Enemy_DataTable;



	// 보스 몬스터 데이터
	//UPROPERTY(BlueprintReadWrite)
	//	TArray<FBoss_DataTable> Boss_Data_Arr;
	UDataTable* Boss_DataTable;



// ------------------------------------------------NPC 데이터-------------------------------------------------------
public:
	void NPCDataTableToArr();

	// NPC 데이터
	UPROPERTY(BlueprintReadWrite)
		TArray<FNPC_DataTable> NPCData_Arr;
	UDataTable* NPC_DataTable;




// ------------------------------------------------퀘스트 데이터-------------------------------------------------------
public:
	void QuestDataTableToArr();

	// 퀘스트 데이터테이블
	UPROPERTY(BlueprintReadWrite)
		TArray<FQuest_DataTable> QuestData_Arr;
	UDataTable* Quest_DataTable;

	


	// 퀘스트 정보를 델리게이트 한 변수
	UPROPERTY(BlueprintAssignable)
		FUpdate_Quest Update_Quest;

	// 퀘스트 정보를 업데이트할 함수
	UFUNCTION(BlueprintCallable)
		void UpdateQuestDate(FQuest_DataTable Input, EQuestDetailsUpdateType QuestDetailsUpdateType, FString InName);


	// 퀘스트 정보 델리게이트
	FORCEINLINE void TriggerUpdateQuest(FQuest_DataTable NewQuestData, EQuestDetailsUpdateType QuestDetailsUpdateType, FString InName) { Update_Quest.Broadcast(NewQuestData, QuestDetailsUpdateType, InName); }



// ------------------------------------------------아이템 데이터-------------------------------------------------------
public:
	void ItemDataTableToArr(); 

	// 유저가 가지고 있는 아이템
	UPROPERTY(BlueprintReadWrite)
		TArray<FMaterialItem_DataTable> MaterialItemItmeData_Arr;
	UDataTable* MaterialItem_DataTable;


	// 아이템 정보 델리게이트 호출 함수
	FORCEINLINE void TriggerUpdataMaterialItem(EItemUseType ItemUseType, EStarRating ItemRating, int AddCount) { Updata_MaterialItem.Broadcast(ItemUseType, ItemRating, AddCount); }

	UPROPERTY(BlueprintAssignable)
		FUpdataMaterialItem Updata_MaterialItem;


	// 배열에 아이템의 갯수를 추가하는 함수
	UFUNCTION(BlueprintCallable)
		void AddMaterialItem(EItemUseType ItemUseType, EStarRating ItemRating, int AddCount);
	


// ------------------------------------------------돈 데이터-------------------------------------------------------
public:

	// 유저가 가지고 있는 소지금 
	UPROPERTY(BlueprintReadWrite)
		int Money = 0;

	// 보유 돈을 추가하는 함수
	UFUNCTION(BlueprintCallable)
		void AddMoney(int AddMoney);


	// 돈 정보 델리게이트 호출 함수
	FORCEINLINE void TriggerUpdataMoney(int AddMoney) { Updata_Money.Broadcast(AddMoney); }

	UPROPERTY(BlueprintAssignable)
		FUpdata_Money Updata_Money;


	



// ------------------------------------------------기타 데이터-------------------------------------------------------
public:
// --------------------아이콘 데이터 --------------------
	void IconDataTableToArr();

	// 위젯 대화 아이콘
	UPROPERTY(BlueprintReadWrite)
		TArray<FConversationIcon_DataTable> ConversationIcon_Arr;
	UDataTable* ConversationIcon_DataTable;




// --------------------강화 데이터 --------------------
	void GearEnhancementDataTableToArr();


	UFUNCTION(BlueprintCallable, BlueprintPure)
		FGearEnhancementData_DataTable GetGearEnhancementData(EGearType InGearType, ECombatType InCombatType);

	FGearStets GetGearStets(EGearType InGearType, ECombatType InCombatType, int InLevel);

	UPROPERTY(BlueprintReadWrite)
		TArray<FGearEnhancementData_DataTable> GearEnhancementData_Arr;
	UDataTable* GearEnhancementData_DataTable;



public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FColor GetRatingColor(EStarRating InRating);

	UPROPERTY(BlueprintReadWrite)
		FItemRarityColor RatingColor;






// ------------------------------------------------DA-------------------------------------------------------
public:
	class UDA_DamageText* DamageText_DA;


	// 맵에 표시될 아이콘 데이터 에셋
	class UDA_MapIcon* MapIcon_DA;



// ----------------------------------------------------SaveGame-------------------------------------------------------
public: 
	// SaveGame
	UFUNCTION(BlueprintCallable)
		void SaveData(FString SlotName = "SaveData", int Index = 0);
	UFUNCTION(BlueprintCallable)
		bool LoadData(FString SlotName = "SaveData", int Index = 0);
	UFUNCTION(BlueprintCallable)
		void DeleteData(FString SlotName = "SaveData", int Index = 0);


public: // Get
		FORCEINLINE int GetMoney() { return Money; }

	


public:

	

	// 유저의 현재 캐릭터
	ECombatType CombatType;

private:
	// 아이템데이터를 저장할 SaveGame
	class UCItmeData_SaveGame* ItmeData_SaveGame;



public: // Get
	UFUNCTION(BlueprintCallable, BlueprintPure)
		class ACCharacter_Player* GetPlayerCharacter();

};
