#pragma once

#include "CoreMinimal.h"
#include "CInteraction.h"
#include "CInteraction_NPC.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACInteraction_NPC : public ACInteraction
{
	GENERATED_BODY()
	
public:
	ACInteraction_NPC();


protected:
	virtual void BeginPlay() override;



public:
	UPROPERTY(BlueprintReadOnly)
		class ACCharacter_NPC* OwnerNPC;
};
