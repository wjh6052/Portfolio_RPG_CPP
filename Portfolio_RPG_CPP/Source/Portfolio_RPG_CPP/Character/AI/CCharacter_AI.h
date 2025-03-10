#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_Base.h"
#include "CCharacter_AI.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_AI : public ACCharacter_Base
{
	GENERATED_BODY()
	

public:
	// Get
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }


	// Set
	FORCEINLINE void SetBehaviorTree(class UBehaviorTree* InBehaviorTree) { BehaviorTree = InBehaviorTree; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 1;

	class UBehaviorTree* BehaviorTree;
};
