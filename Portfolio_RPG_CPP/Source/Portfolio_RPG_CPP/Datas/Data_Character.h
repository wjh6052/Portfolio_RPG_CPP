#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Data_Inventory.h"
#include "Data_Character.generated.h"




//--enum---------------------------------------------------------------------

UENUM(BlueprintType)
enum class EEnemyName : uint8
{
	None			UMETA(DisplayName = "비어있음"),
	TrainingDummy	UMETA(DisplayName = "허수아비"),
	Hilichurl		UMETA(DisplayName = "츄츄족")
};


UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	None	UMETA(DisplayName = "비어있음"),
	Player	UMETA(DisplayName = "플레이어"),
	Enemy	UMETA(DisplayName = "몬스터"),
	Boss	UMETA(DisplayName = "보스"),
	NPC		UMETA(DisplayName = "NPC")
};

UENUM(BlueprintType)
enum class ECombatType : uint8
{
	None		UMETA(DisplayName = "비어있음"),
	Assassin	UMETA(DisplayName = "어쌔신"),
	Katana		UMETA(DisplayName = "사무라이"),
	Greatsword	UMETA(DisplayName = "대검"),
	Spear		UMETA(DisplayName = "창병"),
	Warrior		UMETA(DisplayName = "방패병"),
	Archer		UMETA(DisplayName = "궁수"),
	Wizard		UMETA(DisplayName = "마법사")
};


//--struct---------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FMesh
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UClass* AnimInstance;


	UPROPERTY(EditAnywhere)
		class USkeletalMesh* MeshAsset;

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* MeshOutLineAsset;


	UPROPERTY(EditAnywhere)
		FVector Character_Location = FVector(0.f, 0.f, -80.f);

	UPROPERTY(EditAnywhere)
		FRotator Character_Rotation = FRotator(0.f, -90.f, 0.f);


	
	UPROPERTY(EditAnywhere)
		FVector CameraSpringArm_Location = FVector(0.f, 0.f, 40.f);


	
	UPROPERTY(EditAnywhere)
		float CapsuleHalfHeight = 80.f;

	
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




//--DataTable---------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FPlayer_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 메쉬
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		FMesh Mesh;


	// 캐릭터가 들 무기 타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CombatType")
		ECombatType CombatType;


	// 스텟
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;


	// 스피드
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		FSpeed Speed;

	// 비행 스피드
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		FSpeed_Flight Speed_Flight;

	// 달리기를 위한 더블클릭 허용 시간
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		float Run_Time = 0.25f;

};



USTRUCT(BlueprintType)
struct FEnemy_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public
	:
	// 몬스터의 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Enemy Name")
		EEnemyName EnemyName;

	// 메쉬
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		FMesh Mesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		class UClass* MannequinAnimInstance;


	// 몬스터 사망시 드랍될 아이템 배열
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropItem")
		TArray<FEnemyDropItem> EnemyDropItemArr;




	// 몬스터의 스텟
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;

	// 몬스터의 스피드
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
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

	// 보스 마네킹 애님인스턴스

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
