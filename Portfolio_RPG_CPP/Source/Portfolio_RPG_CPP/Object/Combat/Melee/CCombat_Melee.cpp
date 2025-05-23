﻿#include "CCombat_Melee.h"
#include "../../../Global.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"




ACCombat_Melee::ACCombat_Melee()
{
	CHelpers::CreateSceneComponent(this, &DefaultRoot, "DefaultRoot", GetRootComponent());
	CHelpers::CreateSceneComponent(this, &WeaponMesh, "WeaponMesh", DefaultRoot);
	CHelpers::CreateSceneComponent(this, &CapsuleCollision, "CapsuleCollision", WeaponMesh);


	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	

	//Test
	CapsuleCollision->SetHiddenInGame(true);
}

void ACCombat_Melee::BeginPlay()
{
	Super::BeginPlay();


	for (int i = 0; i < WeaponMesh->GetMaterials().Num(); i++)
	{
		DynamicMaterial.Add(WeaponMesh->CreateDynamicMaterialInstance(i, WeaponMesh->GetMaterials()[i]));
	}
	
	
	

	// 바인딩
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &ACCombat_Melee::OnCapsuleBeginOverlap);

	


}

void ACCombat_Melee::CooldownTick()
{
	Super::CooldownTick();
}



void ACCombat_Melee::StartWeapon()
{
	Super::StartWeapon();

	

}

void ACCombat_Melee::EndWeapon()
{
	Super::EndWeapon();
	

}

void ACCombat_Melee::StartAttack()
{
	Super::StartAttack();
}

void ACCombat_Melee::EndAttack()
{
	Super::EndAttack();
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}



void ACCombat_Melee::SetWeaponCollision(bool bOnCollision)
{
	Super::SetWeaponCollision(bOnCollision);

	if (bOnCollision)
	{
		CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	

}





void ACCombat_Melee::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() != OtherActor && Cast<ACCharacter_Base>(OtherActor))
	{		
		ACCharacter_Base* otherCharacter = Cast<ACCharacter_Base>(OtherActor);

		// 같은 애너미일경우 중지
		if (otherCharacter->CharacterType == Cast<ACCharacter_Base>(GetOwner())->CharacterType)
			return;

		// 다중공격이 될 경우 중지
		for (AActor* actor : BeginActor)
			if (actor == OtherActor)
				return;

		BeginActor.AddUnique(OtherActor);


		FAttack attackData = GetCurrentAttackData();


		// 캐릭터의 스텟 데미지 및 크리티컬 확률 추가
		{
			attackData.AttackDamage.Damage += OwnerCharacter->GetStatComponent()->GetCurrentStat().Damage;
			attackData.AttackDamage.CriticalChance += OwnerCharacter->GetStatComponent()->GetCurrentStat().Critical_Chance;
		}


		// 크리티컬 체크 및 데미지 증가
		bool OnCritical = attackData.AttackDamage.bOnCritical || attackData.AttackDamage.CriticalChance >= FMath::FRandRange(0.0, 100.0);
			
			
		if (OnCritical)
		{	
			attackData.AttackDamage.Damage += (OwnerCharacter->GetStatComponent()->GetPlayerData().Stat.Critical_Damage *   0.01f * attackData.AttackDamage.Damage);
		}

		
		if (!(otherCharacter->GetCharacterType() == ECharacterType::Boss))
		{
			// 공격시 나의 방향을 적의 방향으로 전환
			OwnerCharacter->GetCombatComponent()->AttractToTarget(OtherActor);

			// 넉백 효과
			OwnerCharacter->GetCombatComponent()->AttackKnockBack(OtherActor, attackData.AttackDamage.KnockbackStrength,attackData.AttackDamage.KnockUpStrength);
		}

		// 데미지를 월드상 숫자로 나이아가라 효과스폰
		OwnerCharacter->GetCombatComponent()->ShowDamageText(OverlappedComponent, attackData.AttackDamage.Damage,OnCritical);

		// 데미지를 받은 위치에 나이아가라 효과 스폰
		OwnerCharacter->GetCombatComponent()->OnHitImpact(false, OverlappedComponent);
		
		
		ACCharacter_Base* actor = Cast<ACCharacter_Base>(OtherActor);

		if (actor)
		{
			actor->GetCombatComponent()->TakeDamage(attackData.AttackDamage.Damage, OwnerCharacter, OnCritical, bSkill);
		}
		//UGameplayStatics::ApplyDamage(OtherActor, attackData.AttackDamage.Damage, OwnerCharacter->GetController(), this, UDamageType::StaticClass());


		
		

	}
	

}
	


