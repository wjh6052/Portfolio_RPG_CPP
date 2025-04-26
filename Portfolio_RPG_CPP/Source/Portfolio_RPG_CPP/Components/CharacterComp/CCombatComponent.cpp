#include "CCombatComponent.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Character/Player/CCharacter_Player.h"
#include "../../Character/AI/Enemy/CCharacter_Enemy.h"
#include "../../Character/AI/Boss/CCharacter_Boss.h"
#include "../../Datas/DA/DA_DamageText.h"
#include "../../Object/Combat/CCombat_Base.h"
#include "../../Object/Interaction/CItemInteraction_Material.h"
#include "../../Object/Interaction/CItemInteraction_Money.h"
#include "../../Widgets/CWMain.h"
#include "../../Widgets/GameplayUI/CWGameplayUI.h"


#include "NiagaraComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetMathLibrary.h"
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
		OwnerCharacter_Player = Cast<ACCharacter_Player>(OwnerCharacter_Base);
		PlayerBeginPlay();
		break;

	case ECharacterType::Enemy:
		OwnerCharacter_Enemy = Cast<ACCharacter_Enemy>(OwnerCharacter_Base);
		EnemyBeginPlay();
		break;

	case ECharacterType::Boss:
		OwnerCharacter_Boss = Cast<ACCharacter_Boss>(OwnerCharacter_Base);
		BossBeginPlay();
		break;

	default:
		break;
	}
	
}

void UCCombatComponent::PlayerBeginPlay()
{
	// 데이터테이블의 모든 무기 스폰
	for (FPlayer_DataTable Row : CGameInstance->Player_Data_Arr)
	{		
		FActorSpawnParameters currentOwner;
		currentOwner.Owner = Cast<AActor>(OwnerCharacter_Base);

		Current_CombatData = Row.Player_CombatData.CombatData;
		ACCombat_Base* CombatWeapon = OwnerCharacter_Base->GetWorld()->SpawnActor<ACCombat_Base>(Row.Player_CombatData.CombatData.CombatWeapon, FVector::ZeroVector, FRotator::ZeroRotator, currentOwner);
		
		CombatWeapon->CombatData = Row.Player_CombatData.CombatData;
		CombatArr.AddUnique(CombatWeapon);
	}


	for (FPlayer_DataTable data : CGameInstance->Player_Data_Arr)
	{
		for (ACCombat_Base* combat : CombatArr)
		{
			if (data.Player_CombatData.CombatData.CombatType == combat->CombatData.CombatType)
			{			
				Current_CombatData = combat->CombatData;
				Current_Combat = combat;
				return;
			}
		}
	}
}

void UCCombatComponent::EnemyBeginPlay()
{
	// 데이터테이블의 에너미의 이름에 맞는 무기 스폰
	for (FEnemy_DataTable Row : CGameInstance->Enemy_Data_Arr)
	{
		if (OwnerCharacter_Enemy->EnemyName == Row.EnemyName)
		{
			FActorSpawnParameters currentOwner;
			currentOwner.Owner = Cast<AActor>(OwnerCharacter_Enemy);

			Current_CombatData = Row.CombatData;
			ACCombat_Base* CombatWeapon = OwnerCharacter_Base->GetWorld()->SpawnActor<ACCombat_Base>(Row.CombatData.CombatWeapon, FVector::ZeroVector, FRotator::ZeroRotator, currentOwner);

			CombatWeapon->CombatData = Row.CombatData;
			Current_Combat = CombatWeapon;

			// 테스트
			Current_Combat->SetActorHiddenInGame(false);
			Current_Combat->AttachToComponent(OwnerCharacter_Enemy->GetMainMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), Current_CombatData.EquipBoneName);
			break;
		}	
	}

}

void UCCombatComponent::BossBeginPlay()
{
	
}

