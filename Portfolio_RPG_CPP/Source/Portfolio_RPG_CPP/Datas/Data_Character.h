#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Data_Character.generated.h"


//--struct---------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FMesh
{
	GENERATED_BODY()

public:
	// ¾Ö´ÔÅ¬·¡½º
	UPROPERTY(EditAnywhere)
		class UClass* AnimInstance;

	// ½ºÄÌ·¹Å» ¸Þ½Ã ¿¡¼Â
	UPROPERTY(EditAnywhere)
		class USkeletalMesh* MeshAsset;

	UPROPERTY(EditAnywhere)
		FVector Character_Location = FVector(0.f, 0.f, -80.f);

	UPROPERTY(EditAnywhere)
		FRotator Character_Rotation = FRotator(0.f, -90.f, 0.f);


	// Ä«¸Þ¶ó ¾Ï À§Ä¡
	UPROPERTY(EditAnywhere)
		FVector CameraSpringArm_Location = FVector(0.f, 0.f, 40.f);


	// Ä¸½¶ ¹Ý°æ
	UPROPERTY(EditAnywhere)
		float CapsuleHalfHeight = 80.f;

	// Ä¸½¶ Àý¹Ý ³ôÀÌ
	UPROPERTY(EditAnywhere)
		float CapsuleRadius = 25.f;

};


USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float HP = 100;
	UPROPERTY(EditAnywhere)
		float HP_Max = 100;
	UPROPERTY(EditAnywhere)
		float Damage = 10;
	UPROPERTY(EditAnywhere)
		float Defense = 5;
	UPROPERTY(EditAnywhere)
		float Critical_Damage = 1.5;
	UPROPERTY(EditAnywhere)
		float Critical_Chance = 20;
};


USTRUCT(BlueprintType)
struct FSpeed
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Stop = 0;
	UPROPERTY(EditAnywhere)
		float Walk = 200;
	UPROPERTY(EditAnywhere)
		float Joging = 400;
	UPROPERTY(EditAnywhere)
		float Run = 600;

	UPROPERTY(EditAnywhere)
		float FlyWarkSpeed = 600.f;
	UPROPERTY(EditAnywhere)
		float MaxAcceleration = 2048.f;
	UPROPERTY(EditAnywhere)
		float BrakingDeceleration = 0;
	UPROPERTY(EditAnywhere)
		FRotator RotationRate = FRotator(0.f, 720.f, 0.f);	
};


USTRUCT(BlueprintType)
struct FSpeed_Flight
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float FlyWarkSpeed = 600.f;
	UPROPERTY(EditAnywhere)
		float MaxAcceleration = 2048.f;
	UPROPERTY(EditAnywhere)
		float BrakingDeceleration = 0;
	UPROPERTY(EditAnywhere)
		FRotator RotationRate = FRotator(0.f, 720.f, 0.f);
};

USTRUCT(BlueprintType)
struct FAnimMontageBase : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		class UAnimMontage* AnimMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		float PlayRate = 1.0;
};



//--Main---------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FPlayer_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		FMesh Mesh;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		FSpeed Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
	// ´Þ¸®±â °¡´É ½Ã°£
		float Run_Time = 0.25f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		FSpeed_Flight Speed_Flight;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Roll")
		FAnimMontageBase RollAnimMontage;
};


USTRUCT(BlueprintType)
struct FEnemy_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterType")
		FName EnemyName_Type;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		FMesh Mesh;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		FSpeed Speed;
};


USTRUCT(BlueprintType)
struct FBoss_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterType")
		FName BossName_Type;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		FMesh Mesh;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		FSpeed Speed;
};

UCLASS()
class PORTFOLIO_RPG_CPP_API UData_Character : public UObject
{
	GENERATED_BODY()
	
};
