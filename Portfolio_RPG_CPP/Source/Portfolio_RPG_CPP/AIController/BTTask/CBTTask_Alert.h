#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTask_Alert.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCBTTask_Alert : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTask_Alert();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	// 바라볼 각도
	UPROPERTY(EditAnywhere)
		float LookAngle = 45.0f;

	// 돌아보는 회전 속도
	UPROPERTY(EditAnywhere)
		float RotationSpeed = 5.0f;

	// 한 방향을 본 후 기다리는 시간
	UPROPERTY(EditAnywhere)
		float NextLookTime = 3.0f;

	  

private:
	FRotator StartRotation;
	FRotator LeftRotation;
	FRotator RightRotation;

	bool bLeft = false;
	bool bRight = false;
	bool bCenter = false;

	FRotator TargetRotation;
	float ElapsedTime = 0.0f;

	class ACAIController* AIController;
	class ACCharacter_Base* AICharacter;
};
