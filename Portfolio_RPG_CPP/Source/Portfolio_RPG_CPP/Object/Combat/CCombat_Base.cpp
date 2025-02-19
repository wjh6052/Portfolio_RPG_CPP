#include "CCombat_Base.h"
#include "../../Global.h"




ACCombat_Base::ACCombat_Base()
{
	

}

void ACCombat_Base::BeginPlay()
{
	Super::BeginPlay();
	

	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	SetActorHiddenInGame(true);
	
}


void ACCombat_Base::StartWeapon()
{
	SetActorHiddenInGame(false);
}

void ACCombat_Base::EndWeapon()
{
	SetActorHiddenInGame(true);
}



