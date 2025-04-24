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
	// �����ߴ� ����� ����
	UPROPERTY(SaveGame)
		FName Save_SpawnLevelName;

	// �����ߴ� ����� ��ġ
	UPROPERTY(SaveGame)
		FVector Save_PlayerSpawnPoint;


	// �÷��̾� ������
	UPROPERTY(SaveGame)
		TArray<FPlayer_DataTable> Save_Player_Data_Arr;

	// ���� ������ ������
	UPROPERTY(SaveGame)
		TArray<FMaterialItem_DataTable> Save_MaterialItemItmeData_Arr;
	
	// ���� �Ӵ� ������
	UPROPERTY(SaveGame)
		int Save_Money;


	// ���� ��ȭ ������
	UPROPERTY(SaveGame)
		TArray<FGearEnhancementData_DataTable> Save_GearEnhancementData_Arr;

	// ����Ʈ ���൵
	UPROPERTY(SaveGame)
		TArray<FQuest_DataTable> Save_QuestData_Arr;
};
