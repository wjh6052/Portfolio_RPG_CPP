#include "CBTService_Root.h"
#include "../../Global.h"
#include "../CAIController.h"
#include "../../Character/CCharacter_Base.h"


#include "BehaviorTree/BlackboardComponent.h"



UCBTService_Root::UCBTService_Root()
{
	NodeName = "Service_Root";
}


void UCBTService_Root::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	{
		AIController = Cast<ACAIController>(OwnerComp.GetAIOwner());
		OwnerAICharacter = AIController->OwnerCharacterAI;
		BlackboardComp = OwnerComp.GetBlackboardComponent();
	}
	
	SetStateBehaviorKey(OwnerAICharacter->GetStatComponent()->GetStateType());
	SetStatusBehaviorKey(OwnerAICharacter->GetStatComponent()->GetStatusType());

	UEnum* Enum = StaticEnum<EStateType>();
	FString a = Enum->GetNameStringByValue((int64)OwnerAICharacter->GetStatComponent()->GetStateType());


	switch (OwnerAICharacter->GetStatComponent()->GetStateType())
	{
		case EStateType::Dying:
			AIController->StopMovement();
			return;

		case EStateType::Groggy:
			AIController->StopMovement();
			return;

		case EStateType::Hitted:
			AIController->StopMovement();
			return;
	}


	// 플레이어를 찾았을 때
	if (AIController->bFindPlayer)
	{
		Player = Cast<ACCharacter_Base>(BlackboardComp->GetValueAsObject("PlayerKey"));

		// 플레이어가 죽었을 때
		if (Player->GetStatComponent()->IsState(EStateType::Dying))
		{
			OwnerAICharacter->GetStatComponent()->SetStateType(EStateType::Idling);
		}
		else // 플레이어가 살아 있을 때
		{
			SetPlayerLocationKey(Player);
		}

	}
	else // 플레이어를 찾지 못하였을 때
	{


	}
	

	SetStateBehaviorKey(OwnerAICharacter->GetStatComponent()->GetStateType());
	SetStatusBehaviorKey(OwnerAICharacter->GetStatComponent()->GetStatusType());
}


void UCBTService_Root::SetStateBehaviorKey(EStateType InStateType)
{
	BlackboardComp->SetValueAsEnum("StateTypeKey", static_cast<uint8>(InStateType));
}

void UCBTService_Root::SetStatusBehaviorKey(EStatusType InStatusType)
{
	BlackboardComp->SetValueAsEnum("StatusTypeKey", static_cast<uint8>(InStatusType));
}

void UCBTService_Root::SetPlayerLocationKey(AActor* InPlayer)
{
	// 플레이어와 오너의 거리 계산
	float TargetDistance = OwnerAICharacter->GetDistanceTo(InPlayer);
	BlackboardComp->SetValueAsFloat("TargetDistanceKey", TargetDistance);

	BlackboardComp->SetValueAsVector("LocationKey", InPlayer->GetActorLocation());
}