// 무기 변경
void UCCombatComponent::SwitchWeapon(ECombatType InCombatType)
{
	CheckNull(CGameInstance);

	if (InCombatType == ECombatType::None && Current_Combat->bSpawn == true)
	{
		UnequipCombat();

		return;
	}

	if (InCombatType == Current_CombatData.CombatType && Current_Combat->bSpawn == false)
	{
		EquipCombat();

		return;
	}

	UnequipCombat(false);

	// 캐릭터 변경
	for (FPlayer_DataTable playerdata : CGameInstance->Player_Data_Arr)
	{
		if (playerdata.Player_CombatData.CombatData.CombatType == InCombatType)
		{
			CGameInstance->CombatType = InCombatType;
			OwnerCharacter_Player->GetStatComponent()->PlayerDataSetting();
			break;
		}
	}

	


	// 무기 변경
	for (ACCombat_Base* Row : CombatArr)
	{
		if (InCombatType == Row->CombatData.CombatType)
		{
			Current_CombatData = Row->CombatData;
			Current_Combat = Row;
			
			EquipCombat();
			break;
		}
	}

}

// 데미지 적용
void UCCombatComponent::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (OwnerCharacter_Base->GetStatComponent()->IsState(EStateType::Dying))
		return;

	float InDamage = DamageAmount;
	
	
	// 오너가 보스일 경우 플레이어의 UI의 보스HP바를 수정
	if (OwnerCharacter_Base->GetCharacterType() == ECharacterType::Boss)
	{
		CGameInstance->GetPlayerCharacter()->GetWidgetComponent()->GetMainWidget()->GetGameplayUI()->AddDamageBossHpBar(InDamage);


	}


	// 죽었을때
	if (OwnerCharacter_Base->GetStatComponent() && OwnerCharacter_Base->GetStatComponent()->AddDamage(InDamage))
	{
		CharacterDeath(DamageCauser);
		return;
	}
	


	
	if (OwnerCharacter_Base->GetStatComponent()&& OwnerCharacter_Base->GetStatComponent()->GetCurrentStat().HP_Max * (OwnerCharacter_Base->GetStatComponent()->GetCurrentStat().Stance / 100.f) < InDamage)
	{
		PlayHitReaction();
	}
	
	
	
	
	
}

// 히트 임팩트
void UCCombatComponent::OnHitImpact(bool bThrowable, UPrimitiveComponent* OverlappedComponent)
{
	if (bThrowable)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			OwnerCharacter_Base->GetWorld(),
			Current_CombatData.ImpactFlaresThrowable,
			OverlappedComponent->K2_GetComponentLocation(),
			UKismetMathLibrary::Conv_VectorToRotator(OwnerCharacter_Base->GetMainMesh()->GetForwardVector()),
			Current_CombatData.ImpactFlaresThrowableScale
		);
	}
	else
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			OwnerCharacter_Base->GetWorld(),
			Current_CombatData.ImpactFlares,
			OverlappedComponent->K2_GetComponentLocation(),
			UKismetMathLibrary::Conv_VectorToRotator(OwnerCharacter_Base->GetMainMesh()->GetForwardVector()),
			Current_CombatData.ImpactFlaresScale
		);
	}
}

// 넉백
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

// 히트 애니메이션 재생
void UCCombatComponent::PlayHitReaction()
{
	CheckNull(Current_Combat);

	if (!Current_Combat->bSkill && OwnerCharacter_Player)
		return;

	if (bIsPlayerHitTime)
		return;

	Current_Combat->EndAttack();
	OwnerCharacter_Base->StopAnimMontage();

	OwnerCharacter_Base->GetStatComponent()->SetStateType(EStateType::Hitted);
	OwnerCharacter_Base->PlayAnimMontage(Current_CombatData.Hit_Montage.AnimMontage, Current_CombatData.Hit_Montage.PlayRate);

	if (OwnerCharacter_Player)
	{
		bIsPlayerHitTime = true;
		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(timerHandle, [this]()
			{
				bIsPlayerHitTime = false;
			},
			3.0f, false);
	}
}

