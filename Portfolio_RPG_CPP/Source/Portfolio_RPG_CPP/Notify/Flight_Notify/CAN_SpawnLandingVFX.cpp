#include "CAN_SpawnLandingVFX.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/Player/CCharacter_Player.h"


#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"



FString UCAN_SpawnLandingVFX::GetNotifyName_Implementation() const
{
	return "SpawnLandingVFX";
}


void UCAN_SpawnLandingVFX::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Character = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(Character);

	UCGameInstance* gameInstance = Cast<UCGameInstance>(Character->GetGameInstance());

	ACCharacter_Player* player = gameInstance->GetPlayerCharacter();
	CheckNull(player);

	bool onHit = false;
	FHitResult hitResult;
	onHit = NotifiLineTracetoUpVector(VectorLength, hitResult);
	CheckFalse(onHit);
	FVector HitPoint = hitResult.ImpactPoint;
	FRotator HitNormal = UKismetMathLibrary::MakeRotFromZX(hitResult.ImpactNormal, Character->GetActorForwardVector());

	if (hitResult.PhysMaterial != nullptr)
	{
		SpawnNiagaraAtLocationOrAttach(false, player->GetFlightComponent()->GetLandingVFX(hitResult.PhysMaterial->SurfaceType), nullptr, HitPoint, HitNormal);
	}
	else
	{
		SpawnNiagaraAtLocationOrAttach(false, player->GetFlightComponent()->GetLandingVFX(EPhysicalSurface::SurfaceType_Default), nullptr, HitPoint, HitNormal);
	}

}

bool UCAN_SpawnLandingVFX::NotifiLineTracetoUpVector(float vectorLength, FHitResult& hitResult)
{
	if (Character == nullptr)
		return false;
	FVector start = Character->GetMainMesh()->GetSocketLocation(SocketName);
	FVector end = (Character->GetActorUpVector() * vectorLength) + start;
	TArray<AActor*> ignores;
	ignores.Add(Character);
	bool bRetrunValue = UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
		false,
		ignores,
		EDrawDebugTrace::None,
		hitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.f
	);
	return bRetrunValue;
}


UNiagaraComponent* UCAN_SpawnLandingVFX::SpawnNiagaraAtLocationOrAttach(bool isAttach, UNiagaraSystem* SystemTemplate, USceneComponent* AttachToComponent, FVector Location, FRotator Rotation)
{
	if (isAttach)
	{
		return UNiagaraFunctionLibrary::SpawnSystemAttached(SystemTemplate, AttachToComponent, L"", Location, Rotation, EAttachLocation::KeepRelativeOffset, true, true);
	}
	else
	{
		return UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SystemTemplate, Location, Rotation, FVector(1.f, 1.f, 1.f));
	}
}
