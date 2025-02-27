#pragma once

#include "CoreMinimal.h"
#include "CCombat_Melee.h"
#include "CCombat_Melee_Assassin.generated.h"





UCLASS()
class PORTFOLIO_RPG_CPP_API ACCombat_Melee_Assassin : public ACCombat_Melee
{
	GENERATED_BODY()
	
public:
	ACCombat_Melee_Assassin();

	virtual void BeginPlay() override;
	virtual void CooldownTick() override;

};
