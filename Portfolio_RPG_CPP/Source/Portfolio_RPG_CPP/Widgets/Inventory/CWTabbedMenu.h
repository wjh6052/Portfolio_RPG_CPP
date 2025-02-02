#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWTabbedMenu.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWTabbedMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SwitchTabs(int Input);
	virtual void SwitchTabs_Implementation(int Input);



	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SetOwnerWidget(class UUserWidget* InOwnerInventory);
	virtual void SetOwnerWidget_Implementation(class UUserWidget* InOwnerInventory);




};
