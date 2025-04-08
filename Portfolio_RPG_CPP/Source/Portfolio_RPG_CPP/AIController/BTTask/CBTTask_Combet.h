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

	// 플레이어와의 거리
	float TargetDistance = 0.f;

	FVector TargetLocation;


	UPROPERTY(EditAnywhere, meta = (ToolTip = "공격 사거리"))
		float AttackRange = 200.0f;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "전투 진입 사거리"))
		float CombatEntryRange = 500.0f;

	


	class ACAIController* AIController;
	class ACCharacter_Base* AICharacter;
	class UBlackboardComponent* BlackboardComp;
};
