#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	UFUNCTION(BlueprintCosmetic, BlueprintNativeEvent)
		void SpawnWeapon();
	void SpawnWeapon_Implementation();


	UFUNCTION(BlueprintCosmetic, BlueprintNativeEvent)
		void StartWeapon();
	void StartWeapon_Implementation();

	UFUNCTION(BlueprintCosmetic, BlueprintNativeEvent)
		void EndWeapon();
	void EndWeapon_Implementation();




public:	
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* DefaultRoot;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* WeaponMesh;





public:	
	class ACCharacter_Base* OwnerCharacter;
};
