#include "CAIController_Boss.h"
#include "../Global.h"
#include "../Character/AI/CCharacter_AI.h"
#include "../Character/Player/CCharacter_Player.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


void ACAIController_Boss::SetPlayer(AActor* InPlayer)
{
	ACCharacter_Player* player = Cast<ACCharacter_Player>(InPlayer);


	if (player)
	{
		GetBlackboardComponent()->SetValueAsObject("PlayerKey", player);

		bFindPlayer = true;
	}
	else
	{
		GetBlackboardComponent()->SetValueAsObject("PlayerKey", nullptr);

		bFindPlayer = false;
	}
}