#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Character/Player/CCharacter_Player.h"
#include "../../Components/CharacterComp/PlayerComp/CInteractionComponent.h"
#include "CWInteraction.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCWInteraction : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
		class ACCharacter_Player* Onwer_Player;
};
