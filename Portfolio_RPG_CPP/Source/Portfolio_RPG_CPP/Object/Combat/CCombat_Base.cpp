#include "CCombat_Base.h"
#include "../../Global.h"
#include "../../Character/CCharacter_Base.h"



ACCombat_Base::ACCombat_Base()
{
	CHelpers::CreateSceneComponent(this, &DefaultRoot, "DefaultRoot", GetRootComponent());
	CHelpers::CreateSceneComponent(this, &WeaponMesh, "WeaponMesh", DefaultRoot);


	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ACCombat_Base::BeginPlay()
{
	Super::BeginPlay();
	

	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());

	SpawnWeapon();
	
}

void ACCombat_Base::SpawnWeapon_Implementation()
{
	SetActorHiddenInGame(true);
}

void ACCombat_Base::StartWeapon_Implementation()
{
	SetActorHiddenInGame(false);
}

void ACCombat_Base::EndWeapon_Implementation()
{
	SetActorHiddenInGame(true);
}


