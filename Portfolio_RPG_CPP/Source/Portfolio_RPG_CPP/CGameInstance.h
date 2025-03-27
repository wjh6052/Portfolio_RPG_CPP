#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Datas/Data_Character.h"
#include "Datas/Data_Inventory.h"
#include "Datas/Data_NPC.h"
#include "Datas/Data_Widget.h"
#include "Datas/Data_Quest.h"
#include "CGameInstance.generated.h"

// 아이템 정보 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdataMaterialItem, EItemUseType, ItemUseType, EStarRating, ItemRating, int, AddCount);

// 돈 정보 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdata_Money, int, AddMoney);


// 퀘스트 정보 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdate_Quest, const TArray<FQuest_DataTable>&, NewQuest_DataTable);



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
	void PlayerDataTableToArr();
	void EnemyDataTableToArr();

	// 플레이어 데이터
	UPROPERTY(BlueprintReadWrite)
		TArray<FPlayer_DataTable> Player_Data_Arr;
	UDataTable* Player_DataTable;

	// 몬스터 데이터
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

	


	UPROPERTY(BlueprintAssignable)
		FUpdate_Quest Update_Quest;

	// 퀘스트 정보를 업데이트할 함수
	UFUNCTION(BlueprintCallable)
		void UpdateQuestDate(FQuest_DataTable Input);


	// 퀘스트 정보 델리게이트
	FORCEINLINE void TriggerUpdateQuest() { Update_Quest.Broadcast(QuestData_Arr); }



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

	// 돈 정보 델리게이트 호출 함수
	FORCEINLINE void TriggerUpdataMoney(int AddMoney) { Updata_Money.Broadcast(AddMoney); }

	UPROPERTY(BlueprintAssignable)
		FUpdata_Money Updata_Money;


	// 보유 돈을 추가하는 함수
	UFUNCTION(BlueprintCallable)
		void AddMoney(int AddMoney);




public: // 기타 데이터
	void IconDataTableToArr();

	// 위젯 대화 아이콘
	UPROPERTY(BlueprintReadWrite)
		TArray<FConversationIcon_DataTable> ConversationIcon_Arr;
	UDataTable* ConversationIcon_DataTable;




	UFUNCTION(BlueprintCallable, BlueprintPure)
		FColor GetRatingColor(EStarRating InRating);

	UPROPERTY(BlueprintReadWrite)
		FItemRarityColor RatingColor;


// ------------------------------------------------DataTable-------------------------------------------------------
public:
	class UDA_DamageText* DamageText_DA;



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
	class ACCharacter_Base* GetPlayerCharacter();

};
