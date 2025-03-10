#include "CAIController.h"
#include "../Global.h"
#include "../Character/AI/CCharacter_AI.h"
#include "../Character/Player/CCharacter_Player.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"



ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &PerceptionComp, "PerceptionComponent");
	//PerceptionComp-
}


void ACAIController::Tick(float DeltaTime)
{

}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerCharacterAI = Cast<ACCharacter_AI>(InPawn);
	CheckNull(OwnerCharacterAI);

	RunBehaviorTree(OwnerCharacterAI->GetBehaviorTree());

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
	PerceptionComp->OnTargetPerceptionForgotten.AddDynamic(this, &ACAIController::OnTargetLost);
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actorArr;
	bool bNowFindPlayer = false;

	// AI가 감지범위 내의 액터들
	PerceptionComp->GetCurrentlyPerceivedActors(nullptr, actorArr);

	ACCharacter_Player* player = nullptr;
	
	for (AActor* actor : actorArr)
	{
		player = Cast<ACCharacter_Player>(actor);

		// 플레이어을 찾았을 때
		if (player)
		{
			GetBlackboardComponent()->SetValueAsObject("PlayerKey", player);
			bNowFindPlayer = true;
			bFindPlayer = true;
			CLog::Print(L"플레이어를 찾음");
			return;
		}
	}

	if (!bNowFindPlayer && bFindPlayer) // 캐틱터가 사라진 경우
	{
		bFindPlayer = false;
		OwnerCharacterAI->GetStatComponent()->SetStateType(EStateType::OnAlert);
		CLog::Print(L"플레이어가 범위에서 벗어남");
	}
	
}

void ACAIController::OnTargetLost(AActor* Actor)
{
	ACCharacter_Player* player = Cast<ACCharacter_Player>(Actor);;

	if (player) // 잊혀진 액터가 플레이어인 경우
	{
		bFindPlayer = false;

		GetBlackboardComponent()->SetValueAsObject("PlayerKey", nullptr);
		CLog::Print(L"플레이어가 잊혀짐");

		OwnerCharacterAI->GetStatComponent()->SetStateType(EStateType::Idling);
	}

	
}
