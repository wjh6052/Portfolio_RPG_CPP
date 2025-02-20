#include "CCombatComponent.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Datas/DA/DA_DamageText.h"
#include "../../Object/Combat/CCombat_Base.h"


#include "NiagaraComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Controller.h"



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
		if (OwnerCharacter_Base->GetStatComponent()->GetPlayerData().CombatType == Row.CombatType)
		{
			Current_CombatPlayer_Data = Row;

			if (Current_CombatPlayer_Data.CombatData.CombatWeapon != nullptr)
			{
				FActorSpawnParameters currentOwner;
				currentOwner.Owner = Cast<AActor>(OwnerCharacter_Base);
				Current_Combat = OwnerCharacter_Base->GetWorld()->SpawnActor<ACCombat_Base>(Current_CombatPlayer_Data.CombatData.CombatWeapon, FVector::ZeroVector, FRotator::ZeroRotator, currentOwner);
				Current_Combat->AttachToComponent(OwnerCharacter_Base->GetMainMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), Current_CombatPlayer_Data.CombatData.AttachBoneName);
			}
			break;
		}
	}

}

void UCCombatComponent::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float InDamage = DamageAmount;
	

	ACCombat_Base* waepon = Cast<ACCombat_Base>(DamageCauser);
	waepon->CombatData;


	

	
	
	
	
	
	
	
}

void UCCombatComponent::AttractToTarget(AActor* Target)
{
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter_Base->GetActorLocation(), Target->GetActorLocation());

	OwnerCharacter_Base->SetActorRotation(
		FRotator(
			OwnerCharacter_Base->GetActorRotation().Pitch,
			rot.Yaw,
			rot.Roll
			));
}


// 데미지를 월드상에 나이아가라 텍스트로 보여줌
void UCCombatComponent::ShowDamageText(float Damage, AController* TargetController, bool bCritical, bool bHealing)
{
	TArray<int32> IntArray;
	float textLocatonY = 0;

	// 문자열을 순회하며 숫자로 변환 후 배열에 추가
	for (TCHAR Character : FString::FromInt(static_cast<int32>(Damage)))
	{
		IntArray.Add(Character - TEXT('0'));
	}

	for (int32 number : IntArray)
	{
		UNiagaraComponent* digitSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			OwnerCharacter_Base->GetWorld(),
			CGameInstance->DamageText_DA->NiagaraSystem,
			OwnerCharacter_Base->GetActorLocation(),
			FRotator(180.0, TargetController->GetControlRotation().Yaw, 0.0),
			FVector(0.5, 0.5, 0.5),
			true,
			true,
			ENCPoolMethod::None,
			true
		);

		//크리티컬 추가 예정
		if(bCritical)
			digitSystem->SetColorParameter(CGameInstance->DamageText_DA->ColorParameterName, CGameInstance->DamageText_DA->CriticalColor);
		else if(bHealing)
			digitSystem->SetColorParameter(CGameInstance->DamageText_DA->ColorParameterName, CGameInstance->DamageText_DA->HealingColor);
		else
			digitSystem->SetColorParameter(CGameInstance->DamageText_DA->ColorParameterName, CGameInstance->DamageText_DA->NormalColor);


		digitSystem->AddLocalOffset(FVector(0.0, textLocatonY, 0.0));
		textLocatonY += 25;


		UNiagaraFunctionLibrary::SetTextureObject(digitSystem, CGameInstance->DamageText_DA->OverrideName, CGameInstance->DamageText_DA->Textures[number]);
	}
}

void UCCombatComponent::SpawnCombat()
{
	if (Current_Combat->bSpawn == false)
	{
		OwnerCharacter_Base->GetStatComponent()->SetStatusType(EStatusType::Combat);


		Current_Combat->StartWeapon();
		OwnerCharacter_Base->PlayAnimMontage(Current_CombatPlayer_Data.CombatData.EquipWeapon.AnimMontage, Current_CombatPlayer_Data.CombatData.EquipWeapon.PlayRate);
	}
	else
	{
		OwnerCharacter_Base->GetStatComponent()->SetStatusType(EStatusType::Unarmed);


		Current_Combat->EndWeapon();
		OwnerCharacter_Base->PlayAnimMontage(Current_CombatPlayer_Data.CombatData.UnequipWeapon.AnimMontage, Current_CombatPlayer_Data.CombatData.UnequipWeapon.PlayRate);
	}

	

}


void UCCombatComponent::OnAttack()
{
	
	Current_Combat->ComboAttack();
	

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

