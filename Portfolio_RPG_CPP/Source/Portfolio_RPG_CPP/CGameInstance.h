#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Datas/Data_Character.h"
#include "CGameInstance.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UCGameInstance();


public:
	UDataTable* Player_DataTable;
	UDataTable* Enemy_DataTable;
	UDataTable* Boss_DataTable;
};
