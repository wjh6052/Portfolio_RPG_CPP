#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Datas/Data_Inventory.h"
#include "CWGItemIcon.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWGItemIcon : public UUserWidget
{
	GENERATED_BODY()
	
public: // 
	UFUNCTION(BlueprintCallable)
		void UpdetaMaterialItemData(FMaterialItem_DataTable input);




	UFUNCTION(BlueprintImplementableEvent) // 
		void DetermineRating();

	UFUNCTION(BlueprintImplementableEvent) //
		void ButtonHovered(bool OnHovered);

	UFUNCTION(BlueprintImplementableEvent) // 
		void ButtonClick();

	UFUNCTION(BlueprintImplementableEvent) // 
		void UpdetaIcon();
	



public: // 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UI Data")
		EItemCategory ItemCategory;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI Data")
		FMaterialItem_DataTable MaterialItemData;

	UPROPERTY(BlueprintReadWrite, Category = "UI Data")
		FColor RatingColor;

};
