#include "CN_StopAnim.h"
#include "../Global.h"
#include "../Character/CCharacter_Base.h"


FString UCN_StopAnim::GetNotifyName_Implementation() const
{
	return "StopAnim";
}

void UCN_StopAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	if (ownerCharacter->bOnCustomMesh)
	{
		ownerCharacter->CustomMontagePause(ownerCharacter->GetMainMesh()->GetAnimInstance()->GetCurrentActiveMontage());

	}
	else
	{
		ownerCharacter->GetMesh()->GetAnimInstance()->Montage_Pause(ownerCharacter->GetMesh()->GetAnimInstance()->GetCurrentActiveMontage());
	}
}
