#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "../../Character/AI/CCharacter_AI.h"
#include "CBTService_Root.generated.h"


UCLASS()
class PORTFOLIO_RPG_CPP_API UCBTService_Root : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService_Root();


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void SetStateBehaviorKey(EStateType InStateType);
	void SetStatusBehaviorKey(EStatusType InStatusType);




	

	// 플레이어 오브젝트
	class ACCharacter_Base* Player;

	


	class ACAIController* AIController;
	class ACCharacter_AI* OwnerAICharacter;
	class UBlackboardComponent* BlackboardComp;
};
