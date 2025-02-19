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
		void SpawnWeapon(bool bSpawn);



	virtual void StartWeapon();
	virtual void EndWeapon();







public:	






public:	
	class ACCharacter_Base* OwnerCharacter;
};
