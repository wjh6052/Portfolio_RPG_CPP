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
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // 캐릭터 포함

	// 무시할 액터 리스트
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
		false, // Complex Trace 여부
		outHits, // 무시할 액터 리스트
		RushLengthTest ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 디버그 드로잉 옵션
		HitResult,
		true // 실제 충돌 검사 여부	
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

		// 캐릭터의 스텟 데미지 및 크리티컬 확률 추가
		{
			attackData.AttackDamage.Damage += ownerCharacter->GetStatComponent()->GetCurrentStat().Damage;
			attackData.AttackDamage.CriticalChance += ownerCharacter->GetStatComponent()->GetCurrentStat().Critical_Chance;
		}

		// 데미지를 월드상 숫자로 나이아가라 효과스폰
		ownerCharacter->GetCombatComponent()->ShowDamageText(Cast<ACCharacter_Base>(target)->GetCapsuleComponent(), attackData.AttackDamage.Damage, attackData.AttackDamage.bOnCritical);
		
		// 데미지를 받은 위치에 나이아가라 효과 스폰
		ownerCharacter->GetCombatComponent()->OnHitImpact(false, Cast<ACCharacter_Base>(target)->GetCapsuleComponent());
		
		// 데미지 입력
		UGameplayStatics::ApplyDamage(target, attackData.AttackDamage.Damage, ownerCharacter->GetController(), ownerCharacter->GetCombatComponent()->Current_Combat, UDamageType::StaticClass());
	}
}

