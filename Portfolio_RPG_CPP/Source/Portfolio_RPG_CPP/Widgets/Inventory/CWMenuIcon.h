#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWMenuIcon.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWMenuIcon : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SetOwnerWidget(class UUserWidget* InOwnerTabbedMenu);
	virtual void SetOwnerWidget_Implementation(class UUserWidget* InOwnerTabbedMenu);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ButtonHovered(bool bOnHovered);
	virtual void ButtonHovered_Implementation(bool bOnHovered);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ButtonClick(bool bOnClick);
	virtual void ButtonClick_Implementation(bool bOnClick);
	


protected:
	UPROPERTY(BlueprintReadWrite)
		class UCWTabbedMenu* OwnerTabbedMenu;

	UPROPERTY(BlueprintReadWrite)
		bool bChoice;
};
