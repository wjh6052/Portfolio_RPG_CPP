#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Character/CCharacter_Base.h"
#include "CCombat_Base.generated.h"






UCLASS()
class PORTFOLIO_RPG_CPP_API ACCombat_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCombat_Base();

protected:
	virtual void BeginPlay() override;



public:
	// 무기가 생길때와 사라질때를 타임라인으로 제어할 함수
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnWeapon();

	UPROPERTY(BlueprintReadOnly)
		bool bSpawn = false;

	UPROPERTY(BlueprintReadOnly)
		class UMaterialInstanceDynamic* DissolveMaterial;


public:
	// 무기 꺼낼때
	virtual void StartWeapon();
	// 무기 넣을때
	virtual void EndWeapon();


	

	// 공격 시작
	virtual void StartAttack();
	// 공격 끝
	virtual void EndAttack();
	
	virtual void SpawnThrowableWeapon(FName InSocketName);


	virtual void SetWeaponCollision(bool bOnCollision);


public: // 콤보

	// 마우스 왼쪽 클릭때 호출될 함수
	virtual void ComboAttack();

	// 노티파이를 통해 호출될 함수
	virtual void NextComboAttack();

	int ComboNum = 0;

	bool bCanNextComboTiming = false;
	bool bCanNextCombo = false;


public: // 스킬

	virtual void StartSkill(int InSkillNum);
	virtual void EndSkill();



	bool bSkill = false;
	int SkillNum = 0;
	int SkillComboNum = 0;




public:
	virtual FAttack GetCurrentAttackData();








	


	FCombatData CombatData;
	

	// 다중공격 방지 캐릭터 배열
	TArray<class AActor*> BeginActor;

public:	
	class UCGameInstance* CGameInstance;

	class ACCharacter_Base* OwnerCharacter;

	ECombatType CombatType;
};
