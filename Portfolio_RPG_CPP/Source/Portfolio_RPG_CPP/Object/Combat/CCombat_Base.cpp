#include "CCombat_Base.h"
#include "../../Global.h"
#include "ThrowableWeapon/CThrowableWeapon.h"
#include "../../CGameInstance.h"

#include "Kismet/KismetMaterialLibrary.h"


ACCombat_Base::ACCombat_Base()
{
	PrimaryActorTick.bCanEverTick = false;  // 틱 비활성화 (타이머 사용하므로)

}

void ACCombat_Base::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);

	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());

	CGameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(OwnerCharacter->GetWorld()));



	CombatData = OwnerCharacter->GetCombatComponent()->Current_CombatPlayer_Data.CombatData;
	

	DissolveMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(OwnerCharacter->GetWorld(), CombatData.WeaponMaterial);


	SkillCoolDowns[0] = CombatData.Skill_1_UI.SkillCooldown;
	CurrentSkillCooldowns[0] = SkillCoolDowns[0];

	SkillCoolDowns[1] = CombatData.Skill_2_UI.SkillCooldown;
	CurrentSkillCooldowns[1] = SkillCoolDowns[1];

	SkillCoolDowns[2] = CombatData.Skill_3_UI.SkillCooldown;
	CurrentSkillCooldowns[2] = SkillCoolDowns[2];



	// 0.1초마다 CooldownTick 실행 (반복 실행)
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ACCombat_Base::CooldownTick, 0.1f, true);
}

// 쿨타임 틱
void ACCombat_Base::CooldownTick()
{
	if (CurrentSkillCooldowns[0] >= 0.0f)
	{
		CurrentSkillCooldowns[0] -= 0.1f;
	}
	if (CurrentSkillCooldowns[1] >= 0.0f)
	{
		CurrentSkillCooldowns[1] -= 0.1f;
	}
	if (CurrentSkillCooldowns[2] >= 0.0f)
	{
		CurrentSkillCooldowns[2] -= 0.1f;
	}


}


void ACCombat_Base::StartWeapon()
{
	AttachToComponent(OwnerCharacter->GetMainMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), OwnerCharacter->GetCombatComponent()->Current_CombatPlayer_Data.CombatData.AttachBoneName);
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
	if (bSkill)
	{
		SkillComboNum = -1;
		SkillNum = -1;
		bSkill = false;
	}

	OwnerCharacter->GetStatComponent()->SetStateType(EStateType::Idling);

	ComboNum = 0;


	// 중복방지 초기화
	BeginActor.Empty();
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
	// 중복방지 초기화
	BeginActor.Empty();
}

void ACCombat_Base::ComboAttack()
{
	CheckTrue(bSkill);


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
	// 스킬공격
	if (bSkill)
	{
		SkillComboNum++;	

		switch (SkillNum)
		{
		case 0:
			if (CombatData.Skill_1.Num() - 1 < SkillComboNum)
				EndAttack();
			else
				OwnerCharacter->PlayAnimMontage(CombatData.Skill_1[SkillComboNum].AnimMontage.AnimMontage, CombatData.Skill_1[SkillComboNum].AnimMontage.PlayRate);
			
			break;

		case 1:
			if (CombatData.Skill_2.Num() - 1 < SkillComboNum)
				EndAttack();
			else
				OwnerCharacter->PlayAnimMontage(CombatData.Skill_2[SkillComboNum].AnimMontage.AnimMontage, CombatData.Skill_2[SkillComboNum].AnimMontage.PlayRate);
			
			break;

		case 2:
			if (CombatData.Skill_3.Num() - 1 < SkillComboNum)
				EndAttack();
			else
				OwnerCharacter->PlayAnimMontage(CombatData.Skill_3[SkillComboNum].AnimMontage.AnimMontage, CombatData.Skill_3[SkillComboNum].AnimMontage.PlayRate);
			
			break;
		}
	}
	else// 콤보공격
	{
		if (bCanNextCombo)
		{
			bCanNextCombo = false;
			// 중복방지 초기화
			BeginActor.Empty();


			if (CombatData.Combo_Attack.Num() - 1 >= ++ComboNum)
			{
				if (CombatData.Combo_Attack[ComboNum].AnimMontage.AnimMontage == nullptr)
				{
					EndAttack();
					return;
				}
				else
				{
					OwnerCharacter->PlayAnimMontage(CombatData.Combo_Attack[ComboNum].AnimMontage.AnimMontage, CombatData.Combo_Attack[ComboNum].AnimMontage.PlayRate);
				}
			}
		}
	}
}

void ACCombat_Base::StartSkill(int InSkillNum)
{
	CheckTrue(bSkill);

	bSkill = true;
	SkillNum = InSkillNum;
	SkillComboNum = 0;

	switch (SkillNum)
	{
		case 0:
			OwnerCharacter->PlayAnimMontage(CombatData.Skill_1[SkillComboNum].AnimMontage.AnimMontage, CombatData.Skill_1[SkillComboNum].AnimMontage.PlayRate);
			break;

		case 1:
			OwnerCharacter->PlayAnimMontage(CombatData.Skill_2[SkillComboNum].AnimMontage.AnimMontage, CombatData.Skill_2[SkillComboNum].AnimMontage.PlayRate);
			break;

		case 2:
			OwnerCharacter->PlayAnimMontage(CombatData.Skill_3[SkillComboNum].AnimMontage.AnimMontage, CombatData.Skill_3[SkillComboNum].AnimMontage.PlayRate);
			break;
	}

	

}






FAttack ACCombat_Base::GetCurrentAttackData()
{
	FAttack temp;

	if (bSkill) // 스킬
	{
		switch (SkillNum)
		{
		case 0:
			temp = CombatData.Skill_1[SkillComboNum];			
			break;

		case 1:
			temp = CombatData.Skill_2[SkillComboNum];
			break;

		case 2:
			temp = CombatData.Skill_3[SkillComboNum];
			break;
		}

		temp.AttackDamage.bOnCritical = FMath::RandRange(0, 100) < temp.AttackDamage.CriticalChance;
	}
	else // 콤보공격
	{
		temp = CombatData.Combo_Attack[ComboNum];
		temp.AttackDamage.bOnCritical = FMath::RandRange(0, 100) < temp.AttackDamage.CriticalChance;
		
	}

	return temp;
}




