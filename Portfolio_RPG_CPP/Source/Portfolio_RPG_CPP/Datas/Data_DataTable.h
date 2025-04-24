#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data_Struct.h"
#include "Engine/DataTable.h"
#include "Data_DataTable.generated.h"



// ---------------------캐릭터 데이터 테이블---------------------

// 플레이어 데이터 테이블
USTRUCT(BlueprintType)
struct FPlayer_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 메쉬
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		FMesh Mesh;



	// 플레이어의 기본스텟
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Character_BaseStat;

	// 장비와의 포함된 현재 스텟
	UPROPERTY(BlueprintReadOnly, Category = "Stat")
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


	// 플레이어의 장비

	// 모자
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gear")
		FPlayer_Gear Gear_Helmet;

	// 상의
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gear")
		FPlayer_Gear Gear_Armor;

	// 장갑
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gear")
		FPlayer_Gear Gear_Gloves;

	// 신발
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gear")
		FPlayer_Gear Gear_Boots;

};


// 에너미 데이터 테이블
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
		TArray<FItemType> EnemyDropItemArr;


	// 돈 드랍 액수
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropMoney")
		int LootMoneyCount = 1;

	// 드랍 확률 (0.0 ~ 1.0의 값 설정)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropMoney")
		float MoneyDropRate = 1;

	// 아이템이 스폰하면서 날라갈 힘
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropPower")
		float DropPower;

	// 공격 액션 데이터
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat")
		FCombatData CombatData;


};

// 보스 데이터 테이블
USTRUCT(BlueprintType)
struct FBoss_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:

	// 보스 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Boss Name")
		EBossName BossName;



	// 보스 스텟
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		FStat Stat;

	// 보스 스킬
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
		TArray<FSkill> SkillArr;



	// 보스 사망시 애니메이션
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AnimMontage")
		FAnimMontageBase BossDeathAnimMontage;


	// 몬스터 사망시 드랍될 아이템 배열
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropItem")
		TArray<FItemType> DropItemArr;

	// 돈 드랍 액수
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropMoney")
		int LootMoneyCount = 1;

	// 드랍 확률 (0.0 ~ 1.0의 값 설정)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropMoney")
		float MoneyDropRate = 1;

	// 아이템이 스폰하면서 날라갈 힘
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DropPower")
		float DropPower;

};


// NPC 데이터 테이블
USTRUCT(BlueprintType)
struct FNPC_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPCType")
		ENPCType NPCType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPCType")
		ENPCName NPCName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPCType")
		FText NPCTitle;


	// 퀘스트 목록
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestList")
		TArray<int32> QuestList;


	// 판매 아이템 리스트
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SaleItemList", meta = (EditCondition = "ItemCategory == EItemCategory::Material"))
		TArray<FItemType> SaleItemList;


	// 말을 걸었을때 처음 나올 대화
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Conversation")
		FText FirstConversationText;

	// 대화를 시작해서 나오는 내용을 담은 FConversation
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Conversation")
		TArray<FConversation> ConversationArr;

};



// ---------------------플레이어 비행 데이터 테이블---------------------

// 플레이어 비행 데이터 테이블
USTRUCT(BlueprintType)
struct FPlayer_Flight : public FTableRowBase
{
	GENERATED_BODY()
public:
	//----------------------class--------------------------
	UPROPERTY(EditAnywhere, Category = "WingsClass")
		class UClass* WingsClass;

	UPROPERTY(EditAnywhere, Category = "WingsClass")
		class USkeletalMesh* WingsMesh;


	//----------------------FlightSpeed--------------------------
	UPROPERTY(EditAnywhere, Category = "FlightSpeed")
		FFlightSetting FlightSetting;

	UPROPERTY(EditAnywhere, Category = "FlightSpeed")
		FFlightSetting_Sprint FlightSetting_Sprint;



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
	UPROPERTY(EditAnywhere, Category = "Sprint_FlightUnderDust")
		bool bOnFlightUnderDust = true;

	UPROPERTY(EditAnywhere, Category = "Sprint_FlightUnderDust")
		float FlightUnderDustLength = -300.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "FlightUnderDust")
		TArray <class UNiagaraSystem*> FlightUnderDust_Impact;



	//----------------------SuperheroLnading--------------------------
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuperheroLanding")
		TArray <class UNiagaraSystem*> Landing_Impact;
};




// ---------------------아이템 데이터 테이블---------------------

// 아이템 데이터 테이블
USTRUCT(BlueprintType)
struct FMaterialItem_DataTable : public FTableRowBase // 재료아이템 데이터테이블
{
	GENERATED_BODY()

public:


	// 아이템 카테고리 종류
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Category")
		EItemCategory ItemCategory;

	// 아이템의 사용처
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Category", meta = (EditCondition = "ItemCategory == EItemCategory::Material"))
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


	// 포션 회복량
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Potion", meta = (EditCondition = "ItemCategory == EItemCategory::Potion"))
		float HealAmount = 0;

};


// FPotionItem 포션 데이터 테이블 추가 예정




// ---------------------퀘스트 데이터 테이블---------------------

// 퀘스트 데이터 테이블
USTRUCT(BlueprintType)
struct FQuest_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 퀘스트 ID 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestSetting")
		int32 QuestID;

	// 퀘스트 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestSetting")
		FString QuestName;

	// 퀘스트 설명
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestSetting")
		FString QuestDescription;


	// 퀘스트 내용
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestDetails")
		FQuestDetails QuestDetails;

	// 퀘스트를 수락할때 대화
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuestDetails")
		TArray<FString> AcceptDialogues;



	// 퀘스트 완료 후 대화
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuestReward")
		TArray<FString> RewardDialogues;

	// 퀘스트 보상
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestReward")
		FQuestReward QuestReward;

	// 퀘스트를 완료후의 코드
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "QuestReward")
		TSubclassOf<class ACQuestActor> QuestObject;


	// 현제 퀘스트의 상황
	UPROPERTY(BlueprintReadWrite)
		EQuestState QuestState;

	// 퀘스트를 준 NPC이름
	UPROPERTY(BlueprintReadWrite)
		FString NPCName;
};


// ---------------------NPC 대화 데이터 테이블---------------------

// NPC선택지에 나오는 아이콘 데이터테이블
USTRUCT(BlueprintType)
struct FConversationIcon_DataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 이미지의 타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Type")
		EConversationType ConversationType;

	// 위젯에 표시될 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Image")
		UTexture2D* ConversationImage;
};



// NPC 대화 상점 데이터 테이블
USTRUCT(BlueprintType)
struct FItemShop_DataTable : public FTableRowBase // 아이템상점 데이터테이블
{
	GENERATED_BODY()

public:
	// 카테고리
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
		EItemCategory ItemCategory;

	// 사용처
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
		EItemUseType ItemUseType;

	// 등급
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
		EStarRating StarRating;

	// 위젯에 표시될 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		UTexture2D* ItemImage;

	//-----------------------------------------------------------------------

		// 판매 가격
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Transaction")
		int buyPrice;

	// 구매 가격
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Transaction")
		int sellPrice;
};


// ---------------------NPC 강화 데이터 테이블---------------------

// NPC 장비강화 데이터 테이블
USTRUCT(BlueprintType)
struct FGearEnhancementData_DataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 장비 종류
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EGearType GearType;

	// 무기 종류
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		ECombatType WeaponType;

	// 강화 데이터
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FGearEnhancementData> GearEnhancementDataArr;

};













UCLASS()
class PORTFOLIO_RPG_CPP_API UData_DataTable : public UObject
{
	GENERATED_BODY()
	
};
