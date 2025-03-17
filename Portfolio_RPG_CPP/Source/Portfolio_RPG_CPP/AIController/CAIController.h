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
	// ���Ͱ� �����Ǿ����� ȣ��� �Լ�
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	// ���Ͱ� ����� ������ �������� ȣ��
	UFUNCTION()
		void OnTargetLost(AActor* Actor);


	// ���� ������Ʈ
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
