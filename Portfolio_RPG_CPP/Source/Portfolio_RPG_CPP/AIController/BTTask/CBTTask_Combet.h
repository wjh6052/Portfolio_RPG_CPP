#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTask_Combet.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCBTTask_Combet : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTask_Combet();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	UPROPERTY(EditAnywhere, Category = "Blackboard")
		FBlackboardKeySelector TargetDistanceKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
		FBlackboardKeySelector LocationKey;

	// �÷��̾���� �Ÿ�
	float TargetDistance = 0.f;

	FVector TargetLocation;


	UPROPERTY(EditAnywhere, meta = (ToolTip = "���� ��Ÿ�"))
		float AttackRange = 200.0f;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "���� ���� ��Ÿ�"))
		float CombatEntryRange = 500.0f;

	


	class ACAIController* AIController;
	class ACCharacter_Base* AICharacter;
	class UBlackboardComponent* BlackboardComp;
};
