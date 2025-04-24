#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Datas/Data_DataTable.h"
#include "CSaveGame.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	// 저장했던 당시의 레벨
	UPROPERTY(SaveGame)
		FName Save_SpawnLevelName;

	// 저장했던 당시의 위치
	UPROPERTY(SaveGame)
		FVector Save_PlayerSpawnPoint;


	// 플레이어 데이터
	UPROPERTY(SaveGame)
		TArray<FPlayer_DataTable> Save_Player_Data_Arr;

	// 보유 아이템 데이터
	UPROPERTY(SaveGame)
		TArray<FMaterialItem_DataTable> Save_MaterialItemItmeData_Arr;
	
	// 보유 머니 아이템
	UPROPERTY(SaveGame)
		int Save_Money;


	// 현제 강화 데이터
	UPROPERTY(SaveGame)
		TArray<FGearEnhancementData_DataTable> Save_GearEnhancementData_Arr;

	// 퀘스트 진행도
	UPROPERTY(SaveGame)
		TArray<FQuest_DataTable> Save_QuestData_Arr;
};
