#include "CBTTask_Alert.h"
#include "../../Global.h"
#include "../../Character/CCharacter_Base.h"
#include "../../AIController/CAIController.h"

#include "AIController.h"



UCBTTask_Alert::UCBTTask_Alert()
{
    NodeName = TEXT("Look Around");

    bNotifyTick = true;
}


EBTNodeResult::Type UCBTTask_Alert::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

    AIController = Cast<ACAIController>(OwnerComp.GetAIOwner());
    AICharacter = Cast<ACCharacter_Base>(AIController->GetPawn());


    // 현재 회전 값 가져오기
    StartRotation = AICharacter->GetActorRotation();


    // 왼쪽 45도 회전
    LeftRotation = StartRotation;
    LeftRotation.Yaw -= LookAngle;


    // 오른쪽 45도 회전
    RightRotation = StartRotation;
    RightRotation.Yaw += LookAngle;

    CurrentTargetRotation = LeftRotation;
    ElapsedTime = 0.0f;  // 시간 초기화

	return EBTNodeResult::InProgress;
}


void UCBTTask_Alert::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    
    CheckNull(AIController);
    CheckNull(AICharacter);


    // 부드럽게 회전
    FRotator NewRotation = FMath::RInterpTo(AICharacter->GetActorRotation(), CurrentTargetRotation, DeltaSeconds, RotationSpeed);
    AICharacter->SetActorRotation(NewRotation);

 
    // 목표 회전에 도달했는지 확인
    if (FMath::Abs(NewRotation.Yaw - CurrentTargetRotation.Yaw) < 0.1f)
    {
        ElapsedTime += DeltaSeconds;  // 대기 시간 증가

        // LookTime이 지나면 방향 변경
        if (ElapsedTime >= NextLookTime)
        {
            ElapsedTime = 0.0f;  // 시간 초기화

            // 현재 회전 방향에 따라 다음 회전 방향으로 변경
            if (CurrentTargetRotation.Equals(LeftRotation))
            {
                CurrentTargetRotation = RightRotation;
            }
            else if (CurrentTargetRotation.Equals(RightRotation))
            {
                CurrentTargetRotation = StartRotation;
            }
            else
            {
                // 원래 방향 복귀 후 종료
                AICharacter->GetStatComponent()->SetStateType(EStateType::Idling);
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                return;
            }
        }
    }


}
