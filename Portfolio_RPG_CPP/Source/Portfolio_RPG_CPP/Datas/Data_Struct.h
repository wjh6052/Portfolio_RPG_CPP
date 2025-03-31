#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data_Enum.h"
#include "Data_Struct.generated.h"


// ---------------------기본 구조체---------------------

// 애님 인스턴스 구조체
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



// --------------------- 아이템 관련 구조체 ---------------------

// 등급별 색상 구조체
USTRUCT(BlueprintType)
struct FItemRarityColor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor OneStarColor = FColor(255, 255, 255, 255); // 흰색

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


// 아이템 구별 구조체
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


// 아이템의 타입을 결정할 구조체
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








// --------------------- 강화 구조체 ---------------------

// 강화 스텟 구조체
USTRUCT(BlueprintType)
struct FGearStets
{
	GENERATED_BODY()

public:
	// 현재 체력
	UPROPERTY(EditAnywhere)
		float HP = 0;
	// 최대 체력
	UPROPERTY(EditAnywhere)
		float HP_Max = 0;

	// 기본 데미지
	UPROPERTY(EditAnywhere)
		float Damage = 0;

	// 방어력
	UPROPERTY(EditAnywhere)
		float Defense = 0;

	// 크리티컬 데미지
	UPROPERTY(EditAnywhere)
		float Critical_Damage = 0;

	// 크리티컬 확률
	UPROPERTY(EditAnywhere)
		float Critical_Chance = 0;

	// 히트 저항 수치
	UPROPERTY(EditAnywhere)
		float Stance = 0;
};


// 강화 확률 및 소유 재화 구조체
USTRUCT(BlueprintType)
struct FGearEnhancementData
{
	GENERATED_BODY()

public:

	// 강화 확률
	UPROPERTY(EditAnywhere)
		float EnhancementChance;

	// 강화 천장 시 올라갈 확률
	UPROPERTY(EditAnywhere)
		float PityIncreaseChance;

	// 강화 실패 시 천장이 올라갈 백분율
	UPROPERTY(EditAnywhere)
		float PityIncreaseRate;

	// 강화 성공 시 추가 스탯
	UPROPERTY(EditAnywhere)
		FGearStets AddGearStats;

	// 강화에 사용될 아이템 정보 및 개수
	UPROPERTY(EditAnywhere)
		TArray<FInteractionItemMaterial> RequiredItems;

	// 강화에 사용될 돈의 개수
	UPROPERTY(EditAnywhere)
		int RequiredMoney;

};







// --------------------- 컴뱃 구조체 ---------------------

// 공격 데미지 및 넉백 구조체
USTRUCT(BlueprintType)
struct FAttackDamage
{
	GENERATED_BODY()

public:

	// 데미지
	UPROPERTY(EditAnywhere)
		float Damage;

	// 크리티컬 확률
	UPROPERTY(EditAnywhere)
		float CriticalChance;

	bool bOnCritical = false;

	// 뒤로 넉백
	UPROPERTY(EditAnywhere)
		float KnockbackStrength;

	// 공중 넉백
	UPROPERTY(EditAnywhere)
		float KnockUpStrength;
};


// 공격 구조체
USTRUCT(BlueprintType)
struct FAttack
{
	GENERATED_BODY()

public:
	// 공격 애님 몽타주
	UPROPERTY(EditAnywhere, Category = "Anim Montage")
		FAnimMontageBase AnimMontage;

	// 콤보 ID
	UPROPERTY(EditAnywhere, Category = "Anim Montage")
		int ComboID;

	// 데미지
	UPROPERTY(EditAnywhere, Category = "Anim Montage")
		FAttackDamage AttackDamage;




	// 투척무기
	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon")
		bool bThrowableWeapon = false;

	// 데미지
	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon", meta = (EditCondition = "bThrowableWeapon"))
		FAttackDamage AttackDamage_ThrowableWeapon;

	// 투사체가 유지될 수명 시간
	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon", meta = (EditCondition = "bThrowableWeapon"))
		float Lifespan = 10.0f;

	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon", meta = (EditCondition = "bThrowableWeapon"))
		bool bTargeting = false;
};


