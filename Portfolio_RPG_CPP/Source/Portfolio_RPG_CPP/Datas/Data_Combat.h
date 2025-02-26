#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data_Character.h"
#include "Data_Combat.generated.h"



//--enum---------------------------------------------------------------------







//--struct---------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FAttackDamage
{
	GENERATED_BODY()

public:

	// 데미지
	UPROPERTY(EditAnywhere)
		float Damage;

	// 크리티컬 확률
	UPROPERTY(EditAnywhere)
		float CriticalChance;

	bool bOnCritical = false;

	// 뒤로 넉백
	UPROPERTY(EditAnywhere)
		float KnockbackStrength;

	// 공중 넉백
	UPROPERTY(EditAnywhere)
		float KnockUpStrength;
};

USTRUCT(BlueprintType)
struct FAttack
{
	GENERATED_BODY()

public:
	// 공격 애님 몽타주
	UPROPERTY(EditAnywhere, Category = "Anim Montage")
		FAnimMontageBase AnimMontage;

	// 콤보 ID
	UPROPERTY(EditAnywhere, Category = "Anim Montage")
		int ComboID;

	// 데미지
	UPROPERTY(EditAnywhere, Category = "Anim Montage")
		FAttackDamage AttackDamage;




	// 투척무기
	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon")
		bool bThrowableWeapon = false;

	// 데미지
	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon", meta = (EditCondition = "bThrowableWeapon"))
		FAttackDamage AttackDamage_ThrowableWeapon;

	// 투사체가 유지될 수명 시간
	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon", meta = (EditCondition = "bThrowableWeapon"))
		float Lifespan = 10.0f;

	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon", meta = (EditCondition = "bThrowableWeapon"))
		bool bTargeting = false;
};


USTRUCT(BlueprintType)
struct FSkillUI
{
	GENERATED_BODY()

public:
	// 스킬의 UI에 비춰질 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anim Montage")
		UTexture2D* SkillImage;

	// 스킬의 쿨타임
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anim Montage")
		float SkillCooldown;
};


USTRUCT(BlueprintType)
struct FImpactFlares
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* Impact_Flares;

	UPROPERTY(EditAnywhere)
		FVector Impact_Flares_Scale;

};






//--DataTable---------------------------------------------------------------------


USTRUCT(BlueprintType)
struct FCombatPlayer_DataTable : public FTableRowBase
{
	GENERATED_BODY()


public:
	// 무기 타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CombatType")
		ECombatType CombatType;


	// 무기
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class ACCombat_Base> CombatWeapon;

	// 무기를 붙일 본 이름
	UPROPERTY(EditAnywhere, Category = "Weapon")
		FName AttachBoneName;

	// 투척 무기
	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon")
		TSubclassOf<class ACThrowableWeapon> ThrowableWeaponClass;




	// 무기가 스폰할때나 디스폰할때 임팩트를 만들 머티리얼
	UPROPERTY(EditAnywhere, Category = "Material")
		class UMaterialInterface* WeaponMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
		FName ParameterName;


	UPROPERTY(EditAnywhere, Category = "Niagara")
		class UNiagaraSystem* ImpactFlares;

	UPROPERTY(EditAnywhere, Category = "Niagara")
		FVector ImpactFlaresScale;

	UPROPERTY(EditAnywhere, Category = "Niagara")
		class UNiagaraSystem* ImpactFlaresThrowable;

	UPROPERTY(EditAnywhere, Category = "Niagara")
		FVector ImpactFlaresThrowableScale;



	// 무기를 꺼낼때
	UPROPERTY(EditAnywhere, Category = "EquipWeapon")
		FAnimMontageBase EquipWeapon;

	// 무기를 넣을때
	UPROPERTY(EditAnywhere, Category = "EquipWeapon")
		FAnimMontageBase UnequipWeapon;



	// 데미지를 받을때의 애님인스턴스
	UPROPERTY(EditAnywhere, Category = "Hit")
		FAnimMontageBase Hit_Montage;



	// 콤보 공격
	UPROPERTY(EditAnywhere, Category = "Combo")
		TArray<FAttack> Combo_Attack;



	// 스킬 1
	UPROPERTY(EditAnywhere, Category = "Skill 1")
		TArray<FAttack> Skill_1;

	// 스킬 1의 쿨타임과 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill 1")
		FSkillUI Skill_1_UI;


	// 스킬 2
	UPROPERTY(EditAnywhere, Category = "Skill 2")
		TArray<FAttack> Skill_2;

	// 스킬 2의 쿨타임과 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill 2")
		FSkillUI Skill_2_UI;


	// 스킬 3
	UPROPERTY(EditAnywhere, Category = "Skill 3")
		TArray<FAttack> Skill_3;

	// 스킬 3의 쿨타임과 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill 3")
		FSkillUI Skill_3_UI;



	// 달리기 도중 공격
	UPROPERTY(EditAnywhere, Category = "Run to Attack")
		FAttack RunToAttack;



	// 점프 도중 공격
	UPROPERTY(EditAnywhere, Category = "Jump to Attack")
		FAttack JumpToAttack;



	// 막기
	UPROPERTY(EditAnywhere, Category = "Block")
		FAnimMontageBase Block;

	// 막기 중 맞을때
	UPROPERTY(EditAnywhere, Category = "Block")
		FAnimMontageBase Block_Hit;


	// 죽을 때 애님인스턴스
	UPROPERTY(EditAnywhere, Category = "Die")
		FAnimMontageBase Die_Montage;

	
};






UCLASS()
class PORTFOLIO_RPG_CPP_API UData_Combat : public UObject
{
	GENERATED_BODY()
	
};
