// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_AI.h"
#include "../../../Datas/Data_DataTable.h"
#include "CCharacter_NPC.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_NPC : public ACCharacter_AI
{
	GENERATED_BODY()

public:
	ACCharacter_NPC();

protected:
	virtual void BeginPlay() override;

	
	
	


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		ENPCName NPCName;


public:
	UFUNCTION()
		void UpdateInteractionQuestData(FQuest_DataTable NewQuest_Data, EQuestDetailsUpdateType QuestDetailsUpdateType, FString InName);


	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE class ACInteraction_NPC* GetInteraction_NPC() { return Interaction_NPC; }

	class UCGameInstance* CGameInstance;
	class ACInteraction_NPC* Interaction_NPC;
};
