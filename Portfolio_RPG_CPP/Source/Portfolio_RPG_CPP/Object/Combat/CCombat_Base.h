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






public:
	virtual FAttack GetCurrentAttackData();






public:	

	


	bool bSkill = false;
	int SkillNum = 0;
	int SkillComboNum = 0;


	


	FCombatData CombatData;
	

	// ���߰��� ���� ĳ���� �迭
	TArray<class ACCharacter_Base*> BeginCharacter;

public:	
	class ACCharacter_Base* OwnerCharacter;
};
