#include "CCombat_Melee.h"
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
	CapsuleCollision->SetHiddenInGame(false);
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
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACCombat_Melee::EndAttack()
{
	Super::EndAttack();
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}



void ACCombat_Melee::SetWeaponCollision(bool bOnCollision)
{
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
	if (GetOwner() != OtherActor)
	{		
		ACCharacter_Base* OtherCharacter = Cast<ACCharacter_Base>(OtherActor);

		// 캐릭터형이 아닐때 중지
		CheckNull(OtherCharacter);

		// 다중공격이 될 경우 중지
		for (ACCharacter_Base* character : BeginCharacter)
			if (character == OtherCharacter)
				return;

		BeginCharacter.AddUnique(OtherCharacter);

		switch (OwnerCharacter->GetCharacterType())
		{
		case ECharacterType::Player:
		{
			
	
			
			FAttack attackData = GetCurrentAttackData();

			// 크리티컬 체크 및 데미지 증가
			if (attackData.AttackDamage.bOnCritical)
			{				
				attackData.AttackDamage.Damage += (OwnerCharacter->GetStatComponent()->GetPlayerData().Stat.Critical_Damage * 0.01 * attackData.AttackDamage.Damage);
			}

			// 공격시 나의 방향을 적의 방향으로 전환
			OwnerCharacter->GetCombatComponent()->AttractToTarget(OtherCharacter);

			OtherCharacter->GetCombatComponent()->ShowDamageText(attackData.AttackDamage.Damage, OwnerCharacter->GetController(), attackData.AttackDamage.bOnCritical);
			OwnerCharacter->GetCombatComponent()->OnHitImpact(false, OverlappedComponent);
			UGameplayStatics::ApplyDamage(OtherActor, attackData.AttackDamage.Damage, OwnerCharacter->GetController(), this, UDamageType::StaticClass());
		}
			break;

		case ECharacterType::Enemy:
			
			break;

		default:
			break;
		}

		
		

	}
	

}
	


