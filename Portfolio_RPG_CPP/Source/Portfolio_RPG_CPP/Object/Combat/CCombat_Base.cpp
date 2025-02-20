#include "CCombat_Base.h"
#include "../../Global.h"

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
		temp.bOnCritical = FMath::RandRange(0, 100) < temp.CriticalChance;
		
	}

	return temp;
}