// 죽었을때
void UCCombatComponent::CharacterDeath(AActor* DamageCauser)
{	
	switch (OwnerCharacter_Base->GetCharacterType())
	{
	case ECharacterType::Player:
	{
		OwnerCharacter_Player->GetStatComponent()->Desh_Ragdoll();


		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.5f);

		FTimerHandle timerGameEnd;
		GetWorld()->GetTimerManager().SetTimer(timerGameEnd, [this]()
			{
				UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.f);
				OwnerCharacter_Player->GetWidgetComponent()->GetMainWidget()->SetWidgetSwitcher(ECurrentUi::PlayerDie);
			},
			2.0f, false);
	}
		break;

	case ECharacterType::Enemy:
		for (FQuest_DataTable arr : CGameInstance->QuestData_Arr)
		{
			// 퀘스트의 상태가 진행 중 인지 && 몬스터의 킬이 있는지
			if (arr.QuestState == EQuestState::InProgress && arr.QuestDetails.bRequireMonsterKill == true)
			{
				for (int i = 0; i < arr.QuestDetails.MonsterTargets.Num(); i++)
				{
					// 잡아야하는 몬스터의 이름이 오너캐릭터와 동일한지 확인
					if (arr.QuestDetails.MonsterTargets[i].EnemyName == OwnerCharacter_Enemy->EnemyName)
					{
						if (arr.QuestDetails.MonsterTargets[i].CurrentKillCount + 1 <= arr.QuestDetails.MonsterTargets[i].KillCount)
						{
							arr.QuestDetails.MonsterTargets[i].CurrentKillCount++;
							CGameInstance->UpdateQuestDate(arr, EQuestDetailsUpdateType::Monster, UEnum::GetDisplayValueAsText(arr.QuestDetails.MonsterTargets[i].EnemyName).ToString());
						}

						break;

					}

				}
			}

		}
		break;


	case ECharacterType::Boss:
		for (FQuest_DataTable arr : CGameInstance->QuestData_Arr)
		{
			// 퀘스트의 상태가 진행 중 인지 && 몬스터의 킬이 있는지
			if (arr.QuestState == EQuestState::InProgress && arr.QuestDetails.bRequireBossKill == true)
			{
				for (int i = 0; i < arr.QuestDetails.BossTargets.Num(); i++)
				{
					// 잡아야하는 몬스터의 이름이 오너캐릭터와 동일한지 확인
					if (arr.QuestDetails.BossTargets[i].BossName == OwnerCharacter_Boss->BossName)
					{
						if (arr.QuestDetails.BossTargets[i].CurrentKillCount + 1 <= arr.QuestDetails.BossTargets[i].KillCount)
						{
							arr.QuestDetails.BossTargets[i].CurrentKillCount++;
							CGameInstance->UpdateQuestDate(arr, EQuestDetailsUpdateType::Boss, UEnum::GetDisplayValueAsText(arr.QuestDetails.BossTargets[i].BossName).ToString());
						}

						break;
					}

				}
			}

		}
		break;
	}



	

	// 죽었을때 애니메이션
	if(OwnerCharacter_Base->GetCharacterType() == ECharacterType::Boss && OwnerCharacter_Boss && OwnerCharacter_Boss->Boss_DataTable.BossDeathAnimMontage.AnimMontage)
	{
		if (OwnerCharacter_Boss->bOnCustomMesh)
		{
			OwnerCharacter_Boss->CustomPlayAnimMontage(OwnerCharacter_Boss->Boss_DataTable.BossDeathAnimMontage);
		}
		else
		{
			OwnerCharacter_Boss->PlayAnimMontage(OwnerCharacter_Boss->Boss_DataTable.BossDeathAnimMontage.AnimMontage, OwnerCharacter_Boss->Boss_DataTable.BossDeathAnimMontage.PlayRate);
		}
		
	}
	else
	{
		OwnerCharacter_Base->PlayAnimMontage(Current_CombatData.Die_Montage.AnimMontage, Current_CombatData.Die_Montage.PlayRate);
	}

	OwnerCharacter_Base->GetStatComponent()->SetStateType(EStateType::Dying);
	//OwnerCharacter_Base->GetMainMesh()->SetSimulatePhysics(true);


	DropLootOnDeath();
}

