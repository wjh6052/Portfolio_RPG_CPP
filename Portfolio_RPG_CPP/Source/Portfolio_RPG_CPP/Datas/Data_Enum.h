#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data_Enum.generated.h"

// 무기 종류 열거형
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


// 장비 종류 열거형
UENUM(BlueprintType)
enum class EGearType : uint8
{
	None		UMETA(DisplayName = "비어있음"),
	Weapon		UMETA(DisplayName = "무기"),
	Helmet		UMETA(DisplayName = "모자"),
	Armor		UMETA(DisplayName = "상의"),
	Gloves		UMETA(DisplayName = "장갑"),
	Boots		UMETA(DisplayName = "신발")
};


UENUM(BlueprintType)
enum class EEnemyName : uint8
{
	None			UMETA(DisplayName = "비어있음"),
	Dummy			UMETA(DisplayName = "허수아비"),
	Hilichurl		UMETA(DisplayName = "츄츄족")
};

UENUM(BlueprintType)
enum class EBossName : uint8
{
	None			UMETA(DisplayName = "비어있음")
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



UENUM(BlueprintType)
enum class ENPCType : uint8 // NPC종류 열거형
{
	None			UMETA(DisplayName = "비어있음"),
	Common			UMETA(DisplayName = "일반 NPC"),
	Merchant		UMETA(DisplayName = "상인"),
	Blacksmith 		UMETA(DisplayName = "대장장이")

};


UENUM(BlueprintType)
enum class ENPCName : uint8 // NPC이름 열거형
{
	None		UMETA(DisplayName = "비어있음"),
	Evelyn		UMETA(DisplayName = "이블린"),
	Citlali		UMETA(DisplayName = "시틀라리"),
	Navia 		UMETA(DisplayName = "나비아")

};


UENUM(BlueprintType)
enum class EQuestState : uint8  // 퀘스트의 상태
{
	NotStarted		UMETA(DisplayName = "시작 전"),
	InProgress		UMETA(DisplayName = "진행 중"),
	Completed		UMETA(DisplayName = "완료됨")

};


UENUM(BlueprintType)
enum class EQuestDetailsUpdateType : uint8  // 변경된 퀘스트 알림
{
	None			UMETA(DisplayName = "비어있음"),
	Monster			UMETA(DisplayName = "몬스터"),
	Boss			UMETA(DisplayName = "보스"),
	Itme			UMETA(DisplayName = "아이템")

};

UENUM(BlueprintType)
enum class EConversationType : uint8 // NPC대화종류 열거형
{
	None			UMETA(DisplayName = "비어있음"),
	Dialogue		UMETA(DisplayName = "대화"),
	Shop			UMETA(DisplayName = "퀘스트"),
	Blacksmith		UMETA(DisplayName = "상점"),
	Quest         	UMETA(DisplayName = "대장장이"),
	DialogueEnd     UMETA(DisplayName = "대화종료")
};




UCLASS()
class PORTFOLIO_RPG_CPP_API UData_Enum : public UObject
{
	GENERATED_BODY()
	
};
