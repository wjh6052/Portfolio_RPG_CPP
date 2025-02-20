#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Datas/Data_Combat.h"
#include "CCombatComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_RPG_CPP_API UCCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCCombatComponent();


protected:
	virtual void BeginPlay() override;


	void SwitchWeapon();

public:
	void TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	
	void AttractToTarget(AActor* Target);
	void ShowDamageText(float Damage, class AController* TargetController, bool bCritical = false, bool bHill = false);


	void SpawnCombat();


	void OnAttack();


	void Skill_1();
	void Skill_2();
	void Skill_3();



	int ComboCount = 0;






	FCombatPlayer_DataTable Current_CombatPlayer_Data;

	class ACCombat_Base* Current_Combat;


public:
	class UCGameInstance* CGameInstance;

	class ACCharacter_Base* OwnerCharacter_Base;




public:// 노티파이

		
};
