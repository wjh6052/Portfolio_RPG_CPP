#include "CNS_Combat_AssassinSkill_2.h"
#include "../../../Global.h"

#include "../../../Character/CCharacter_Base.h"
#include "../../../Object/Combat/CCombat_Base.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"


FString UCNS_Combat_AssassinSkill_2::GetNotifyName_Implementation() const
{
	return "AssassinSkill_2";
}

void UCNS_Combat_AssassinSkill_2::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());

	// 무시할 액터 리스트
	TArray<AActor*> outHits;
	outHits.Add(ownerCharacter);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // 캐릭터 포함

	TArray<FHitResult> HitResult;

	bool bhit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		ownerCharacter->GetWorld(),
		ownerCharacter->GetActorLocation(),
		ownerCharacter->GetActorLocation(),
		600.0f,
		ObjectTypes,
		false, // Complex Trace 여부
		outHits, // 무시할 액터 리스트
		EDrawDebugTrace::None, // 디버그 드로잉 옵션
		HitResult,
		true // 실제 충돌 검사 여부	
	);



	
	TargetArr.Empty();
	if (bhit)
	{
		for (FHitResult hit : HitResult)
		{
			ACCharacter_Base* ch = Cast<ACCharacter_Base>(hit.GetActor());

			if (ch)
			{
				TargetArr.AddUnique(hit.GetActor());
			}	
		}
	}
}


void UCNS_Combat_AssassinSkill_2::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CheckNull(MeshComp->GetOwner());

	CheckFalse(Cast<ACCharacter_Base>(MeshComp->GetOwner()));
	ACCharacter_Base* ownerCharacter = Cast<ACCharacter_Base>(MeshComp->GetOwner());



	AActor* selectTarget = nullptr;

	for (int i = 0; i < TargetArr.Num(); i++)
	{
		if (i == 0)
		{
			selectTarget = TargetArr[i];
		}
		else if (FVector::DistSquared(ownerCharacter->GetActorLocation(), selectTarget->GetActorLocation()) > FVector::DistSquared(ownerCharacter->GetActorLocation(), TargetArr[i]->GetActorLocation()))
		{
			selectTarget = TargetArr[i];
		}

	}

	if (selectTarget)
	{
		ownerCharacter->SetActorRotation(selectTarget->GetActorRotation());
		ownerCharacter->SetActorLocation(UKismetMathLibrary::Add_VectorVector(selectTarget->GetActorLocation(), UKismetMathLibrary::Multiply_VectorFloat(selectTarget->GetActorForwardVector(), -50.0f)));			
	}
}


