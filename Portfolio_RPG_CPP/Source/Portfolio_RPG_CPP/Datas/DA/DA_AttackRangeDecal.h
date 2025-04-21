#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_AttackRangeDecal.generated.h"





UCLASS()
class PORTFOLIO_RPG_CPP_API UDA_AttackRangeDecal : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Box")
		class UMaterialInterface* RangeBox;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Circle")
		class UMaterialInterface* RangeCircle;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "HalfCircle")
		class UMaterialInterface* RangeHalfCircle;
};
