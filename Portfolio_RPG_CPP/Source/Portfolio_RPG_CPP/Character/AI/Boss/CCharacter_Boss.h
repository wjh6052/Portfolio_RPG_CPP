#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_AI.h"
#include "CCharacter_Boss.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_Boss : public ACCharacter_AI
{
	GENERATED_BODY()
	


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		EBossName BossName;
};
