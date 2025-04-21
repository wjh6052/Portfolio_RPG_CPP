#pragma once

#include "CoreMinimal.h"
#include "CAIController.h"
#include "CAIController_Boss.generated.h"






UCLASS()
class PORTFOLIO_RPG_CPP_API ACAIController_Boss : public ACAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void SetPlayer(AActor* InPlayer);
};
