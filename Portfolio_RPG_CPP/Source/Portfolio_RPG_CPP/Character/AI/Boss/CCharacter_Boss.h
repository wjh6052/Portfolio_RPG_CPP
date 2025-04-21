#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_AI.h"
#include "CCharacter_Boss.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_Boss : public ACCharacter_AI
{
	GENERATED_BODY()
	
public:
	ACCharacter_Boss();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(BlueprintReadOnly, Category = "Data")
		FBoss_DataTable Boss_DataTable;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		EBossName BossName;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Effect")
		class UDecalComponent* AttackRangeDecal;




	// 스킬을 쓸때 호출 할 함수
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void PlaySkill(FAnimMontageBase InAnimMontage, FSkillDecal SkillDecal, int SkillIndex);

	// 데칼의 사이즈를 조절하는 함수
	UFUNCTION(BlueprintCallable)
		void SetAttackRangeDecalSize(FVector InDecalSize);


public:
	UPROPERTY(BlueprintReadOnly)
		TArray<float> CurrentSkillCooldownArr;

	UPROPERTY(BlueprintReadWrite)
		bool bOnSkill = false;

	UPROPERTY(BlueprintReadWrite)
		FVector DecalSize;

	UPROPERTY(BlueprintReadWrite)
		FVector DecalLocation;

	UPROPERTY(BlueprintReadWrite)
		FSkill CurrentSkill;

	UPROPERTY(BlueprintReadWrite)
		int CurrentIndex;


	
};
