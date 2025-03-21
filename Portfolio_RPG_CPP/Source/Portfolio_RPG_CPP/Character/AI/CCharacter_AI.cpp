#include "CCharacter_AI.h"
#include "../../Global.h"
#include "../../Object/Combat/CCombat_Base.h"



ACCharacter_AI::ACCharacter_AI()
{
	bUseControllerRotationYaw = true;

	CHelpers::CreateActorComponent(this, &PatrolComponent, "PatrolComponent");
}

void ACCharacter_AI::BeginPlay()
{
	Super::BeginPlay();



	if (DissolveCurve)
	{
		// 머티리얼 다이나믹화
		for (int32 i = 0; i < GetMainMesh()->GetNumMaterials(); i++)
		{
			UMaterialInterface* Material = GetMainMesh()->GetMaterial(i);
			if (Material)
			{
				// 메인메시
				MeshMateriaeDynamic.Add(UMaterialInstanceDynamic::Create(Material, this));
				GetMainMesh()->SetMaterial(i, UMaterialInstanceDynamic::Create(Material, this));

				// 아웃라인
				UMaterialInterface* outLineMaterial = GetOutLineMesh()->GetMaterial(i);
				OutLineMeshMateriaeDynamic = UMaterialInstanceDynamic::Create(outLineMaterial, this);

				if (DissolveMaterial)
				{
					DissolveMaterialeDynamic.Add(UMaterialInstanceDynamic::Create(DissolveMaterial, this));
				}
				
			}
		}
	
		if (DissolveMaterial)
		{
			OutLineDissolveMaterialeDynamic = (UMaterialInstanceDynamic::Create(DissolveMaterial, this));
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
}

void ACCharacter_AI::DyingTimeLineStart()
{
	for (int32 i = 0; i < GetMainMesh()->GetNumMaterials(); i++)
	{
		TArray<UTexture*> Textures;
		MeshMateriaeDynamic[i]->GetUsedTextures(Textures, EMaterialQualityLevel::High, true, ERHIFeatureLevel::SM5, true);
		DissolveMaterialeDynamic[i]->SetTextureParameterValue("BaseTexture", Textures[0]);


		GetMainMesh()->SetMaterial(i, DissolveMaterialeDynamic[i]);
		GetOutLineMesh()->SetMaterial(i, OutLineDissolveMaterialeDynamic);
	}
	
	
	DyingTimeLine.PlayFromStart();
	GetCombatComponent()->Current_Combat->EndWeapon();
}

void ACCharacter_AI::TimelineUpdate(float Value)
{
	for (int32 i = 0; i < GetMainMesh()->GetNumMaterials(); i++)
	{
		DissolveMaterialeDynamic[i]->SetScalarParameterValue("Amount", Value);
		OutLineDissolveMaterialeDynamic->SetScalarParameterValue("Amount", Value);
	}
	

}

void ACCharacter_AI::TimelineFinished()
{
	GetCombatComponent()->Current_Combat->Destroy();
	this->Destroy();

}