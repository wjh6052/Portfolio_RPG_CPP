#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACAIController();

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	// 액터가 감지되었을때 호출될 함수
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	// 액터가 벗어나고 수명이 끝났을때 호출
	UFUNCTION()
		void OnTargetLost(AActor* Actor);


	// 감지 컴포넌트
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* PerceptionComp;

public:
	bool bFindPlayer = false;


private:
	UPROPERTY(EditAnywhere)
		bool bDrawDebug = true;

	UPROPERTY(EditAnywhere)
		float BehaviorRange = 150.f;

public:
	class ACCharacter_AI* OwnerCharacterAI = nullptr;
	class UAISenseConfig_Sight* Sight;
};
