#include "CN_Combat_SetSkillTarget.h"


#include "../../Global.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"


FString UCN_Combat_SetSkillTarget::GetNotifyName_Implementation() const
{
	return "SetSingleTarget";
}

void UCN_Combat_SetSkillTarget::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(ownerCharacter);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // ĳ���� ����

	// ������ ���� ����Ʈ
	TArray<AActor*> outHits;
	outHits.Add(ownerCharacter);

	TArray<FHitResult> HitResult;

	bool bhit = UKismetSystemLibrary::BoxTraceMultiForObjects(
		ownerCharacter->GetWorld(),
		ownerCharacter->GetActorLocation(),
		UKismetMathLibrary::Add_VectorVector(ownerCharacter->GetActorLocation(), UKismetMathLibrary::Multiply_VectorFloat(ownerCharacter->GetActorForwardVector(), TraceLength)),
		TraceSize,
		FRotator::ZeroRotator,
		ObjectTypes,
		false, // Complex Trace ����
		outHits, // ������ ���� ����Ʈ
		TraceTest ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // ����� ����� �ɼ�
		HitResult,
		true // ���� �浹 �˻� ����
	);


	ownerCharacter->GetCombatComponent()->Current_Combat->SkillTargetArr.Empty();
	if (bhit)
	{
		for (FHitResult hit : HitResult)
		{
			ACCharacter_Base* ch = Cast<ACCharacter_Base>(hit.GetActor());

			if (ch && ch->IsCharacterType(ECharacterType::Enemy))
			{
				ownerCharacter->GetCombatComponent()->Current_Combat->SkillTargetArr.AddUnique(hit.GetActor());
			}
		}
	}
}