#pragma once

#include "CoreMinimal.h"
#include "CInteraction.h"
#include "../../Datas/Data_Quest.h"
#include "../../Datas/Data_NPC.h"
#include "CInteraction_NPC.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACInteraction_NPC : public ACInteraction
{
	GENERATED_BODY()
	
public:
	ACInteraction_NPC();


protected:
	virtual void BeginPlay() override;


public:
	void SettingInteraction_NPC(class ACCharacter_NPC* InOwnerNPC);


public:
	UPROPERTY(BlueprintReadOnly)
		class ACCharacter_NPC* OwnerNPC;

	UPROPERTY(BlueprintReadOnly)
		FNPC_DataTable NPC_DataTable;

	UPROPERTY(BlueprintReadOnly)
		TArray<FQuest_DataTable> Quest_DataTable_Arr;
};
