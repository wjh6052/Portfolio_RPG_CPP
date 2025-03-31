#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../Datas/Data_DataTable.h"
#include "CThrowableWeapon.generated.h"

UCLASS()
class PORTFOLIO_RPG_CPP_API ACThrowableWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACThrowableWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	

	UFUNCTION()
		virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* DefaultRoot;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* ThrowableWeaponMesh;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCapsuleComponent* CapsuleCollision;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UProjectileMovementComponent* ProjectileMovement;


public:	
	class ACCharacter_Base* OwnerCharacter;
	FAttack AttackData;
	class ACCharacter_Base* TargetCharacter;
};