// 공격 임팩트 구조체
USTRUCT(BlueprintType)
struct FImpactFlares
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* Impact_Flares;

	UPROPERTY(EditAnywhere)
		FVector Impact_Flares_Scale;

};


// 캐릭터가 소유할 무기 정보 구조체
USTRUCT(BlueprintType)
struct FCombatData
{
	GENERATED_BODY()


public:
	// 캐릭터가 들 무기 타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CombatType")
		ECombatType CombatType;

	// 무기
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class ACCombat_Base> CombatWeapon;

	// 무기 사용할 때 붙일 본 이름
	UPROPERTY(EditAnywhere, Category = "AttachBoneName")
		FName EquipBoneName;

	// 무기를 소지할 때 본 이름
	UPROPERTY(EditAnywhere, Category = "AttachBoneName")
		FName UnequipBoneName;


	// 투척 무기
	UPROPERTY(EditAnywhere, Category = "ThrowableWeapon")
		TSubclassOf<class ACThrowableWeapon> ThrowableWeaponClass;




	// 무기가 스폰할때나 디스폰할때 임팩트를 만들 머티리얼
	UPROPERTY(EditAnywhere, Category = "Material")
		class UMaterialInterface* WeaponMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
		FName ParameterName;


	UPROPERTY(EditAnywhere, Category = "Niagara")
		class UNiagaraSystem* ImpactFlares;

	UPROPERTY(EditAnywhere, Category = "Niagara")
		FVector ImpactFlaresScale;

	UPROPERTY(EditAnywhere, Category = "Niagara")
		class UNiagaraSystem* ImpactFlaresThrowable;

	UPROPERTY(EditAnywhere, Category = "Niagara")
		FVector ImpactFlaresThrowableScale;



	// 무기를 꺼낼때
	UPROPERTY(EditAnywhere, Category = "EquipWeapon")
		FAnimMontageBase EquipWeapon;

	// 무기를 넣을때
	UPROPERTY(EditAnywhere, Category = "EquipWeapon")
		FAnimMontageBase UnequipWeapon;



	// 데미지를 받을때의 애님인스턴스
	UPROPERTY(EditAnywhere, Category = "Hit")
		FAnimMontageBase Hit_Montage;



	// 콤보 공격
	UPROPERTY(EditAnywhere, Category = "Combo")
		TArray<FAttack> Combo_Attack;



	// 스킬 1
	UPROPERTY(EditAnywhere, Category = "Skill 1")
		TArray<FAttack> Skill_1;

	// 스킬 1의 쿨타임
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill 1")
		float Skill_1_Cooldown;


	// 스킬 2
	UPROPERTY(EditAnywhere, Category = "Skill 2")
		TArray<FAttack> Skill_2;

	// 스킬 2의 쿨타임
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill 2")
		float Skill_2_Cooldown;


	// 스킬 3
	UPROPERTY(EditAnywhere, Category = "Skill 3")
		TArray<FAttack> Skill_3;

	// 스킬 3의 쿨타임
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill 3")
		float Skill_3_Cooldown;



	// 달리기 도중 공격
	UPROPERTY(EditAnywhere, Category = "Run to Attack")
		FAttack RunToAttack;



	// 점프 도중 공격
	UPROPERTY(EditAnywhere, Category = "Jump to Attack")
		FAttack JumpToAttack;



	// 막기
	UPROPERTY(EditAnywhere, Category = "Block")
		FAnimMontageBase Block;

	// 막기 중 맞을때
	UPROPERTY(EditAnywhere, Category = "Block")
		FAnimMontageBase Block_Hit;


	// 죽을 때 애님인스턴스
	UPROPERTY(EditAnywhere, Category = "Die")
		FAnimMontageBase Die_Montage;
};


