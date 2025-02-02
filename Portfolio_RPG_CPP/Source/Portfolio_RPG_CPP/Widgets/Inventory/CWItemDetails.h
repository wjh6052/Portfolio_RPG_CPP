#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Datas/Data_Inventory.h"
#include "CWItemDetails.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWItemDetails : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SetDetails(FMaterialItem_DataTable MaterialItemData, FColor RatingColor);
	virtual void SetDetails_Implementation(FMaterialItem_DataTable MaterialItemData, FColor RatingColor);



};
