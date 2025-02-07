#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWMain.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCWMain : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void AddInteraction(AActor* InActor);
	
	UFUNCTION(BlueprintImplementableEvent)
		void RemovalInteraction(AActor* InActor);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintPure)
		class UCWInteractionBox* GetWInteractionBox();

};
