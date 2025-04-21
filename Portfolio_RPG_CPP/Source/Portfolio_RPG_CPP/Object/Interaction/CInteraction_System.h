#pragma once

#include "CoreMinimal.h"
#include "CInteraction.h"
#include "CInteraction_System.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACInteraction_System : public ACInteraction
{
	GENERATED_BODY()

public:
	ACInteraction_System();
	

public:
	UFUNCTION(BlueprintCallable)
		virtual void UseInteractionSystem();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UseInteractionSystem_Blueprint();
};
