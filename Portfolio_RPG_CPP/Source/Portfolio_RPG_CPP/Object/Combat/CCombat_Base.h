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
		void SpawnWeapon(bool bSpawn);



	virtual void StartWeapon();
	virtual void EndWeapon();







public:	






public:	
	class ACCharacter_Base* OwnerCharacter;
};
