#include "CCombat_Base.h"
#include "../../Global.h"
#include "ThrowableWeapon/CThrowableWeapon.h"

#include "Kismet/KismetMaterialLibrary.h"


ACCombat_Base::ACCombat_Base()
{
	

}

void ACCombat_Base::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorHiddenInGame(true);

	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	CombatData = OwnerCharacter->GetCombatComponent()->Current_CombatPlayer_Data.CombatData;
	

	DissolveMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(OwnerCharacter->GetWorld(), CombatData.WeaponMaterial);

}


void ACCombat_Base::StartWeapon()
{
	SetActorHiddenInGame(false);
	bSpawn = true;
	SpawnWeapon();
}

void ACCombat_Base::EndWeapon()
{
	bSpawn = false;
	SpawnWeapon();
}



void ACCombat_Base::StartAttack()
{
	OwnerCharacter->GetStatComponent()->SetStateType(EStateType::Attacking);
}

void ACCombat_Base::EndAttack()
{
	OwnerCharacter->GetStatComponent()->SetStateType(EStateType::Idling);

	ComboNum = 0;


	// 중복방지 초기화
	BeginCharacter.Empty();
}

void ACCombat_Base::SpawnThrowableWeapon(FName InSocketName)
{
	if (CombatData.ThrowableWeaponClass == nullptr)
		return;

	FAttack attackData = GetCurrentAttackData();

	FRotator spawnRotation;

	if (OwnerCharacter->GetCombatComponent()->bLookOn && OwnerCharacter->GetCombatComponent()->LookOn_Character != nullptr)
	{
		spawnRotation = UKismetMathLibrary::FindLookAtRotation(
			OwnerCharacter->GetMainMesh()->GetSocketLocation(InSocketName),
			OwnerCharacter->GetCombatComponent()->LookOn_Character->GetActorLocation()
		);
	}
	else
	{
		if (attackData.bJumpAttack)
		{
			FVector target = (OwnerCharacter->GetMainMesh()->GetSocketLocation(InSocketName) +
				(OwnerCharacter->GetActorForwardVector() * 100.0f) + 
				(OwnerCharacter->GetActorUpVector() * -80.0f)
				);

			spawnRotation = UKismetMathLibrary::FindLookAtRotation(
				OwnerCharacter->GetMainMesh()->GetSocketLocation(InSocketName),
				target
			);
		}
		else
		{
			FVector target = UKismetMathLibrary::Add_VectorVector(OwnerCharacter->GetMainMesh()->GetSocketLocation(InSocketName), 
				UKismetMathLibrary::Multiply_VectorFloat(OwnerCharacter->GetActorForwardVector(), 100.0f)		
				);

			spawnRotation = UKismetMathLibrary::FindLookAtRotation(
				OwnerCharacter->GetMainMesh()->GetSocketLocation(InSocketName),
				target
			);
		}

		FActorSpawnParameters currentOwner;
		currentOwner.Owner = Cast<AActor>(OwnerCharacter);

		ACThrowableWeapon* throwableWeapon = OwnerCharacter->GetWorld()->SpawnActor<ACThrowableWeapon>(
			CombatData.ThrowableWeaponClass,
			OwnerCharacter->GetMainMesh()->GetSocketLocation(InSocketName),
			spawnRotation,
			currentOwner
			);	
	}

	

}

void ACCombat_Base::SetWeaponCollision(bool bOnCollision)
{
}

void ACCombat_Base::ComboAttack()
{
	if (bCanNextComboTiming)
	{
		bCanNextCombo = true;
	}

	if (!OwnerCharacter->GetStatComponent()->IsState(EStateType::Attacking))
	{
		OwnerCharacter->PlayAnimMontage(CombatData.Combo_Attack[ComboNum].AnimMontage.AnimMontage, CombatData.Combo_Attack[ComboNum].AnimMontage.PlayRate);
	}
	
}

void ACCombat_Base::NextComboAttack()
{
	if (bCanNextCombo)
	{
		bCanNextCombo = false;
		// 중복방지 초기화
		BeginCharacter.Empty();


		if (CombatData.Combo_Attack.Num() - 1 >= ++ComboNum)
		{
			if (CombatData.Combo_Attack[ComboNum].AnimMontage.AnimMontage == nullptr)
			{
				EndAttack();
				return;
			}
			else
			{
				SetWeaponCollision(CombatData.Combo_Attack[ComboNum].bOnWeaponCollision);

				OwnerCharacter->PlayAnimMontage(CombatData.Combo_Attack[ComboNum].AnimMontage.AnimMontage, CombatData.Combo_Attack[ComboNum].AnimMontage.PlayRate);
			}
		}
		

		
		
	}
}




FAttack ACCombat_Base::GetCurrentAttackData()
{
	FAttack temp;

	if (bSkill) // 스킬
	{
		//SkillNum;
		//SkillComboNum;

	}
	else // 콤보공격
	{
		temp = CombatData.Combo_Attack[ComboNum];
		temp.AttackDamage.bOnCritical = FMath::RandRange(0, 100) < temp.AttackDamage.CriticalChance;
		
	}

	return temp;
}




