#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data_Base.generated.h"


//--struct---------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FAnimMontageBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		class UAnimMontage* AnimMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		float PlayRate = 1.0;
};













UCLASS()
class PORTFOLIO_RPG_CPP_API UData_Base : public UObject
{
	GENERATED_BODY()
	
};
