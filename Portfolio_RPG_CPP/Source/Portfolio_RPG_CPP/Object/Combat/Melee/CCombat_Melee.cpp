#include "CCombat_Melee.h"
#include "../../../Global.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"


ACCombat_Melee::ACCombat_Melee()
{
	CHelpers::CreateSceneComponent(this, &DefaultRoot, "DefaultRoot", GetRootComponent());
	CHelpers::CreateSceneComponent(this, &WeaponMesh, "WeaponMesh", DefaultRoot);
	CHelpers::CreateSceneComponent(this, &CapsuleCollision, "CapsuleCollision", WeaponMesh);


	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);



	

	//Test
	CapsuleCollision->SetHiddenInGame(false);
}

void ACCombat_Melee::BeginPlay()
{
	Super::BeginPlay();

	// 바인딩
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &ACCombat_Melee::OnCapsuleBeginOverlap);

	// 처음에 콜리젼끄기
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}



void ACCombat_Melee::StartWeapon()
{
	Super::StartWeapon();

	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void ACCombat_Melee::EndWeapon()
{
	Super::EndWeapon();
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}





void ACCombat_Melee::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (GetOwner() != OtherActor)
	{
		switch (OwnerCharacter->GetCharacterType())
		{
		case ECharacterType::Player:
			
			UGameplayStatics::ApplyDamage(OtherActor, 15.0f, OwnerCharacter->GetController(), this, UDamageType::StaticClass());
			//FDamageEvent damageEvent;
			//overlapCharacter->TakeDamage(13.f, damageEvent, )


			break;

		case ECharacterType::Enemy:
			
			break;

		default:
			break;
		}

		
		

	}
	//CCharacter_Base

}
	


