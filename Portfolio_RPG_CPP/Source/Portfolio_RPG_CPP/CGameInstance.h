#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Datas/Data_Character.h"
#include "Datas/Data_Combat.h"
#include "Datas/Data_Inventory.h"
#include "Datas/Data_NPC.h"
#include "Datas/Data_Widget.h"
#include "CGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdataMaterialItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdata_Money);

UCLASS()
class PORTFOLIO_RPG_CPP_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UCGameInstance();

	virtual void Init() override;

public:

	



	






	
// ------------------------------------------------Delegate-------------------------------------------------------
public:
	// 델리게이트 호출 함수
	FORCEINLINE void TriggerUpdataMaterialItem() { Updata_MaterialItem.Broadcast(); }
	FORCEINLINE void TriggerUpdataMoney() { Updata_Money.Broadcast(); }



	// 델리게이트 변수
	UPROPERTY(BlueprintAssignable)
		FUpdataMaterialItem Updata_MaterialItem;

	UPROPERTY(BlueprintAssignable)
		FUpdata_Money Updata_Money;
	





// ------------------------------------------------DataTable-------------------------------------------------------
public: // 캐릭터 데이터
	void PlayerDataTableToArr();
	void EnemyDataTableToArr();

	// 플레이어 데이터
	UPROPERTY(BlueprintReadWrite)
		TArray<FPlayer_DataTable> Playe_Data_Arr;
	UDataTable* Player_DataTable;

	// 몬스터 데이터
	UPROPERTY(BlueprintReadWrite)
		TArray<FEnemy_DataTable> Enemy_Data_Arr;
	UDataTable* Enemy_DataTable;

	// 보스 몬스터 데이터
	//UPROPERTY(BlueprintReadWrite)
	//	TArray<FBoss_DataTable> Boss_Data_Arr;
	UDataTable* Boss_DataTable;



public: // NPC 데이터
	void NPCDataTableToArr();

	// NPC 데이터
	UPROPERTY(BlueprintReadWrite)
		TArray<FNPC_DataTable> NPCData_Arr;
	UDataTable* NPC_DataTable;





public: // 아이템 데이터
	void ItemDataTableToArr(); 

	// 유저가 가지고 있는 아이템
	UPROPERTY(BlueprintReadWrite)
		TArray<FMaterialItem_DataTable> MaterialItemItmeData_Arr;
	UDataTable* MaterialItem_DataTable;




public: // 아이템 데이터
	void CombatPlayerDataTableToArr();

	// 유저가 가지고 있는 아이템
	UPROPERTY(BlueprintReadWrite)
		TArray<FCombatPlayer_DataTable> CombatPlayerData_Arr;
	UDataTable* CombatPlayer_DataTable;
	



public: // 기타 데이터
	void IconDataTableToArr();

	// 위젯 대화 아이콘
	UPROPERTY(BlueprintReadWrite)
		TArray<FConversationIcon_DataTable> ConversationIcon_Arr;
	UDataTable* ConversationIcon_DataTable;




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
	// 배열에 아이템의 갯수를 추가함
	UFUNCTION(BlueprintCallable)
		void AddMaterialItem(EItemUseType ItemUseType, EStarRating ItemRating, int AddCount);
	UFUNCTION(BlueprintCallable)
		void AddMoney(int AddMoney);


public:

// 유저가 가지고 있는 소지금 
	UPROPERTY(BlueprintReadWrite)
		int Money = 0;


private:
	// 아이템데이터를 저장할 SaveGame
	class UCItmeData_SaveGame* ItmeData_SaveGame;




};
