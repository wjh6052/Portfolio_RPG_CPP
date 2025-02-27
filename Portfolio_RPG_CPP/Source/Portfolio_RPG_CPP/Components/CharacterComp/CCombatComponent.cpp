#include "CCombatComponent.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Character/Player/CCharacter_Player.h"
#include "../../Datas/DA/DA_DamageText.h"
#include "../../Object/Combat/CCombat_Base.h"
#include "../../Widgets/CWMain.h"
#include "../../Widgets/GameplayUI/CWGameplayUI.h"


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
	

	switch (OwnerCharacter_Base->GetCharacterType())
	{
	case ECharacterType::Player:
		PlayerBeginPlay();
		OwnerCharacter_Player = Cast<ACCharacter_Player>(OwnerCharacter_Base);
		break;

	case ECharacterType::Enemy:
		//EnemyBeginPlay();
		break;

	case ECharacterType::Boss:
		//BossBeginPlay();
		break;

	default:
		break;
	}
	
}

void UCCombatComponent::PlayerBeginPlay()
{
	// ���������̺��� ��� ���� ����
	for (FCombatPlayer_DataTable Row : CGameInstance->CombatPlayerData_Arr)
	{
		Current_CombatPlayer_Data = Row;

		FActorSpawnParameters currentOwner;
		currentOwner.Owner = Cast<AActor>(OwnerCharacter_Base);

		ACCombat_Base* CombatWeapon = OwnerCharacter_Base->GetWorld()->SpawnActor<ACCombat_Base>(Current_CombatPlayer_Data.CombatWeapon, FVector::ZeroVector, FRotator::ZeroRotator, currentOwner);
		
		CombatWeapon->CombatData = Row;
		CombatArr.AddUnique(CombatWeapon);
	}

	SwitchWeapon();
}

// ���� ����
void UCCombatComponent::SwitchWeapon()
{
	CheckNull(CGameInstance);


	for (FCombatPlayer_DataTable Row : CGameInstance->CombatPlayerData_Arr)
	{
		if (OwnerCharacter_Base->GetStatComponent()->GetPlayerData().CombatType == Row.CombatType)
		{
			Current_CombatPlayer_Data = Row;

			for (ACCombat_Base* RowCombat : CombatArr)
			{
				if (Current_CombatPlayer_Data.CombatType == RowCombat->CombatData.CombatType)
				{
					Current_Combat = RowCombat;
					if (OwnerCharacter_Player)
					{
						OwnerCharacter_Player->GetWidgetComponent()->GetMainWidget()->GetGameplayUI()->SetWidgetSwitcher(OwnerCharacter_Base->GetStatComponent()->IsStatus(EStatusType::Combat), Current_Combat->CombatData.CombatType);
					}
					return;
				}
			}		
		}
	}

}

// ������ ����
void UCCombatComponent::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float InDamage = DamageAmount;
	

	ACCombat_Base* waepon = Cast<ACCombat_Base>(DamageCauser);
	waepon->CombatData;


	

	
	
	
	
	
	
	
}

// ��Ʈ ����Ʈ
void UCCombatComponent::OnHitImpact(bool bThrowable, UPrimitiveComponent* OverlappedComponent)
{
	if (bThrowable)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			OwnerCharacter_Base->GetWorld(),
			Current_CombatPlayer_Data.ImpactFlaresThrowable,
			OverlappedComponent->K2_GetComponentLocation(),
			UKismetMathLibrary::Conv_VectorToRotator(OwnerCharacter_Base->GetMainMesh()->GetForwardVector()),
			Current_CombatPlayer_Data.ImpactFlaresThrowableScale
		);
	}
	else
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			OwnerCharacter_Base->GetWorld(),
			Current_CombatPlayer_Data.ImpactFlares,
			OverlappedComponent->K2_GetComponentLocation(),
			UKismetMathLibrary::Conv_VectorToRotator(OwnerCharacter_Base->GetMainMesh()->GetForwardVector()),
			Current_CombatPlayer_Data.ImpactFlaresScale
		);
	}
}

