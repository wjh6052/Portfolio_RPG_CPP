#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInteractionComponent.generated.h"





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_RPG_CPP_API UCInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCInteractionComponent();

protected:
	virtual void BeginPlay() override;



public:	
	void AddInteraction(AActor* InIteminteraction);
	void RemovalInteraction(AActor* InIteminteraction);
	

private:
	class ACCharacter_Player* OwnerPlayer;
};
