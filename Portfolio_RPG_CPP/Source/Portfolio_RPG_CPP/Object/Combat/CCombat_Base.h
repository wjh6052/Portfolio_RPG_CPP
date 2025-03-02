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


	virtual void CooldownTick();  // 0.1�ʸ��� ����Ǵ� �Լ�
	FTimerHandle CooldownTimerHandle;  // ��Ÿ���� ���� Ÿ�̸� �ڵ�


public:
	// ���Ⱑ ���涧�� ��������� Ÿ�Ӷ������� ������ �Լ�
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnWeapon();

	UPROPERTY(BlueprintReadOnly)
		bool bSpawn = false;

	UPROPERTY(BlueprintReadOnly)
		class UMaterialInstanceDynamic* DissolveMaterial;


public:
	// ���� ������
	virtual void StartWeapon();
	// ���� ������
	virtual void EndWeapon();


	

	// ���� ����
	virtual void StartAttack();
	// ���� ��
	virtual void EndAttack();
	
	virtual void SpawnThrowableWeapon(FName InSocketName);


	virtual void SetWeaponCollision(bool bOnCollision);


public: // �޺�

	// ���콺 ���� Ŭ���� ȣ��� �Լ�
	virtual void ComboAttack();

	// ��Ƽ���̸� ���� ȣ��� �Լ�
	virtual void NextComboAttack();

	int ComboNum = 0;

	bool bCanNextComboTiming = false;
	bool bCanNextCombo = false;

	bool bRunToAttack = false;
	bool bJumpAttack = false;

public: // ��ų

	virtual void StartSkill(int InSkillNum);

	virtual void MoveTarget(const class AActor* InTarget, float InForward = 0, float InRight = 0, float InUp = 0, bool bNotMove = false, bool bNotTurn = false);
	virtual void DamagesTarget(class AActor* InTarget);

	bool bSkill = false;
	int SkillNum = -1;
	int SkillComboNum = -1;

	float SkillCoolDowns[3];
	float CurrentSkillCooldowns[3];
	bool bOnSkill[3];


public:
	virtual FAttack GetCurrentAttackData();








	


	FCombatData CombatData;
	

	// ���߰��� ���� ĳ���� �迭
	TArray<class AActor*> BeginActor;


	// ��ų ���� Ÿ��
	TArray<class AActor*> SkillTargetArr;
	class AActor* SkillSingleTarget;


public:	
	class UCGameInstance* CGameInstance;

	class ACCharacter_Base* OwnerCharacter;
};
