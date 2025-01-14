#include "CAN_SpawnLandingVFX.h"

#include "../../Global.h"
#include "../../Character/Player/CCharacter_Player.h"


#include "PhysicalMaterials/PhysicalMaterial.h"


FString UCAN_SpawnLandingVFX::GetNotifyName_Implementation() const
{
	return "SpawnLandingVFX";
}


void UCAN_SpawnLandingVFX::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACCharacter_Player* characterOwner = Cast<ACCharacter_Player>(MeshComp->GetOwner());
	CheckNull(characterOwner);
	CheckNull(characterOwner->GetFlightComponent());

	bool onHit = false;
	FHitResult hitResult;
	onHit = characterOwner->GetFlightComponent()->NotifiLineTracetoUpVector(VectorLength, hitResult);
	CheckFalse(onHit);
	FVector HitPoint = hitResult.ImpactPoint;
	FRotator HitNormal = UKismetMathLibrary::MakeRotFromZX(hitResult.ImpactNormal, characterOwner->GetActorForwardVector());

	if (hitResult.PhysMaterial != nullptr)
	{
		characterOwner->GetFlightComponent()->SpawnNiagaraAtLocationOrAttach(false, characterOwner->GetFlightComponent()->GetLandingVFX(hitResult.PhysMaterial->SurfaceType), nullptr, HitPoint, HitNormal);
	}
	else
	{
		characterOwner->GetFlightComponent()->SpawnNiagaraAtLocationOrAttach(false, characterOwner->GetFlightComponent()->GetLandingVFX(EPhysicalSurface::SurfaceType_Default), nullptr, HitPoint, HitNormal);
	}

}