#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CCharacterDataAsset.generated.h"

//--enum---------------------------------------------------------------------
UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Player,
	Enemy,
	Boss
};

//--struct---------------------------------------------------------------------

USTRUCT(Atomic, BlueprintType)
struct FMesh
{
	GENERATED_BODY()

public:
	// �ִ�Ŭ����
	UPROPERTY(EditAnywhere)
		class UClass* AnimInstance;

	// ���̷�Ż �޽� ����
	UPROPERTY(EditAnywhere)
		class USkeletalMesh* MeshAsset;

	UPROPERTY(EditAnywhere)
		FVector Character_Location = FVector(0.f, 0.f, -80.f);

	UPROPERTY(EditAnywhere)
		FRotator Character_Rotation = FRotator(0.f, -90.f, 0.f);
		

	// ī�޶� �� ��ġ
	UPROPERTY(EditAnywhere)
		FVector CameraSpringArm_Location = FVector(0.f, 0.f, 40.f);


	// ĸ�� �ݰ�
	UPROPERTY(EditAnywhere)
		float CapsuleHalfHeight = 80.f;

	// ĸ�� ���� ����
	UPROPERTY(EditAnywhere)
		float CapsuleRadius = 25.f;

	


};


USTRUCT(Atomic, BlueprintType)
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


USTRUCT(Atomic, BlueprintType)
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

	// �޸��� ���� �ð�
	UPROPERTY(EditAnywhere)
		float Run_Time = 0.25f;
};

USTRUCT(BlueprintType)
struct FAnimMontageBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		class UAnimMontage* AnimMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		float PlayRate = 1.0;
};


UCLASS()
class PORTFOLIO_RPG_CPP_API UCCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterType")
		ECharacterType CharacterType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		FMesh Mesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		FSpeed Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Roll")
		FAnimMontageBase RollAnimMontage;
};
