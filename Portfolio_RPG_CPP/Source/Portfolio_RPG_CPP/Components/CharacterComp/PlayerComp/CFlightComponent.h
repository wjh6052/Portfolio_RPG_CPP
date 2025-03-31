
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "../../../Datas/Data_DataTable.h"
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



public: //-----------------------------------------Get-----------------------------------------
//	FORCEINLINE bool GetSprint() const { return Flight_bSprint; } // statcomp�� ESpeedType�� ��ü
	FORCEINLINE FPlayer_Flight GetFlightData() const { return FlightData; }




public:
	void OnMoveForward_Flight(float InAxis);
	void OnMoveRight_Flight(float InAxis);

	void SettingFlying(bool input);
	void SetFlightMovementParam(bool input);

	void StartFlight();
	void EndFlight();

	void SetSprint(bool input);
	bool CheckMovementMode(EMovementMode input);

	void StopToPlayAnim(struct FAnimMontageBase* inAnimMontage);
	void SetActiveComponent(class UActorComponent* Component, bool bNewActive, bool bReset);

	int GetSurfaceType(EPhysicalSurface SurfaceType);



public: //-----------------------------------------HitEvent-----------------------------------------
	FORCEINLINE void HitReset() { HitReset_True = false; HitReset_False = false; }

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void HitEvent(bool input);



public: //-------------------------------Sprint_FlightUnderDust------------------------------------
	void Sprint_FlightUnderDust();

	class UNiagaraComponent* GetDustVFX(EPhysicalSurface SurfaceType);




public: //-----------------------------------------Notifi-----------------------------------------
	bool NotifiLineTracetoUpVector(float vectorLength, FHitResult& hitResult);

	class UNiagaraSystem* GetLandingVFX(EPhysicalSurface SurfaceType);	
	
	UNiagaraComponent* SpawnNiagaraAtLocationOrAttach(bool isAttach, UNiagaraSystem* SystemTemplate, USceneComponent* AttachToComponent, FVector Location, FRotator Rotation);






public:
	UPROPERTY(EditAnywhere, Category = "Flight_Variable")
		float Lean_X;
	UPROPERTY(EditAnywhere, Category = "Flight_Variable")
		float Lean_Y;

	UPROPERTY(EditAnywhere, Category = "Flight_Variable")
		FVector LookAtLocation;


private:

	class ACCharacter_Player* OwnerPlayer;

	class ACWings* Wings;

	UDataTable* FlightDataTable;
	FPlayer_Flight FlightData;

	bool Flight_bFlying = false;
	bool Flight_bLanding = false;

	bool HitReset_True = true;
	bool HitReset_False = true;

	
	
 
 
	class UNiagaraComponent* Flight_Trail_Ref;
	class UNiagaraComponent* Flight_Wave_Ref;
	TArray<class UNiagaraComponent*> Under_Dust_Ref;
	FTimerHandle SetActiveComponentTime;
};
