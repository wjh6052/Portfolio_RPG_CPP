#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWInteractionBox.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWInteractionBox : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void ChoiceInteraction(int UPIndex);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UseInteraction();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintPure)
		bool GetOnInteractionBox();

};
