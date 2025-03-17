#include "CBTTask_Spline.h"

#include "../../Global.h"
#include "../../Character/AI/CCharacter_AI.h"
#include "../../AIController/CAIController.h"

#include "AIController.h"
#include "Components/SplineComponent.h"


UCBTTask_Spline::UCBTTask_Spline()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTask_Spline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetAIOwner()->StopMovement();

	return EBTNodeResult::InProgress;
}

void UCBTTask_Spline::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* AIController = Cast<ACAIController>(OwnerComp.GetAIOwner());
	ACCharacter_AI* AICharacter = Cast<ACCharacter_AI>(AIController->GetPawn());

	UCPatrolComponent* PatrolComp = AICharacter->GetPatrolComponent();

	
	FVector location;
	float acceptanceRadius;
	CheckFalse(PatrolComp->GetMoveTo(location, acceptanceRadius));

	AICharacter->GetStatComponent()->SetSpeed(ESpeedType::Walk);


	EPathFollowingRequestResult::Type result = AIController->MoveToLocation(location, acceptanceRadius, false);
	if (result == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		PatrolComp->SplineUpdateNextIndex();
		return;
	}
}
