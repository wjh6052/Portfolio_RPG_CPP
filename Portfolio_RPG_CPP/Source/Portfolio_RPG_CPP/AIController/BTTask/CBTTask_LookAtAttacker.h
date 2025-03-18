#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTask_LookAtAttacker.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_RPG_CPP_API UCBTTask_LookAtAttacker : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTask_LookAtAttacker();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// ȸ���ӵ�
	UPROPERTY(EditAnywhere, Category = "RotationSpeed")
		float RotationSpeed = 2.0f;

	// ȸ�� ��������
	UPROPERTY(EditAnywhere, Category = "RotationSpeed")
		float RotationTolerance = 5.0f;


	class ACAIController* AIController;
	class ACCharacter_Base* AICharacter;

	FVector TargetLocation;
};
