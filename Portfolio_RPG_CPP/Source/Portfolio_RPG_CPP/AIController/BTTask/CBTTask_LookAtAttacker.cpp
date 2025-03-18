#include "CBTTask_LookAtAttacker.h"
#include "../../Global.h"
#include "../../Character/AI/CCharacter_AI.h"
#include "../../AIController/CAIController.h"

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"



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
	TargetLocation = AICharacter->GetCombatComponent()->DamageCharacter->GetActorLocation();



	return EBTNodeResult::InProgress;
}

void UCBTTask_LookAtAttacker::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	// 현재 회전값
	FRotator currentRotation = AICharacter->GetActorRotation();


	// 목표 회전값
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(AICharacter->GetActorLocation(), TargetLocation);

	float deltaYaw = FMath::Abs(FMath::FindDeltaAngleDegrees(currentRotation.Yaw, targetRotation.Yaw));
	float speed = deltaYaw * (RotationSpeed * 0.01f);

	// 부드럽게 회전
	FRotator newRotation = FMath::RInterpTo(currentRotation, targetRotation, DeltaSeconds, speed);
	newRotation.Pitch = currentRotation.Pitch;
	newRotation.Roll = currentRotation.Roll;
	AICharacter->SetActorRotation(newRotation);


	if (FMath::Abs(AICharacter->GetActorRotation().Yaw - targetRotation.Yaw) < 50.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		AICharacter->GetStatComponent()->SetStateType(EStateType::Idling);
		return;
	}
}