void UCCombatComponent::DropLootOnDeath()
{
	float Power = 0;

	if (OwnerCharacter_Base->GetCharacterType() == ECharacterType::Enemy)
	{
		for (FItemType row : OwnerCharacter_Enemy->Enemy_DataTable.EnemyDropItemArr)
		{
			switch (row.ItemCategory)
			{
			case EItemCategory::Material:
				{
					if (row.DropRate >= FMath::FRand())
					{
						ACItemInteraction_Material* item = GetWorld()->SpawnActor<ACItemInteraction_Material>   (ACItemInteraction_Material::StaticClass(), OwnerCharacter_Enemy->GetActorLocation(), FRotator::ZeroRotator);

						item->FInteractionItemMaterial.StarRating = row.StarRating;
						item->FInteractionItemMaterial.ItemUseType = row.ItemUseType;
						item->FInteractionItemMaterial.MaterialNum = row.ItemCount;
						item->ItemName = L"이름";

						item->SetMaterialItemIcon();
						Power = OwnerCharacter_Enemy->Enemy_DataTable.DropPower;

						FVector Impulse = FVector(FMath::RandRange(-Power, Power), FMath::RandRange(-Power, Power), 500);
						item->GetMesh()->AddImpulse(Impulse);
					}
					

					break;
				}
			case EItemCategory::Equipment:
				break;
			}
		}
		
		if (OwnerCharacter_Enemy->Enemy_DataTable.LootMoneyCount > 0 && OwnerCharacter_Enemy->Enemy_DataTable.MoneyDropRate >= FMath::FRand())
		{
			ACItemInteraction_Money* money = GetWorld()->SpawnActor<ACItemInteraction_Money>(ACItemInteraction_Money::StaticClass(), OwnerCharacter_Enemy->GetActorLocation(), FRotator::ZeroRotator);
			money->Money = OwnerCharacter_Enemy->Enemy_DataTable.LootMoneyCount;

			FVector Impulse = FVector(FMath::RandRange(-Power, Power), FMath::RandRange(-Power, Power), 500);
			money->GetMesh()->AddImpulse(Impulse);
		}

	}
	else if (OwnerCharacter_Base->GetCharacterType() == ECharacterType::Boss)
	{
		Power = OwnerCharacter_Boss->Boss_DataTable.DropPower;

		for (FItemType row : OwnerCharacter_Boss->Boss_DataTable.DropItemArr)
		{
			switch (row.ItemCategory)
			{
			case EItemCategory::Material:
			{
				if (row.DropRate >= FMath::FRand())
				{
					ACItemInteraction_Material* item = GetWorld()->SpawnActor<ACItemInteraction_Material>(ACItemInteraction_Material::StaticClass(), OwnerCharacter_Boss->GetActorLocation(), FRotator::ZeroRotator);

					item->FInteractionItemMaterial.StarRating = row.StarRating;
					item->FInteractionItemMaterial.ItemUseType = row.ItemUseType;
					item->FInteractionItemMaterial.MaterialNum = row.ItemCount;
					item->ItemName = L"이름";

					item->SetMaterialItemIcon();


					FVector Impulse = FVector(FMath::RandRange(-Power, Power), FMath::RandRange(-Power, Power), 500);
					item->GetMesh()->AddImpulse(Impulse);
				}


				break;
			}
			case EItemCategory::Equipment:
				break;
			}
		}

		
	}

}

// 적의 뱡향으로 돌아서기
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


// 데미지를 월드상에 나이아가라 텍스트로 보여줌
void UCCombatComponent::ShowDamageText(UPrimitiveComponent* OverlappedComponent, float Damage, bool bCritical, bool bHealing)
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
			OverlappedComponent->K2_GetComponentLocation(),
			FRotator(180.0, CGameInstance->GetPlayerCharacter()->GetControlRotation().Yaw, 0.0),
			FVector(0.5, 0.5, 0.5),
			true,
			true,
			ENCPoolMethod::None,
			true
		);


		//크리티컬
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


