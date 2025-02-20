#include "CN_Combat_EndAttack.h"

#include "../../Global.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"

FString UCN_Combat_EndAttack::GetNotifyName_Implementation() const
{
	return "EndAttack";
}


void UCN_Combat_EndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	ACCharacter_Base* characterOwner = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(characterOwner);


	characterOwner->GetCombatComponent()->Current_Combat->EndAttack();
}