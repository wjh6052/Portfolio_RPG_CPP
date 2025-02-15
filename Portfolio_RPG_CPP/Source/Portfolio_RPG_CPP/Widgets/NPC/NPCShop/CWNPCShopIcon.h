#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../../Datas/Data_Inventory.h"
#include "CWNPCShopIcon.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWNPCShopIcon : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FColor GetRatingColor();



public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI Data")
		FMaterialItem_DataTable ItemData;
};
