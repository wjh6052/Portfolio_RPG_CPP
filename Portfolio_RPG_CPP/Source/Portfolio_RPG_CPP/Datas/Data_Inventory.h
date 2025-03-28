#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Data_Combat.h"
#include "Data_Inventory.generated.h"




//---------------------------Enum---------------------------------------------

UENUM(BlueprintType)
enum class EStarRating : uint8 // 등급 설정
{
	None		UMETA(DisplayName = "비어있음"),
	OneStar		UMETA(DisplayName = "1성"), 
	TwoStar		UMETA(DisplayName = "2성"),
	ThreeStar	UMETA(DisplayName = "3성"),
	Fourstar	UMETA(DisplayName = "4성"),
	Fivestar	UMETA(DisplayName = "5성"),
};

UENUM(BlueprintType)
enum class EInteractionCategory : uint8 // 아이템의 사용처
{
	None		UMETA(DisplayName = "비어있음"),
	Material	UMETA(DisplayName = "강화 재료"),
	Money		UMETA(DisplayName = "돈"),
	System		UMETA(DisplayName = "시스템"),
	NPC			UMETA(DisplayName = "NPC")
};

UENUM(BlueprintType)
enum class EItemCategory : uint8 // 아이템 카테고리 종류
{
	None		UMETA(DisplayName = "비어있음"),
	Material	UMETA(DisplayName = "재료 아이템"),	
	Potion		UMETA(DisplayName = "포션"),			
	Equipment	UMETA(DisplayName = "장비"),			
	Weapon		UMETA(DisplayName = "무기")			
};


UENUM(BlueprintType)
enum class EItemUseType : uint8 // 재료 아이템의 사용처
{
	None				UMETA(DisplayName = "비어있음"),
	PotionCraft			UMETA(DisplayName = "포션제작 재료"),		
	EquipmentUpgrade	UMETA(DisplayName = "장비 강화 재료"),		
	DaggerUpgrade		UMETA(DisplayName = "단검 강화 재료"),		
	BowUpgrade			UMETA(DisplayName = "활 강화 재료"),		
	StaffUpgrade		UMETA(DisplayName = "지팡이 강화 재료	")
};



//---------------------------struct---------------------------------------------

USTRUCT(BlueprintType)
struct FItemRarityColor // 등급별 색상 구조체
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor OneStarColor = FColor(255,255,255,255); // 흰색

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor TwoStarColor = FColor(60, 121, 125, 255); // 초록색

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor ThreeStarColor = FColor(70, 116, 178, 255); // 파란색

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor FourstarColor = FColor(152, 103, 208, 255); // 보라색

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor FivestarColor = FColor(197, 162, 113, 255); // 노란색


	FColor GetRatingColor(EStarRating Input)
	{
		switch (Input)
		{
		case EStarRating::OneStar:
			return OneStarColor;
			break;
		case EStarRating::TwoStar:
			return TwoStarColor;
			break;
		case EStarRating::ThreeStar:
			return ThreeStarColor;
			break;
		case EStarRating::Fourstar:
			return FourstarColor;
			break;
		case EStarRating::Fivestar:
			return FivestarColor;
			break;
		}

		return FColor(0);
	}
};



USTRUCT(BlueprintType)
struct FInteractionItemMaterial
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EStarRating StarRating;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EItemUseType ItemUseType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int MaterialNum;
};


USTRUCT(BlueprintType)
struct FItemType
{
	GENERATED_BODY()
		
public:
	// 아이템 카테고리 종류
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EItemCategory ItemCategory;

	// 재료 아이템의 사용처
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "ItemCategory == EItemCategory::Material"))
		EItemUseType ItemUseType;

	// 무기 또는 장비 종류
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "ItemCategory == EItemCategory::Equipment || ItemCategory == EItemCategory::Weapon"))
		ECombatType CombatType;
	
	//등급 설정
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EStarRating StarRating;

	//갯수
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int ItemCount = 1;


	// 드랍 확률 (0.0 ~ 1.0의 값 설정)
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float DropRate = 1;

};






//---------------------------DataTable---------------------------------------------


USTRUCT(BlueprintType)
struct FMaterialItem_DataTable : public FTableRowBase // 재료아이템 데이터테이블
{
	GENERATED_BODY()

public:


	// 아이템 카테고리 종류
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Category")
		EItemCategory ItemCategory; 

	// 아이템의 사용처
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Category")
		EItemUseType ItemUseType; 

	//등급 설정
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Category")
		EStarRating StarRating;



		
	// 아이템 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		FString ItemName; 

	// 아이템 갯수
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		int ItemCount = 0; 



	// 판매 가격
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Transaction")
		int buyPrice;

	// 구매 가격
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Transaction")
		int sellPrice;



	// 위젯에 표시될 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		UTexture2D* ItemImage; 
	
	// 아이템 간단 설명
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		FString ItemSimpleDescription; 

	// 아이템 설명
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		FString ItemDescription; 
	
	
};




// FPotionItem 포션 데이터 테이블 추가 예정

// FEquipmentItem 장비 데이터 테이블 추가 예정

// FWeaponItem 무기 데이터 테이블 추가 예정











UCLASS()
class PORTFOLIO_RPG_CPP_API AData_Inventory : public AActor
{
	GENERATED_BODY()


};
