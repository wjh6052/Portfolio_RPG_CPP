#include "CThrowableWeapon.h"

#include "../../../Global.h"
#include "../../../Character/CCharacter_Base.h"
#include "../../../CGameInstance.h"
#include "../CCombat_Base.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ACThrowableWeapon::ACThrowableWeapon()
{
	CHelpers::CreateSceneComponent(this, &DefaultRoot, "DefaultRoot", GetRootComponent());
	CHelpers::CreateSceneComponent(this, &ThrowableWeaponMesh, "ThrowableWeaponMesh", DefaultRoot);
	CHelpers::CreateSceneComponent(this, &CapsuleCollision, "CapsuleCollision", ThrowableWeaponMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));




	ThrowableWeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMovement->ProjectileGravityScale = 0.0f;


	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1200.0f;





	CapsuleCollision->SetHiddenInGame(false);



	PrimaryActorTick.bCanEverTick = true;

}


void ACThrowableWeapon::BeginPlay()
{
	Super::BeginPlay();

	// ���ε�
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &ACThrowableWeapon::OnCapsuleBeginOverlap);

	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	
	CheckNull(OwnerCharacter);
	if (OwnerCharacter->GetCombatComponent()->bLookOn)
	{
		TargetCharacter = OwnerCharacter->GetCombatComponent()->LookOn_Character;
	}


	AttackData = OwnerCharacter->GetCombatComponent()->Current_Combat->GetCurrentAttackData();

	SetLifeSpan(AttackData.Lifespan);
	
	
}


void ACThrowableWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (TargetCharacter != nullptr) // Ÿ�����϶�
	{

	}


}





void ACThrowableWeapon::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() != OtherActor)
	{
		ACCharacter_Base* OtherCharacter = Cast<ACCharacter_Base>(OtherActor);

		// ĳ�������� �ƴҶ� ����
		CheckNull(OtherCharacter);
		
		CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			// ũ��Ƽ�� üũ �� ������ ����

		AttackData.bThrowableWeapon = FMath::RandRange(0, 100) < AttackData.AttackDamage_ThrowableWeapon.CriticalChance;
		if (AttackData.bThrowableWeapon)
		{
			AttackData.AttackDamage_ThrowableWeapon.Damage += (OwnerCharacter->GetStatComponent()->GetPlayerData().Stat.Critical_Damage * 0.01 * AttackData.AttackDamage_ThrowableWeapon.Damage);
		}
	

		// �������� ����� ���ڷ� ���̾ư��� ȿ������
		OwnerCharacter->GetCombatComponent()->ShowDamageText(OtherActor, AttackData.AttackDamage_ThrowableWeapon.Damage, OwnerCharacter->GetController(), AttackData.bThrowableWeapon);
		
		// �������� ���� ��ġ�� ���̾ư��� ȿ�� ����
		OwnerCharacter->GetCombatComponent()->OnHitImpact(true, OverlappedComponent);

		// �˹� ȿ��
		OwnerCharacter->GetCombatComponent()->AttackKnockBack(OwnerCharacter, AttackData.AttackDamage_ThrowableWeapon.KnockbackStrength, AttackData.AttackDamage_ThrowableWeapon.KnockUpStrength);

		UGameplayStatics::ApplyDamage(OtherActor, AttackData.AttackDamage_ThrowableWeapon.Damage, OwnerCharacter->GetController(), this, UDamageType::StaticClass());


		K2_DestroyActor();
	}



}

