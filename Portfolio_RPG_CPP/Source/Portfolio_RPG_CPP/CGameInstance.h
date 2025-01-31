#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Datas/Data_Character.h"
#include "Datas/Data_Inventory.h"
#include "CGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateMaterialItem);

UCLASS()
class PORTFOLIO_RPG_CPP_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UCGameInstance();

	virtual void Init() override;

public:

	void DataTableToMaterialItemData(); // 데이터테이블에서 가져온 데이터를 배열으로 옮김
	// 배열에 아이템의 갯수를 더함
	void AddMaterialItem(EItemUseType ItemUseType, EStarRating ItemRating,int AddCount); // 델리게이트 추가 예정
	
	// SaveGame
	void SaveData(int Index = 0);
	void LoadData(int Index = 0);
	void DeleteData(int Index = 0);


	FORCEINLINE TArray<FMaterialItem_DataTable> GetMaterialItemArr() { return MaterialItemItmeData_Arr; }


	// 델리게이트 호출 함수
	FORCEINLINE void TriggerUpdateMaterialItem() { Update_MaterialItem.Broadcast(); }



public: // DataTable
	UDataTable* Player_DataTable;
	UDataTable* Enemy_DataTable;
	UDataTable* Boss_DataTable;

	UDataTable* MaterialItem_DataTable;

	

public:
	// 델리게이트 변수
	UPROPERTY(BlueprintAssignable)
		FUpdateMaterialItem Update_MaterialItem;
	

private:
	TArray<FMaterialItem_DataTable> MaterialItemItmeData_Arr;
	FItemRarityColor RatingColor;


	// 아이템데이터를 저장할 SaveGame
	class UCItmeData_SaveGame* ItmeData_SaveGame;
};
