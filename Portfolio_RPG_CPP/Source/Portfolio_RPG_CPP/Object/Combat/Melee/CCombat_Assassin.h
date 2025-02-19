#pragma once

#include "CoreMinimal.h"
#include "CCombat_Melee.h"
#include "CCombat_Assassin.generated.h"






UCLASS()
class PORTFOLIO_RPG_CPP_API ACCombat_Assassin : public ACCombat_Melee
{
	GENERATED_BODY()

public:
	ACCombat_Assassin();

protected:
	virtual void BeginPlay() override;



public:
	virtual void StartWeapon() override;
	virtual void EndWeapon() override;


public:
	
};
