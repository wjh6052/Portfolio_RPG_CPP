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
		// ��Ƽ���� ���̳���ȭ
		for (int32 i = 0; i < GetMainMesh()->GetNumMaterials(); i++)
		{
			// ���θ޽�
			MeshMateriaeDynamic.Add(UMaterialInstanceDynamic::Create(GetMainMesh()->GetMaterial(i), this));
			GetMainMesh()->SetMaterial(i, UMaterialInstanceDynamic::Create(GetMainMesh()->GetMaterial(i), this));
		}
	
		
	
		// ������Ʈ���� ȣ��� �Լ� ���ε�
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, L"TimelineUpdate");
		DyingTimeLine.AddInterpFloat(DissolveCurve, TimelineCallback);


		// Ÿ�Ӷ����� ������ ȣ��� �Լ� ���ε�0
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
	//for (int32 i = 0; i < GetMainMesh()->GetNumMaterials(); i++)
	//{
	//	if (GetMainMesh() && GetMainMesh()->GetMaterial(i) && MeshMateriaeDynamic[i])
	//	{
	//		if (i < MeshMateriaeDynamic.Num() && IsValid(MeshMateriaeDynamic[i]) && GetMainMesh()->GetMaterial(i))
	//		{
	//			GetMainMesh()->SetMaterial(i, MeshMateriaeDynamic[i]);
	//		}
	//
	//		if (IsValid(GetOutLineMesh()))
	//		{
	//			GetOutLineMesh()->SetVisibility(false);
	//		}
	//	}
	//	
	//}
	
	
	GetCombatComponent()->Current_Combat->EndWeapon();
	DyingTimeLine.PlayFromStart();
}

void ACCharacter_AI::TimelineUpdate(float Value)
{
	//if (MeshMateriaeDynamic.Num() > 0)
	//{
	//	const int32 NumMaterials = MeshMateriaeDynamic.Num();
	//	for (int32 i = 0; i < NumMaterials; i++)
	//	{
	//		if (MeshMateriaeDynamic.IsValidIndex(i) && MeshMateriaeDynamic[i])
	//		{
	//			//MeshMateriaeDynamic[i]->SetScalarParameterValue("Amount", Value);
	//		}
	//	}
	//}
	
	return;

}

void ACCharacter_AI::TimelineFinished()
{
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			if (AISpawner)
				AISpawner->ReSpawn(Spawnindex);

			GetCombatComponent()->Current_Combat->Destroy();


			this->Destroy();
		},
		1, false);

	

}