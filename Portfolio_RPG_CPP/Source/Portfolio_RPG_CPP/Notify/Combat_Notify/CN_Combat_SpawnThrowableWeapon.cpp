#include "CN_Combat_SpawnThrowableWeapon.h"
#include "../../Global.h"

#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"



FString UCN_Combat_SpawnThrowableWeapon::GetNotifyName_Implementation() const
{
	return "SpawnThrowableWeapon";
}

void UCN_Combat_SpawnThrowableWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	ACCharacter_Base* characterOwner = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(characterOwner);


	characterOwner->GetCombatComponent()->Current_Combat->SpawnThrowableWeapon(SocketName);
}
