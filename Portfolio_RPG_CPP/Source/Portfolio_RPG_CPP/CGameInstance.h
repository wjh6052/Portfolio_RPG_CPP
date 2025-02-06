#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Datas/Data_Character.h"
#include "Datas/Data_Inventory.h"
#include "CGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateMaterialItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdate_Money, int, InMoney);

UCLASS()
class PORTFOLIO_RPG_CPP_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UCGameInstance();

	virtual void Init() override;

public:

	void DataTableToMaterialItemData(); // 데이터테이블에서 가져온 데이터를 배열으로 옮김	
	void AddMaterialItem(EItemUseType ItemUseType, EStarRating ItemRating,int AddCount); // 배열에 아이템의 갯수를 더함
	

public:
	// SaveGame
	UFUNCTION(BlueprintCallable)
		void SaveData(FString SlotName = "SaveData", int Index = 0);
	UFUNCTION(BlueprintCallable)
		bool LoadData(FString SlotName = "SaveData", int Index = 0);
	UFUNCTION(BlueprintCallable)
		void DeleteData(FString SlotName = "SaveData", int Index = 0);




	




	

public:
	// 델리게이트 호출 함수
	FORCEINLINE void TriggerUpdateMaterialItem() { Update_MaterialItem.Broadcast(); }
	void TriggerUpdateMoney(int InMoney);



	// 델리게이트 변수
	UPROPERTY(BlueprintAssignable)
		FUpdateMaterialItem Update_MaterialItem;

	UPROPERTY(BlueprintAssignable)
		FUpdate_Money Update_Money;
	




public:
	// 유저가 가지고 있는 아이템 배열
	UPROPERTY(BlueprintReadWrite)
		TArray<FMaterialItem_DataTable> MaterialItemItmeData_Arr;

	UPROPERTY(BlueprintReadWrite)
		FItemRarityColor RatingColor;



	// 유저가 가지고 있는 소지금 
	UPROPERTY(BlueprintReadWrite)
		int Money = 0;




public: // DataTable
	UDataTable* Player_DataTable;
	UDataTable* Enemy_DataTable;
	UDataTable* Boss_DataTable;

	UDataTable* MaterialItem_DataTable;


private:
	

	// 아이템데이터를 저장할 SaveGame
	class UCItmeData_SaveGame* ItmeData_SaveGame;
};
