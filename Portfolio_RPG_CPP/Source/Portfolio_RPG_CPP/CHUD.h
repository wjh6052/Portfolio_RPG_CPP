#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"


UCLASS()
class PORTFOLIO_RPG_CPP_API ACHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ACHUD();

protected:
	virtual void BeginPlay() override;

public:
	virtual void DrawHUD() override;

public:
	

private:
	class ACCharacter_Base* BaseCharacter;
};
