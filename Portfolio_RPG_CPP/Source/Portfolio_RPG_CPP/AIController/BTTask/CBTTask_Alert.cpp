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
    LeftRotation.Yaw = FMath::UnwindDegrees(LeftRotation.Yaw);

    // 오른쪽 45도 회전
    RightRotation = StartRotation;
    RightRotation.Yaw += LookAngle;
    RightRotation.Yaw = FMath::UnwindDegrees(RightRotation.Yaw);

    bLeft = false;
    bRight = false;


    TargetRotation = StartRotation;
    ElapsedTime = 0.0f;  // 시간 초기화  
    bCenter = true;

    AIController->StopMovement();

	return EBTNodeResult::InProgress;
}


void UCBTTask_Alert::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    
    CheckNull(AIController);
    CheckNull(AICharacter);

    

    // 부드럽게 회전
    FRotator CurrentRotation = FMath::RInterpTo(AICharacter->GetActorRotation(), TargetRotation, DeltaSeconds, RotationSpeed);
    AICharacter->SetActorRotation(CurrentRotation);


    // 목표 회전에 도달했는지 확인
    if (FMath::Abs(CurrentRotation.Yaw - TargetRotation.Yaw) < 0.5f)
    {
        ElapsedTime += DeltaSeconds;  // 대기 시간 증가

        // LookTime이 지나면 방향 변경
        if (ElapsedTime >= NextLookTime)
        {
            ElapsedTime = 0.0f;  // 시간 초기화

            // 중앙에 도착
            if (bCenter == true)
            {   
                // 왼쪽 회전
                if (!bLeft)
                {
                    TargetRotation = LeftRotation;
                    bLeft = true;
                    bCenter = false;
                    return;
                }

                // 오른쪽 회전
                if (!bRight)
                {
                    TargetRotation = RightRotation;
                    bRight = true;
                    bCenter = false;
                    return;
                }

                // 끝
                if (bLeft && bRight)
                {
                    AICharacter->GetStatComponent()->SetStateType(EStateType::Idling);
                    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                    return;
                }
            }
            else
            {
                TargetRotation = StartRotation;
                bCenter = true;
            }
        }
    }


}
