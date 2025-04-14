#include "CCharacter_AI.h"
#include "../../Global.h"
#include "../../Object/Combat/CCombat_Base.h"
#include "../../Object/AISpawner/CAISpawner.h"



#include "Components/WidgetComponent.h"


ACCharacter_AI::ACCharacter_AI()
{
	bUseControllerRotationYaw = true;

	CHelpers::CreateActorComponent(this, &PatrolComponent, "PatrolComponent");


	CHelpers::CreateSceneComponent<UWidgetComponent>(this, &AINameWidget, "AINameWidget", RootComponent);


	TSubclassOf<class UCW_AI_Name> aINameClass;
	CHelpers::GetClass<UCW_AI_Name>(&aINameClass, "WidgetBlueprint'/Game/Widgets/AIName/CWB_AIName'");
	
	AINameWidget->SetWidgetClass(aINameClass);
	
	AINameWidget->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	AINameWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACCharacter_AI::BeginPlay()
{
	Super::BeginPlay();

	CW_AIName = Cast<UCW_AI_Name>(AINameWidget->GetWidget());


	if (DissolveCurve)
	{
		MeshMateriaeDynamic.Empty();
		// 머티리얼 다이나믹화
		for (int32 i = 0; i < GetMainMesh()->GetNumMaterials(); i++)
		{
			// 메인메시
			MeshMateriaeDynamic.Add(UMaterialInstanceDynamic::Create(GetMainMesh()->GetMaterial(i), this));
			GetMainMesh()->SetMaterial(i, UMaterialInstanceDynamic::Create(GetMainMesh()->GetMaterial(i), this));
		}
	
		
	
		// 업데이트마다 호출될 함수 바인딩
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, L"TimelineUpdate");
		DyingTimeLine.AddInterpFloat(DissolveCurve, TimelineCallback);


		// 타임라인이 끝나고 호출될 함수 바인딩0
		FOnTimelineEvent TimelineFinishedCallback;
		TimelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));
		DyingTimeLine.SetTimelineFinishedFunc(TimelineFinishedCallback);
	
		
		DyingTimeLine.SetLooping(false);
		DyingTimeLine.SetPlayRate(TimeLinePlayRate);
	}
}

void ACCharacter_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DyingTimeLine.TickTimeline(DeltaTime);


	AINameWidget->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(AINameWidget->GetComponentLocation(), GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation()));
}

void ACCharacter_AI::DyingTimeLineStart()
{
	for (int32 i = 0; i < GetMainMesh()->GetNumMaterials(); i++)
	{
		GetMainMesh()->SetMaterial(i, MeshMateriaeDynamic[i]);
		GetOutLineMesh()->SetVisibility(false);
	}
	
	
	DyingTimeLine.PlayFromStart();
	GetCombatComponent()->Current_Combat->EndWeapon();
}

void ACCharacter_AI::TimelineUpdate(float Value)
{
	for (int32 i = 0; i < MeshMateriaeDynamic.Num(); i++)
	{
		if (MeshMateriaeDynamic[i]->IsValidLowLevel())
		{
			float dummyValue = 0;
			if (MeshMateriaeDynamic[i]->GetScalarParameterValue(FMaterialParameterInfo("Amount"), dummyValue))
				MeshMateriaeDynamic[i]->SetScalarParameterValue("Amount", Value);
		}
			
	}
	

}

void ACCharacter_AI::TimelineFinished()
{
	if (AISpawner)
		AISpawner->ReSpawn(Spawnindex);

	GetCombatComponent()->Current_Combat->Destroy();
	this->Destroy();

}