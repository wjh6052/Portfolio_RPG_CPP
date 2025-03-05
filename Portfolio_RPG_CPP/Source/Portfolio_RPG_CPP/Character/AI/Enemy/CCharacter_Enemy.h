#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_AI.h"
#include "CCharacter_Enemy.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_Enemy : public ACCharacter_AI
{
	GENERATED_BODY()

public:
	ACCharacter_Enemy();

protected:
	virtual void BeginPlay() override;


public:





public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		EEnemyName EnemyName;

	class UBehaviorTree* BehaviorTree;
};
