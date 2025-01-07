#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Data_Character.h"
#include "Data_Flight.generated.h"


USTRUCT(BlueprintType)
struct FFlightSetting
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float FlyWarkSpeed = 600.f;
	UPROPERTY(EditAnywhere)
		float MaxAcceleration = 2048.f;
	UPROPERTY(EditAnywhere)
		float BrakingDeceleration = 4096.0;
	UPROPERTY(EditAnywhere)
		FRotator RotationRate = FRotator(0.f, 540.f, 0.f);
};

USTRUCT(BlueprintType)
struct FFlightSetting_Sprint
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float FlyWarkSpeed = 1000.f;
	UPROPERTY(EditAnywhere)
		float FlySpeed = 4096.f;
	UPROPERTY(EditAnywhere)
		float MaxAcceleration = 20480.f;
	UPROPERTY(EditAnywhere)
		float BrakingDeceleration = 4096.0;
	UPROPERTY(EditAnywhere)
		FRotator RotationRate = FRotator(0.f, 720.f, 0.f);
};






USTRUCT(BlueprintType)
struct FPlayer_Flight : public FTableRowBase
{
	GENERATED_BODY()
public:
	//----------------------class--------------------------
	UPROPERTY(EditAnywhere, Category = "WingsClass")
		class UClass* WingsClass;
	
	//----------------------FlightSpeed--------------------------
	UPROPERTY(EditAnywhere, Category = "FlightSpeed")
		FFlightSetting FlightSetting;

	UPROPERTY(EditAnywhere, Category = "FlightSpeed")
		FFlightSetting_Sprint FlightSetting_Sprint;


	//----------------Sprint_FlightUnderDust----------------------
	UPROPERTY(EditAnywhere, Category = "Sprint_FlightUnderDust")
		bool bOnFlightUnderDust = true;

	UPROPERTY(EditAnywhere, Category = "Sprint_FlightUnderDust")
		float FlightUnderDustLength = -300.f;


	//----------------------AnimMontage--------------------------
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		struct FAnimMontageBase Hover_Start;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		struct FAnimMontageBase FastMove_Start;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		struct FAnimMontageBase Landing;

	//----------------------Flight_Trail--------------------------
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Trail")
		class UNiagaraSystem* Flight_Trail;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Trail")
		FVector Flight_Trail_Location;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Trail")
		FRotator Flight_Trail_Rotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Trail")
		FVector Flight_Trail_Scale = FVector(1.f, 1.f, 1.f);



	//----------------------Flight_Wave--------------------------
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Wave")
		class UNiagaraSystem* Flight_Wave;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Wave")
		FVector Flight_Wave_Location;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Wave")
		FRotator Flight_Wave_Rotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flight_Wave")
		FVector Flight_Wave_Scale = FVector(1.f, 1.f, 1.f);


	//----------------------FlightUnderDust--------------------------
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "FlightUnderDust")
		TArray <class UNiagaraSystem*> FlightUnderDust_Impact;



	//----------------------SuperheroLnading--------------------------
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuperheroLanding")
		TArray <class UNiagaraSystem*> Landing_Impact;
};












UCLASS()
class PORTFOLIO_RPG_CPP_API UData_Flight : public UObject
{
	GENERATED_BODY()
	
};
