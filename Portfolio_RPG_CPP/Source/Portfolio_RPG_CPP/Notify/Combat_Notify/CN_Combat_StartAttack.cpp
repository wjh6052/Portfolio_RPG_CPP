#include "CN_Combat_StartAttack.h"

#include "../../Global.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"


FString UCN_Combat_StartAttack::GetNotifyName_Implementation() const
{
	return "StartAttack";
}

void UCN_Combat_StartAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	ACCharacter_Base* characterOwner = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(characterOwner);


	characterOwner->GetCombatComponent()->Current_Combat->StartAttack();
}