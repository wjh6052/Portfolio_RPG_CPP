#pragma once

#include "CoreMinimal.h"
#include "CItemInteraction.h"
#include "CItemInteraction_Money.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACItemInteraction_Money : public ACItemInteraction
{
	GENERATED_BODY()
	
public:
	ACItemInteraction_Money();


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		int Money;
};
