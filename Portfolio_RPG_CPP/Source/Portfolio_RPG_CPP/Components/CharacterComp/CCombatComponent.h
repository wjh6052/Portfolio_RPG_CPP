#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Datas/Data_DataTable.h"
#include "CCombatComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_RPG_CPP_API UCCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCCombatComponent();


protected:
	virtual void BeginPlay() override;
	void PlayerBeginPlay();
	void EnemyBeginPlay();
	void BossBeginPlay();


	UFUNCTION(BlueprintCallable)
		void SwitchWeapon(ECombatType InCombatType);

public:
	// 연출

	// 데미지 적용
	void TakeDamage(float DamageAmount, AActor* DamageCauser, bool IsCritical, bool IsSkill = false);
	void OnHitImpact(bool bThrowable, class UPrimitiveComponent* OverlappedComponent);
	void AttackKnockBack(AActor* DamageOwner, float InKnockBackForward, float InKnockBackUp);
	void PlayHitReaction();
	void CharacterDeath(AActor* DamageCauser);

	void DropLootOnDeath();

	void AttractToTarget(AActor* Target);
	void ShowDamageText(class UPrimitiveComponent* OverlappedComponent, float Damage, bool bCritical = false, bool bHill = false);


	// 무기를 꺼낼때와 넣을때 호출
	UFUNCTION(BlueprintCallable)
		void EquipCombat(bool bPlayMontage = true);
	UFUNCTION(BlueprintCallable)
		void UnequipCombat(bool bPlayMontage = true);


	void OnAttack();


	void Skill_1();
	void Skill_2();
	void Skill_3();


	void PlayerRolling();
	void EndRolling();

	int ComboCount = 0;





	UPROPERTY(BlueprintReadOnly)
		FCombatData Current_CombatData;
	class ACCombat_Base* Current_Combat;


	TArray<class ACCombat_Base*> CombatArr;



	bool bLookOn = false;
	class ACCharacter_Base* LookOn_Character;


	bool bCanBeKnockedBack = true;

public:
	class UCGameInstance* CGameInstance;

	class ACCharacter_Base* OwnerCharacter_Base;
	class ACCharacter_Player* OwnerCharacter_Player = nullptr;
	class ACCharacter_Enemy* OwnerCharacter_Enemy = nullptr;
	class ACCharacter_Boss* OwnerCharacter_Boss = nullptr;


	class ACCharacter_Base* DamageCharacter = nullptr;

public:

	bool bIsPlayerHitTime = false;
		
};