// 플레이어 캐릭터가 소유할 무기 정보 + UI 구조체
USTRUCT(BlueprintType)
struct FPlayer_CombatData
{
	GENERATED_BODY()


public:
	// UI에 표시될 텍스쳐
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "On")
		bool bOn = false;


	// UI에 표시될 무기의 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponName")
		FString WeaponName;

	// 무기의 강화 등급
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat Weapon Data")
		int WeaponEnhancementLevel = 0;

	// 현재 무기의 강화 상태
	UPROPERTY(BlueprintReadOnly)
		FGearEnhancementData CurrentGearEnhancementData;



	// UI에 표시될 텍스쳐
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CombatType")
		UTexture2D* CombatImage;

	// 스킬의 UI에 비춰질 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat UI")
		UTexture2D* Skill_1_Image;

	// 스킬의 UI에 비춰질 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat UI")
		UTexture2D* Skill_2_Image;

	// 스킬의 UI에 비춰질 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat UI")
		UTexture2D* Skill_3_Image;



	// 무기 데이터
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat")
		FCombatData CombatData;


};




// --------------------- 캐릭터 구조체 ---------------------

// 캐릭터가 소유할 매쉬 정보 구조체
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


// 캐릭터의 스피드스텟 구조체
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


// 캐릭터의 기본 스텟 구조체
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



// --------------------- 캐릭터 비행 구조체 ---------------------

// 캐릭터의 비행이 끝난 후 기본 이동속도 구조체
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

// 비행 스프린트 시 이동속도 구조체
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

// 비행 스프린트 시 이동속도 구조체
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






// --------------------- NPC 대화 구조체 ---------------------

// NPC대화의 내용과 선택지id를 설정하는 구조체
USTRUCT(BlueprintType)
struct FConversation 
{
	GENERATED_BODY()

public:
	// 선택지 Id
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Id")
		int ConversationId;

	// 선택지 ID 목록 (선택지가 없으면 비움)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Id")
		TArray<int32> NextChoices;


	// 대화 선택지의 타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Choice")
		EConversationType ChoiceType;


	// 위젯에서나올 선택지이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Choice")
		FText ChoiceName;




	// 선택지를 선택했을때 나올 대화
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dialogue")
		TArray<FText> ConversationTextArr;
};


// --------------------- 퀘스트 구조체 ---------------------

// 퀘스트 요구 몬스터
USTRUCT(BlueprintType)
struct FQuestDetails_Monster	
{
	GENERATED_BODY()
public:
	// 잡아야 하는 몬스터의 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EEnemyName EnemyName;

	// 잡아야 하는 몬스터의 수
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 KillCount;

	// 현재 잡은 보스의 수
	UPROPERTY(BlueprintReadWrite)
		int32 CurrentKillCount;
};


// 퀘스트 요구 보스
USTRUCT(BlueprintType)
struct FQuestDetails_Boss	
{
	GENERATED_BODY()

public:
	// 잡아야 하는 보스의 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EBossName BossName;

	// 잡아야 하는 보스의 수
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 KillCount;

	// 현재 잡은 보스의 수
	UPROPERTY(BlueprintReadWrite)
		int32 CurrentKillCount;
};


// 퀘스트 내용
USTRUCT(BlueprintType)
struct FQuestDetails	
{
	GENERATED_BODY()

public: 
	// 몬스터를 잡을 것을 요구
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bRequireMonsterKill;

	// 퀘스트 요구 몬스터
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bRequireMonsterKill"))
		TArray<FQuestDetails_Monster> MonsterTargets;



	// 보스를 잡을 것을 요구 
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bRequireBossKill;

	// 퀘스트 요구 보스
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bRequireBossKill"))
		TArray<FQuestDetails_Boss> BossTargets;



	// 아이템을 요구
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bRequireItemCollection;

	// 퀘스트 요구 아이템
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bRequireItemCollection"))
		TArray<FItemType> RequiredItems;



	// 돈을 요구
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bRequireMoney;

	// 돈의 액수  
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = "bRequireMoney"))
		int32 MoneyAmount;
};


// 퀘스트 보상
USTRUCT(BlueprintType)
struct FQuestReward		
{
	GENERATED_BODY()

public:
	// 보상으로 지급할 아이템 종류
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FItemType> RewardItems;

	// 보상으로 지급할 돈
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ClampMin = "0"))
		int32 RewardGold = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ClampMin = "0"))
		int32 RewardExe = 0;
};




UCLASS()
class PORTFOLIO_RPG_CPP_API UData_Struct : public UObject
{
	GENERATED_BODY()
	
};
