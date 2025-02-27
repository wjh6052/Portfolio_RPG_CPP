#include "CCombat_Base.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/Player/CCharacter_Player.h"
#include "../../Widgets/CWMain.h"
#include "../../Widgets/GameplayUI/CWGameplayUI.h"
#include "ThrowableWeapon/CThrowableWeapon.h"



#include "Kismet/KismetMaterialLibrary.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"



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



	CombatData = OwnerCharacter->GetCombatComponent()->Current_CombatPlayer_Data;
	

	DissolveMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(OwnerCharacter->GetWorld(), CombatData.WeaponMaterial);




	SkillCoolDowns[0] = CombatData.Skill_1_UI.SkillCooldown;
	CurrentSkillCooldowns[0] = SkillCoolDowns[0];
	bOnSkill[0] = false;

	SkillCoolDowns[1] = CombatData.Skill_2_UI.SkillCooldown;
	CurrentSkillCooldowns[1] = SkillCoolDowns[1];
	bOnSkill[1] = false;

	SkillCoolDowns[2] = CombatData.Skill_3_UI.SkillCooldown;
	CurrentSkillCooldowns[2] = SkillCoolDowns[2];
	bOnSkill[2] = false;



	// 0.1초마다 CooldownTick 실행 (반복 실행)
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ACCombat_Base::CooldownTick, 0.1f, true);
}

// 쿨타임 틱
void ACCombat_Base::CooldownTick()
{
	for (int i = 0; i < 3; i++)
	{
		if (CurrentSkillCooldowns[i] > 0.0f)
		{
			CurrentSkillCooldowns[i] -= 0.1f;
			bOnSkill[i] = false;
			
			if (OwnerCharacter->GetCharacterType() == ECharacterType::Player)
				Cast<ACCharacter_Player>(OwnerCharacter)->GetWidgetComponent()->GetMainWidget()->GetGameplayUI()->SetSkillCooldownTime(CombatData.CombatType, i, CurrentSkillCooldowns[i]);
		}
		else
		{
			bOnSkill[i] = true;
		}		
	}

	// 공중 공격 중복 방지
	if (OwnerCharacter->IsMovementMode(EMovementMode::MOVE_Walking))
	{
		bJumpAttack = false;
	}
}


void ACCombat_Base::StartWeapon()
{
	AttachToComponent(OwnerCharacter->GetMainMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), OwnerCharacter->GetCombatComponent()->Current_CombatPlayer_Data.AttachBoneName);
	SetActorHiddenInGame(false);
	bSpawn = true;
	SpawnWeapon();
}

void ACCombat_Base::EndWeapon()
{
	if (bRunToAttack)
		bRunToAttack = !bRunToAttack;

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
		if(SkillSingleTarget)
			Cast<ACCharacter_Base>(SkillSingleTarget)->GetCharacterMovement()->GravityScale = 1.0f;
		OwnerCharacter->GetCharacterMovement()->GravityScale = 1.0f;

		SkillTargetArr.Empty();
		SkillSingleTarget = nullptr;

		// 콜리젼 되돌리기
		OwnerCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
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
		if (bJumpAttack)
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


	if (OwnerCharacter->IsMovementMode(EMovementMode::MOVE_Falling) && !bJumpAttack)
	{
		bJumpAttack = true;
		OwnerCharacter->PlayAnimMontage(CombatData.JumpToAttack.AnimMontage.AnimMontage, CombatData.JumpToAttack.AnimMontage.PlayRate);
		return;
	}

	if (OwnerCharacter->GetStatComponent()->IsSpeedType(ESpeedType::Run))
	{
		bRunToAttack = true;
		OwnerCharacter->PlayAnimMontage(CombatData.RunToAttack.AnimMontage.AnimMontage, CombatData.RunToAttack.AnimMontage.PlayRate);
		return;
	}
	
	

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
	// 스킬 사용중일때 종료
	CheckTrue(bSkill);

	// 스킬 쿨타임일때 종료
	CheckFalse(bOnSkill[InSkillNum]);


	bSkill = true;
	SkillNum = InSkillNum;
	SkillComboNum = 0;
	
	CurrentSkillCooldowns[InSkillNum] = SkillCoolDowns[InSkillNum];

	// 오너캐릭터가 돌진 중 다른 캐릭터와 붙이치지 않도록 설정
	OwnerCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);


	switch (InSkillNum)
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



void ACCombat_Base::MoveTarget(const AActor* InTarget, float InForward, float InRight, float InUp, bool bNotMove, bool bNotTurn)
{
	
	FVector location = InTarget->GetActorLocation() + (InTarget->GetActorForwardVector() * InForward) + (InTarget->GetActorRightVector() * InRight) + (InTarget->GetActorUpVector() * InUp);


	// 이동
	if (!bNotMove)
		OwnerCharacter->SetActorLocation(location);

	// 회전	
	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), InTarget->GetActorLocation());
	
	if(!bNotTurn)
		OwnerCharacter->SetActorRotation(FRotator(OwnerCharacter->GetActorRotation().Pitch, rotator.Yaw, OwnerCharacter->GetActorRotation().Roll));



	
	
}


void ACCombat_Base::DamagesTarget(AActor* InTarget)
{
	ACCharacter_Base* target = Cast<ACCharacter_Base>(InTarget);
	if (target == nullptr)
	{
		return;
	}

	FAttack attackData = OwnerCharacter->GetCombatComponent()->Current_Combat->GetCurrentAttackData();

	// 데미지를 월드상 숫자로 나이아가라 효과스폰
	OwnerCharacter->GetCombatComponent()->ShowDamageText(InTarget, attackData.AttackDamage.Damage, OwnerCharacter->GetController(), attackData.AttackDamage.bOnCritical);

	// 데미지를 받은 위치에 나이아가라 효과 스폰
	OwnerCharacter->GetCombatComponent()->OnHitImpact(false, target->GetMesh());

	// 넉백
	OwnerCharacter->GetCombatComponent()->AttackKnockBack(InTarget, attackData.AttackDamage.KnockbackStrength, attackData.AttackDamage.KnockUpStrength);

	// 데미지 입력
	UGameplayStatics::ApplyDamage(InTarget, attackData.AttackDamage.Damage, OwnerCharacter->GetController(), OwnerCharacter->GetCombatComponent()->Current_Combat, UDamageType::StaticClass());
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
	else if (bRunToAttack)
	{
		temp = CombatData.RunToAttack;
		temp.AttackDamage.bOnCritical = FMath::RandRange(0, 100) < temp.AttackDamage.CriticalChance;
	}
	else// 콤보공격
	{
		temp = CombatData.Combo_Attack[ComboNum];
		temp.AttackDamage.bOnCritical = FMath::RandRange(0, 100) < temp.AttackDamage.CriticalChance;
		
	}

	return temp;
}




