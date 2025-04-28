#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CQuestActor.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACQuestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACQuestActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


public:
	// 진행 중
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void InProgress();

	// 완료됨
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Completed();


public:
	UPROPERTY(BlueprintReadWrite)
		class UCGameInstance* CGameInstance;
};
