#pragma once

#include "CoreMinimal.h"
#include "../CCombat_Base.h"
#include "CCombat_Melee.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACCombat_Melee : public ACCombat_Base
{
	GENERATED_BODY()
	
public:
	ACCombat_Melee();

protected:
	virtual void BeginPlay() override;



public:
	virtual void StartWeapon() override;
	virtual void EndWeapon() override;




	UFUNCTION()
		virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	


public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* DefaultRoot;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCapsuleComponent* CapsuleCollision;

};
