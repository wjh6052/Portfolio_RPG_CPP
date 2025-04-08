#include "CAIController.h"
#include "../Global.h"
#include "../Character/AI/CCharacter_AI.h"
#include "../Character/Player/CCharacter_Player.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"


ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &PerceptionComp, "PerceptionComponent");
	
	
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	if (!!Sight)
	{
		Sight->SightRadius = 600.f;
		Sight->LoseSightRadius = 800.f;
		Sight->PeripheralVisionAngleDegrees = 90.f;
		Sight->SetMaxAge(2.f);
	
		Sight->DetectionByAffiliation.bDetectEnemies = true;
		Sight->DetectionByAffiliation.bDetectFriendlies = false;
		Sight->DetectionByAffiliation.bDetectNeutrals = false;
	
		PerceptionComp->ConfigureSense(*Sight);
		PerceptionComp->SetDominantSense(Sight->GetSenseImplementation());
	}
}


void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDrawDebug)
	{
		FVector center = OwnerCharacterAI->GetActorLocation();
	
	
		//Draw Debug Circle
		DrawDebugCircle(GetWorld(), center, Sight->SightRadius, 300, FColor::Green, false, -1.0f, 0, 2, FVector::RightVector, FVector::ForwardVector);
		DrawDebugCircle(GetWorld(), center, BehaviorRange, 300, FColor::Red, false, -1.0f, 0, 2, FVector::RightVector, FVector::ForwardVector);
	}

}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerCharacterAI = Cast<ACCharacter_AI>(InPawn);
	CheckNull(OwnerCharacterAI);



	SetGenericTeamId(OwnerCharacterAI->GetTeamID());
	RunBehaviorTree(OwnerCharacterAI->GetBehaviorTree());


	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
	PerceptionComp->OnTargetPerceptionForgotten.AddDynamic(this, &ACAIController::OnTargetLost);

	
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actorArr;
	bool bLookPlayer = false;

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
			bLookPlayer = true;
			bFindPlayer = true;
			return;
		}
	}

	// 플레이어가 범위에서 벗어남
	if(bLookPlayer == false && bFindPlayer == true)
	{
		bLookPlayer = false;
	}
	
}

void ACAIController::OnTargetLost(AActor* Actor)
{
	ACCharacter_Player* player = Cast<ACCharacter_Player>(Actor);;

	if (player) // 잊혀진 액터가 플레이어인 경우
	{
		OwnerCharacterAI->GetStatComponent()->SetStateType(EStateType::Alert);
		GetBlackboardComponent()->SetValueAsObject("PlayerKey", nullptr);
		StopMovement();

		bFindPlayer = false;
		CLog::Print(L"잊혀짐");
	}

	
}
