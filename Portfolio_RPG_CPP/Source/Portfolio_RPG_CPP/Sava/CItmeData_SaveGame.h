#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Datas/Data_Inventory.h"
#include "CItmeData_SaveGame.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCItmeData_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(SaveGame)
		TArray<FMaterialItem_DataTable> Save_MaterialItemItmeData_Arr;
	
	UPROPERTY(SaveGame)
		int Save_Money;
};
