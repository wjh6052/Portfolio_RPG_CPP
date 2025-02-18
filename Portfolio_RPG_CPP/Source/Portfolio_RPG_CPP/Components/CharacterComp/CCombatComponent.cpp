#include "CCombatComponent.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Object/Combat/CCombat_Base.h"




UCCombatComponent::UCCombatComponent()
{
	OwnerCharacter_Base = Cast<ACCharacter_Base>(GetOwner());

}


void UCCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CGameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(OwnerCharacter_Base->GetWorld()));

	
	SwitchWeapon();
	
	
	

}

void UCCombatComponent::SwitchWeapon()
{
	CheckNull(CGameInstance);



	for (FCombatPlayer_DataTable Row : CGameInstance->CombatPlayerData_Arr)
	{
		if (OwnerCharacter_Base->GetStatComponent()->GetPlayerDataTable().CombatType == Row.CombatType)
		{
			Current_CombatPlayer_Data = Row;

			if (Current_CombatPlayer_Data.CombatWeapon != nullptr)
			{
				Current_Combat = OwnerCharacter_Base->GetWorld()->SpawnActor<ACCombat_Base>(Current_CombatPlayer_Data.CombatWeapon, FVector::ZeroVector, FRotator::ZeroRotator);
				Current_Combat->AttachToComponent(OwnerCharacter_Base->GetMainMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), Current_CombatPlayer_Data.AttachBoneName);
			}
			break;
		}
	}

}

void UCCombatComponent::StartCombat()
{
	OwnerCharacter_Base->GetStatComponent()->SetStatusType(EStatusType::Combat);

	OwnerCharacter_Base->PlayAnimMontage(Current_CombatPlayer_Data.EquipWeapon.AnimMontage, Current_CombatPlayer_Data.EquipWeapon.PlayRate);
	Current_Combat->StartWeapon();

}

void UCCombatComponent::EndCombat()
{
	OwnerCharacter_Base->GetStatComponent()->SetStatusType(EStatusType::Unarmed);

	OwnerCharacter_Base->PlayAnimMontage(Current_CombatPlayer_Data.UnequipWeapon.AnimMontage, Current_CombatPlayer_Data.UnequipWeapon.PlayRate);
	Current_Combat->EndWeapon();
}

void UCCombatComponent::OnAttack()
{
	
	OwnerCharacter_Base->PlayAnimMontage(Current_CombatPlayer_Data.Combo_Attack[0].AnimMontage.AnimMontage, Current_CombatPlayer_Data.Combo_Attack[0].AnimMontage.PlayRate);

}

void UCCombatComponent::Skill_1()
{
}

void UCCombatComponent::Skill_2()
{
}

void UCCombatComponent::Skill_3()
{
}

