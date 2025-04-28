#include "CNS_Combat_AssassinSkill_1.h"
#include "../../../Global.h"

#include "../../../Character/CCharacter_Base.h"
#include "../../../Object/Combat/CCombat_Base.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"


FString UCNS_Combat_AssassinSkill_1::GetNotifyName_Implementation() const
{
	return "AssassinSkill_1";
}

void UCNS_Combat_AssassinSkill_1::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	


	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // ĳ���� ����

	// ������ ���� ����Ʈ
	TArray<AActor*> outHits;
	outHits.Add(ownerCharacter);

	TArray<FHitResult> HitResult;


	bool bhit = UKismetSystemLibrary::BoxTraceMultiForObjects(
		ownerCharacter->GetWorld(),
		ownerCharacter->GetActorLocation(),
		UKismetMathLibrary::Add_VectorVector(ownerCharacter->GetActorLocation(), UKismetMathLibrary::Multiply_VectorFloat(ownerCharacter->GetActorForwardVector(), RushLength)),
		FVector(50, 50, 50),
		FRotator::ZeroRotator,
		ObjectTypes,
		false, // Complex Trace ����
		outHits, // ������ ���� ����Ʈ
		RushLengthTest ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // ����� ����� �ɼ�
		HitResult,
		true // ���� �浹 �˻� ����	
	);
	

	TargetArr.Empty();
	if (bhit)
	{
		for (FHitResult hit : HitResult)
		{
			ACCharacter_Base* hitCharacter = Cast<ACCharacter_Base>(hit.GetActor());

			if (hitCharacter && (hitCharacter->IsCharacterType(ECharacterType::Enemy) || hitCharacter->IsCharacterType(ECharacterType::Boss)))
			{
				TargetArr.AddUnique(hit.GetActor());
			}
		}
	}
}


void UCNS_Combat_AssassinSkill_1::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	


	for (AActor* target : TargetArr)
	{
		FAttack attackData = ownerCharacter->GetCombatComponent()->Current_Combat->GetCurrentAttackData();

		// ĳ������ ���� ������ �� ũ��Ƽ�� Ȯ�� �߰�
		{
			attackData.AttackDamage.Damage += ownerCharacter->GetStatComponent()->GetCurrentStat().Damage;
			attackData.AttackDamage.CriticalChance += ownerCharacter->GetStatComponent()->GetCurrentStat().Critical_Chance;
		}

		// �������� ����� ���ڷ� ���̾ư��� ȿ������
		ownerCharacter->GetCombatComponent()->ShowDamageText(Cast<ACCharacter_Base>(target)->GetCapsuleComponent(), attackData.AttackDamage.Damage, attackData.AttackDamage.bOnCritical);
		
		// �������� ���� ��ġ�� ���̾ư��� ȿ�� ����
		ownerCharacter->GetCombatComponent()->OnHitImpact(false, Cast<ACCharacter_Base>(target)->GetCapsuleComponent());
		
		// ������ �Է�
		UGameplayStatics::ApplyDamage(target, attackData.AttackDamage.Damage, ownerCharacter->GetController(), ownerCharacter->GetCombatComponent()->Current_Combat, UDamageType::StaticClass());
	}
}