// 무기를 꺼낼 때
void UCCombatComponent::EquipCombat(bool bPlayMontage)
{

	OwnerCharacter_Base->GetStatComponent()->SetStatusType(EStatusType::Combat);


	Current_Combat->StartWeapon();
	if (bPlayMontage)
		OwnerCharacter_Base->PlayAnimMontage(Current_CombatData.EquipWeapon.AnimMontage, Current_CombatData.EquipWeapon.PlayRate);
	
	// 점프 높이 설정
	OwnerCharacter_Base->GetCharacterMovement()->JumpZVelocity = OwnerCharacter_Base->GetStatComponent()->GetPlayerData().Stat.JumpVelocity;


	

	if (OwnerCharacter_Player)
	{
		OwnerCharacter_Player->GetWidgetComponent()->GetMainWidget()->GetGameplayUI()->SetWidgetSwitcher(OwnerCharacter_Base->GetStatComponent()->IsStatus(EStatusType::Combat), Current_Combat->CombatData.CombatType);
	}
}

// 무기를 넣을 때
void UCCombatComponent::UnequipCombat(bool bPlayMontage)
{
	OwnerCharacter_Base->GetStatComponent()->SetStatusType(EStatusType::Unarmed);


	Current_Combat->EndWeapon();
	if (bPlayMontage)
		OwnerCharacter_Base->PlayAnimMontage(Current_CombatData.UnequipWeapon.AnimMontage, Current_CombatData.UnequipWeapon.PlayRate);

	// 점프 높이 설정
	OwnerCharacter_Base->GetCharacterMovement()->JumpZVelocity = 420.0f;

	if (OwnerCharacter_Player)
	{
		OwnerCharacter_Player->GetWidgetComponent()->GetMainWidget()->GetGameplayUI()->SetWidgetSwitcher(OwnerCharacter_Base->GetStatComponent()->IsStatus(EStatusType::Combat), Current_Combat->CombatData.CombatType);
	}
}





// 마우스 좌클릭
void UCCombatComponent::OnAttack()
{
	
	Current_Combat->ComboAttack();
	

}

// 스킬 1번
void UCCombatComponent::Skill_1()
{
	Current_Combat->StartSkill(0);
}

// 스킬 2번
void UCCombatComponent::Skill_2()
{
	Current_Combat->StartSkill(1);
}

// 스킬 3번
void UCCombatComponent::Skill_3()
{
	Current_Combat->StartSkill(2);
}

void UCCombatComponent::PlayerRolling()
{
	CheckNull(OwnerCharacter_Player);
	CheckNull(Current_Combat->CombatData.Rolling.AnimMontage);

	CheckTrue(Current_Combat->bSkill);
	CheckTrue(OwnerCharacter_Player->GetStatComponent()->IsState(EStateType::Rolling));

	OwnerCharacter_Player->bUseControllerRotationYaw = false;
	OwnerCharacter_Player->GetCharacterMovement()->bOrientRotationToMovement = true;


	OwnerCharacter_Player->GetStatComponent()->SetStateType(EStateType::Rolling);


	
	if (UKismetMathLibrary::Vector_IsNearlyZero(OwnerCharacter_Player->GetVelocity(), 0.0001f))
	{
		FRotator nawRotation = UKismetMathLibrary::Conv_VectorToRotator(OwnerCharacter_Player->GetActorForwardVector());
		OwnerCharacter_Player->SetActorRotation(nawRotation);
	}
	else
	{
		FVector start = OwnerCharacter_Player->GetActorLocation();
		FVector target = (start + UKismetMathLibrary::Vector_Normal2D(OwnerCharacter_Player->GetVelocity(), 0.0001f));

		FRotator nawRotation = UKismetMathLibrary::FindLookAtRotation(start, target);
		OwnerCharacter_Player->SetActorRotation(nawRotation);
	}

	OwnerCharacter_Base->PlayAnimMontage(Current_Combat->CombatData.Rolling.AnimMontage, Current_Combat->CombatData.Rolling.PlayRate);
}

void UCCombatComponent::EndRolling()
{
	OwnerCharacter_Player->bUseControllerRotationYaw = true;
	OwnerCharacter_Player->GetCharacterMovement()->bOrientRotationToMovement = false;


	OwnerCharacter_Player->GetStatComponent()->SetStateType(EStateType::Idling);
}

