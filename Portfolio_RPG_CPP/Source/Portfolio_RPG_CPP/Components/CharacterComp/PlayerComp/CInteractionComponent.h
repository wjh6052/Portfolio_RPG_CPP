#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../../Datas/Data_NPC.h"
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:	
	void AddInteraction(AActor* InIteminteraction);
	void RemovalInteraction(AActor* InIteminteraction);
	
	UFUNCTION(BlueprintCallable)
		void StartNPCTalk(AActor* InNpc);
	UFUNCTION(BlueprintCallable)
		void EndNPCTalk(AActor* InNpc);



private:
	class UCGameInstance* CGameInstance;

	class ACCharacter_Player* OwnerPlayer;
};
