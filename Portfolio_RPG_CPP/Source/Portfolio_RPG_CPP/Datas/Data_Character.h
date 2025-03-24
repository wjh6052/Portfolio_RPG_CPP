#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Data_Inventory.h"
#include "Data_Base.h"
#include "Data_Combat.h"
#include "Data_Character.generated.h"




//--enum---------------------------------------------------------------------

UENUM(BlueprintType)
enum class EEnemyName : uint8
{
	None			UMETA(DisplayName = "비어있음"),
	Dummy			UMETA(DisplayName = "허수아비"),
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
		float CapsuleHalfHeight = 80.f;

	
	UPROPERTY(EditAnywhere)
		float CapsuleRadius = 25.f;

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
struct FStat
{
	GENERATED_BODY()

public:
	// 현재 체력
	UPROPERTY(EditAnywhere)
		float HP = 100;
	// 최대 체력
	UPROPERTY(EditAnywhere)
		float HP_Max = 100;

	// 기본 데미지
	UPROPERTY(EditAnywhere)
		float Damage = 10;

	// 방어력
	UPROPERTY(EditAnywhere)
		float Defense = 5;

	// 크리티컬 데미지
	UPROPERTY(EditAnywhere)
		float Critical_Damage = 50;

	// 크리티컬 확률
	UPROPERTY(EditAnywhere)
		float Critical_Chance = 20;

	// 히트 저항 수치
	UPROPERTY(EditAnywhere)
		float Stance = 0;

	// 점프 높이 (기본 : 420)
	UPROPERTY(EditAnywhere)
		float JumpVelocity = 420.0f;

	// 스피스 스텟
	UPROPERTY(EditAnywhere)
		FSpeed Speed;
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






//--DataTable---------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FPlayer_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 메쉬
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		FMesh Mesh;



	// 스텟
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;



	// 비행 스피드
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		FSpeed_Flight Speed_Flight;

	// 달리기를 위한 더블클릭 허용 시간
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Speed")
		float Run_Time = 0.25f;




	// 플레이어의 무기
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat")
		FPlayer_CombatData Player_CombatData;
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



	// 몬스터의 스텟
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;


	// 몬스터 사망시 드랍될 아이템 배열
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropItem")
		TArray<FEnemyDropItem> EnemyDropItemArr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropItem")
		int LootMoneyCount = 1;


	// 공격 액션 데이터
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat")
		FCombatData CombatData;


};



USTRUCT(BlueprintType)
struct FBoss_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterType")
		FName BossName_Type;

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
