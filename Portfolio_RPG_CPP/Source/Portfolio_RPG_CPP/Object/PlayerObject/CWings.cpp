#include "CWings.h"
#include "../../Global.h"
#include "../../Character/Player/CCharacter_Player.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"



ACWings::ACWings()
{
	CHelpers::CreateSceneComponent(this, &WingsMesh, "SkeletalMesh", GetRootComponent());
}


void ACWings::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerPlayer = Cast<ACCharacter_Player>(GetOwner());
	CheckNull(OwnerPlayer);
}


void ACWings::SpawnWings(bool input)
{

}


void ACWings::AttachTo(FName InSocketName)
{
	CheckNull(OwnerPlayer);

	AttachToComponent
	(
		OwnerPlayer->GetMainMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}


void ACWings::SetSprint(bool input)
{

}

void ACWings::SetWingsMove(float input)
{
	Wing_L = FVector(0.f, input * 50, input * 30);
	Wing_R = FVector(0.f, input * 50, input * 30);
}



