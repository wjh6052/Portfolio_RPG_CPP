
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CFlightComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_RPG_CPP_API UCFlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCFlightComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//public: //-----------------------------------------Get-----------------------------------------
//	FORCEINLINE bool GetSprint() const { return Flight_bSprint; }
//	FORCEINLINE class UCFlightDataAsset* GetFlightDataAsset() const { return FlightDataAsset; }
//
//
//public:
//	void OnMoveForward_Flight(float InAxis);
//	void OnMoveRight_Flight(float InAxis);
//
//	void SetFlying(bool input);
//	void SetFlightMovementParam(bool input);
//
//	void StartFlight();
//	void EndFlight();
//
//	void SetSprint(bool input);
//	bool CheckMovementMode(EMovementMode input);
//
//	void StopToPlayAnim(struct FAnimMontageBase* inAnimMontage);
//	void SetActiveComponent(class UActorComponent* Component, bool bNewActive, bool bReset);
//
//	int GetSurfaceType(EPhysicalSurface SurfaceType);
//
//
//public: //-----------------------------------------HitEvent-----------------------------------------
//	FORCEINLINE void HitReset() { HitReset_True = false; HitReset_False = false; };
//
//	UFUNCTION()
//		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
//
//	void HitEvent(bool input);
//
//
//public: //-------------------------------Sprint_FlightUnderDust------------------------------------
//	void Sprint_FlightUnderDust();
//
//	UNiagaraComponent* GetDustVFX(EPhysicalSurface SurfaceType);
//
//
//
//
//public: //-----------------------------------------Notifi-----------------------------------------
//	bool NotifiLineTracetoUpVector(float vectorLength, FHitResult& hitResult);
//
//	UNiagaraSystem* GetLandingVFX(EPhysicalSurface SurfaceType);
//
//	UNiagaraComponent* SpawnNiagaraAtLocationOrAttach(bool isAttach, UNiagaraSystem* SystemTemplate, USceneComponent* AttachToComponent, FVector Location, FRotator Rotation);
//
//
//
//
//
//private:
//	UPROPERTY(EditAnywhere, Category = "Data")
//		class UCFlightDataAsset* FlightDataAsset;
//
//	UPROPERTY(EditAnywhere, Category = "Data")
//		TSubclassOf<ACWings> WingsClass;
//
//
//
//
//
//public:
//	UPROPERTY(EditAnywhere, Category = "Flight_Variable")
//		float Lean_X;
//	UPROPERTY(EditAnywhere, Category = "Flight_Variable")
//		float Lean_Y;
//
//	UPROPERTY(EditAnywhere, Category = "Flight_Variable")
//		FVector LookAtLocation;
//
//
//private:
//	class ACWings* Wings;
//
//	class ACPlayer* OwnerPlayer;
//
//	bool Flight_bFlying = false;
//	bool Flight_bSprint = false;
//	bool Flight_bLanding = false;
//
//
//	bool HitReset_True = true;
//	bool HitReset_False = true;
//
//
//	class UNiagaraComponent* Flight_Trail_Ref;
//	class UNiagaraComponent* Flight_Wave_Ref;
//	TArray<class UNiagaraComponent*> Under_Dust_Ref;
//	FTimerHandle SetActiveComponentTime;
};
