#include "CN_Combat_NextCombo.h"


#include "../../Global.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"




FString UCN_Combat_NextCombo::GetNotifyName_Implementation() const
{
	return "NextCombo";
}

void UCN_Combat_NextCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	ACCharacter_Base* characterOwner = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(characterOwner);


	characterOwner->GetCombatComponent()->Current_Combat->NextComboAttack();
}