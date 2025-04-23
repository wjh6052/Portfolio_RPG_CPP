#include "CNS_AttackTrace.h"
#include "../../Global.h"
#include "../../Character/AI/Boss/CCharacter_Boss.h"
#include "../../Character/Player/CCharacter_Player.h"


FString UCNS_AttackTrace::GetNotifyName_Implementation() const
{
	return "AttackTrace Bear";
}


void UCNS_AttackTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CheckNull(MeshComp->GetOwner());


	ACCharacter_Base* base = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(base);

	if (base->GetOutLineMesh() == MeshComp)
		return;

	TargetArr.Empty();

	


	if (SkillDecalType == ESkillDecalType::Box)
	{
		OnTarget = false;

		return;
	}

	switch (CharacterType)
	{
	case ECharacterType::Boss:
		BossNotify(MeshComp, Animation);
		break;

	default:
		break;
	}

}




void UCNS_AttackTrace::BossNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACCharacter_Boss* ownerBoss = Cast<ACCharacter_Boss>(MeshComp->GetOwner());
	CheckNull(ownerBoss);

	if (SkillDecalType == ESkillDecalType::Box)
		return;


	TArray<AActor*> outHits;
	outHits.Add(ownerBoss);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // 캐릭터 포함

	TArray<FHitResult> hitResult;

	bool bhit = false;
	

	switch (SkillDecalType)
	{
	case ESkillDecalType::Box:
	{
		
	}
		break;


	case ESkillDecalType::Circle:
	{
		bhit = UKismetSystemLibrary::SphereTraceMultiForObjects(
			ownerBoss->GetWorld(),
			ownerBoss->DecalLocation,
			ownerBoss->DecalLocation,
			ownerBoss->DecalSize.Z,
			ObjectTypes,
			false, // Complex Trace 여부
			outHits, // 무시할 액터 리스트
			(bOnDebug) ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 디버그 드로잉 옵션
			hitResult,
			true // 실제 충돌 검사 여부	
		);
	}
		break;

	case ESkillDecalType::HalfCircle:
	{
		bhit = UKismetSystemLibrary::SphereTraceMultiForObjects(
			ownerBoss->GetWorld(),
			ownerBoss->DecalLocation,
			ownerBoss->DecalLocation,
			ownerBoss->DecalSize.Z,
			ObjectTypes,
			false, // Complex Trace 여부
			outHits, // 무시할 액터 리스트
			(bOnDebug) ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // 디버그 드로잉 옵션
			hitResult,
			true // 실제 충돌 검사 여부	
		);
	}
		break;
	}
	

	if (bhit)
	{
		switch (SkillDecalType)
		{
		case ESkillDecalType::Circle:
			for (FHitResult hit : hitResult)
			{
				ACCharacter_Player* target = Cast<ACCharacter_Player>(hit.GetActor());

				if (target)
				{
					TargetArr.AddUnique(target);
				}
			}
			break;


		case ESkillDecalType::HalfCircle:
			for (FHitResult hit : hitResult)
			{
				ACCharacter_Player* target = Cast<ACCharacter_Player>(hit.GetActor());

				if (target)
				{

					FVector toTarget = target->GetActorLocation() - ownerBoss->DecalLocation;
					toTarget.Normalize();

					float dot = FVector::DotProduct(ownerBoss->GetActorForwardVector(), toTarget);

					// Dot ≥ 0 → 앞쪽 180도
					if (dot >= 0.0f)
					{
						TargetArr.AddUnique(target);
					}
				}
			}

		}

		
	}


}


void UCNS_AttackTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (SkillDecalType != ESkillDecalType::Box)
		return;

	ACCharacter_Boss* ownerBoss = Cast<ACCharacter_Boss>(MeshComp->GetOwner());
	CheckNull(ownerBoss);

	TArray<AActor*> outHits;
	outHits.Add(ownerBoss);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // 캐릭터 포함

	
	TArray<FHitResult> hitResult;
	

	bool bhit = UKismetSystemLibrary::BoxTraceMultiForObjects(
		ownerBoss->GetWorld(),
		ownerBoss->GetActorLocation(),
		ownerBoss->GetActorLocation(),
		ownerBoss->CurrentSkill.SkillDecal.BoxTraceSize,
		ownerBoss->GetActorRotation(),
		ObjectTypes,
		false, // Complex Trace 여부
		outHits, // 무시할 액터 리스트
		(bOnDebug) ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None, // 디버그 드로잉 옵션
		hitResult,
		true // 실제 충돌 검사 여부	
		);

	if (bhit)
	{
		for (FHitResult hit : hitResult)
		{
			ACCharacter_Player* target = Cast<ACCharacter_Player>(hit.GetActor());

			if (target)
			{
				TargetArr.AddUnique(target);
			}
		}		
	}

	for (ACCharacter_Base* target : TargetArr)
	{
		if (OnTarget == false && Cast<ACCharacter_Player>(target))
		{
			FVector location = target->GetActorLocation() - ownerBoss->GetActorLocation();

			// 넉백 효과
			target->LaunchCharacter(
				UKismetMathLibrary::Add_VectorVector(
					UKismetMathLibrary::Multiply_VectorFloat(location, ownerBoss->CurrentSkill.SkillDamage.KnockbackStrength),
					UKismetMathLibrary::Multiply_VectorFloat(target->GetActorUpVector(), ownerBoss->CurrentSkill.SkillDamage.KnockUpStrength)
				),
				true,
				true
			);


			// 데미지를 월드상 숫자로 나이아가라 효과스폰
			ownerBoss->GetCombatComponent()->ShowDamageText(target->GetMainMesh(), ownerBoss->CurrentSkill.SkillDamage.Damage, false);


			UGameplayStatics::ApplyDamage(target, ownerBoss->CurrentSkill.SkillDamage.Damage, ownerBoss->GetController(), ownerBoss, UDamageType::StaticClass());

			OnTarget = true;
		}

	}

	
}


void UCNS_AttackTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACCharacter_Base* base = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(base);

	if (base->GetOutLineMesh() == MeshComp)
		return;

	if (SkillDecalType == ESkillDecalType::Box)
		return;


	switch (CharacterType)
	{
	case ECharacterType::Boss:
		BossEndNotify(MeshComp, Animation);
		break;

	default:
		break;
	}
	


}

void UCNS_AttackTrace::BossEndNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACCharacter_Boss* ownerBoss = Cast<ACCharacter_Boss>(MeshComp->GetOwner());
	CheckNull(ownerBoss);

	


	for (ACCharacter_Base* target : TargetArr)
	{
		FVector Direction = ((target->GetActorLocation()) - (ownerBoss->DecalLocation)).GetSafeNormal();

		// 넉백 효과
		target->LaunchCharacter(
			UKismetMathLibrary::Add_VectorVector(
				UKismetMathLibrary::Multiply_VectorFloat(Direction, ownerBoss->CurrentSkill.SkillDamage.KnockUpStrength),
				UKismetMathLibrary::Multiply_VectorFloat(ownerBoss->GetActorUpVector(), ownerBoss->CurrentSkill.SkillDamage.KnockUpStrength)
			),
			true,
			true
		);


		// 데미지를 월드상 숫자로 나이아가라 효과스폰
		ownerBoss->GetCombatComponent()->ShowDamageText(target->GetMainMesh(), ownerBoss->CurrentSkill.SkillDamage.Damage, false);


		UGameplayStatics::ApplyDamage(target, ownerBoss->CurrentSkill.SkillDamage.Damage, ownerBoss->GetController(), ownerBoss, UDamageType::StaticClass());


	}
}