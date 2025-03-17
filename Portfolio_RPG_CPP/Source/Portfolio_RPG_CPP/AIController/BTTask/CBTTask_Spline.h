#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTask_Spline.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCBTTask_Spline : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTask_Spline();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
