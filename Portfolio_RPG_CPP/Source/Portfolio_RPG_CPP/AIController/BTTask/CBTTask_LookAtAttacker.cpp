#include "CBTTask_LookAtAttacker.h"
#include "../../Global.h"
#include "../../Character/AI/CCharacter_AI.h"
#include "../../AIController/CAIController.h"

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"



UCBTTask_LookAtAttacker::UCBTTask_LookAtAttacker()
{
	NodeName = TEXT("LookAtAttacker");

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTask_LookAtAttacker::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AIController = Cast<ACAIController>(OwnerComp.GetAIOwner());
	AICharacter = AIController->OwnerCharacterAI;
	BlackboardComp = OwnerComp.GetBlackboardComponent();
	StartRotation = AICharacter->GetActorRotation();
	StartRotation.Yaw += RotationTolerance;


	return EBTNodeResult::InProgress;
}

void UCBTTask_LookAtAttacker::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	// 부드럽게 회전
	FRotator newRotation = AICharacter->GetActorRotation();
	newRotation.Pitch = StartRotation.Pitch;
	newRotation.Roll = StartRotation.Roll;
	newRotation.Yaw -= RotationSpeed;
	AICharacter->SetActorRotation(newRotation);


	if (FMath::Abs(AICharacter->GetActorRotation().Yaw - StartRotation.Yaw) < RotationTolerance ||
		BlackboardComp->GetValueAsObject("PlayerKey"))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		AICharacter->GetStatComponent()->SetStateType(EStateType::Idling);
		return;
	}
}
