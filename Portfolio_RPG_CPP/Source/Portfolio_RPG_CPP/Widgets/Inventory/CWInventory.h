#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWInventory.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SwitchTabs(int Input);
	virtual void SwitchTabs_Implementation(int Input);


};
