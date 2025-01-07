#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/DataTable.h"
#include "CLevel_Main.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACLevel_Main : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	ACLevel_Main();


protected:
	virtual void BeginPlay() override;


public:
};
