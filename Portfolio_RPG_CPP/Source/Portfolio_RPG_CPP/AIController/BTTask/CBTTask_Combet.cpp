#include "CBTTask_Combet.h"

#include "../../Global.h"
#include "../../Character/AI/CCharacter_AI.h"
#include "../../AIController/CAIController.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"



UCBTTask_Combet::UCBTTask_Combet()
{
	NodeName = TEXT("Combet");

	bNotifyTick = true;
}


EBTNodeResult::Type UCBTTask_Combet::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AIController = Cast<ACAIController>(OwnerComp.GetAIOwner());
	AICharacter = AIController->OwnerCharacterAI;
	BlackboardComp = OwnerComp.GetBlackboardComponent();

	AActor* player = Cast<AActor>(BlackboardComp->GetValueAsObject("PlayerKey"));

	TargetLocation = player->GetActorLocation();
	BlackboardComp->SetValueAsVector("LocationKey", TargetLocation);

	TargetDistance = AICharacter->GetDistanceTo(player);
	BlackboardComp->SetValueAsFloat("TargetDistanceKey", TargetDistance);


	AIController->MoveToLocation(TargetLocation, 1.0f, false);


	if (AICharacter->GetStatComponent()->IsState(EStateType::Idling))
	{
		if (TargetDistance <= AttackRange && TargetDistance >= 1) // 공격 사거리에 들어왔을 경우
		{
			AICharacter->GetStatComponent()->SetSpeed(ESpeedType::Stop);

			//AICharacter->GetCombatComponent()->OnAttack();
		}
		else if (TargetDistance <= CombatEntryRange) // 이동속도를 줄이며 접근
		{
			AICharacter->GetStatComponent()->SetSpeed(ESpeedType::Walk);
		}
		else // 뛰어가 접근
		{
			AICharacter->GetStatComponent()->SetSpeed(ESpeedType::Joging);
		}
	}


	return EBTNodeResult::Succeeded;

}

