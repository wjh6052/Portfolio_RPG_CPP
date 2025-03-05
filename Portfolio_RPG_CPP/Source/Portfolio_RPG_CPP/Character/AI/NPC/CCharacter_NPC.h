// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_AI.h"
#include "../../../Datas/Data_NPC.h"
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
		ENPCType NPCType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		ENPCName NPCName;


private:


	class ACInteraction_NPC* Interaction_NPC;
};