// �˹�
void UCCombatComponent::AttackKnockBack(AActor* DamageOwner, float InKnockBackForward, float InKnockBackUp)
{
	ACharacter* damageCharacter = Cast<ACharacter>(DamageOwner);
	damageCharacter->LaunchCharacter(
		UKismetMathLibrary::Add_VectorVector(
			UKismetMathLibrary::Multiply_VectorFloat(OwnerCharacter_Base->GetActorForwardVector(), InKnockBackForward),
			UKismetMathLibrary::Multiply_VectorFloat(OwnerCharacter_Base->GetActorUpVector(), InKnockBackUp)
		),
		true,
		true
	);
}

// ���� �������� ���Ƽ���
void UCCombatComponent::AttractToTarget(AActor* Target)
{
	if (bLookOn)
	{
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter_Base->GetActorLocation(), LookOn_Character->GetActorLocation());

		OwnerCharacter_Base->SetActorRotation(
			FRotator(
				OwnerCharacter_Base->GetActorRotation().Pitch,
				rot.Yaw,
				rot.Roll
			));
	}
	else 
	{
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter_Base->GetActorLocation(), Target->GetActorLocation());

		OwnerCharacter_Base->SetActorRotation(
			FRotator(
				OwnerCharacter_Base->GetActorRotation().Pitch,
				rot.Yaw,
				rot.Roll
			));
	}
	
}


// �������� ����� ���̾ư��� �ؽ�Ʈ�� ������
void UCCombatComponent::ShowDamageText(AActor* DamageOwner, float Damage, AController* TargetController, bool bCritical, bool bHealing)
{
	TArray<int32> IntArray;
	float textLocatonY = 0;

	// ���ڿ��� ��ȸ�ϸ� ���ڷ� ��ȯ �� �迭�� �߰�
	for (TCHAR Character : FString::FromInt(static_cast<int32>(Damage)))
	{
		IntArray.Add(Character - TEXT('0'));
	}

	for (int32 number : IntArray)
	{		
		UNiagaraComponent* digitSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			DamageOwner->GetWorld(),
			CGameInstance->DamageText_DA->NiagaraSystem,
			DamageOwner->GetActorLocation(),
			FRotator(180.0, TargetController->GetControlRotation().Yaw, 0.0),
			FVector(0.5, 0.5, 0.5),
			true,
			true,
			ENCPoolMethod::None,
			true
		);


		//ũ��Ƽ��
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


void UCCombatComponent::EquipCombat()
{
	if (Current_Combat->bSpawn == false) // ����
	{
		OwnerCharacter_Base->GetStatComponent()->SetStatusType(EStatusType::Combat);


		Current_Combat->StartWeapon();
		OwnerCharacter_Base->PlayAnimMontage(Current_CombatPlayer_Data.EquipWeapon.AnimMontage, Current_CombatPlayer_Data.EquipWeapon.PlayRate);
	
		// ���� ���� ����
		OwnerCharacter_Base->GetCharacterMovement()->JumpZVelocity = OwnerCharacter_Base->GetStatComponent()->GetPlayerData().JumpVelocity;	
	}
	else // ����
	{
		OwnerCharacter_Base->GetStatComponent()->SetStatusType(EStatusType::Unarmed);


		Current_Combat->EndWeapon();
		OwnerCharacter_Base->PlayAnimMontage(Current_CombatPlayer_Data.UnequipWeapon.AnimMontage, Current_CombatPlayer_Data.UnequipWeapon.PlayRate);
		
		// ���� ���� ����
		OwnerCharacter_Base->GetCharacterMovement()->JumpZVelocity = 420.0f;
	}

	

	if (OwnerCharacter_Player)
	{
		OwnerCharacter_Player->GetWidgetComponent()->GetMainWidget()->GetGameplayUI()->SetWidgetSwitcher(OwnerCharacter_Base->GetStatComponent()->IsStatus(EStatusType::Combat), Current_Combat->CombatData.CombatType);
	}
}


// ���콺 ��Ŭ��
void UCCombatComponent::OnAttack()
{
	
	Current_Combat->ComboAttack();
	

}

// ��ų 1��
void UCCombatComponent::Skill_1()
{
	Current_Combat->StartSkill(0);
}

// ��ų 2��
void UCCombatComponent::Skill_2()
{
	Current_Combat->StartSkill(1);
}

// ��ų 3��
void UCCombatComponent::Skill_3()
{
	Current_Combat->StartSkill(2);
}

