#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_Base.h"
#include "../../Components/CharacterComp/AIComp/CPatrolComponent.h"
#include "../../Widgets/AIName/CW_AI_Name.h"
#include "Components/TimelineComponent.h"
#include "CCharacter_AI.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_AI : public ACCharacter_Base
{
	GENERATED_BODY()
	

public:
	ACCharacter_AI();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	// Get
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE class UCPatrolComponent* GetPatrolComponent() { return PatrolComponent; }





private:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCPatrolComponent* PatrolComponent;


protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
		uint8 TeamID = 0;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;



protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UWidgetComponent* AINameWidget;


	class UCW_AI_Name* CW_AIName;


public:
	virtual void DyingTimeLineStart(); // 타임라인을 세팅 및 시작할 함수
	
protected:
	// 타임라인
	FTimeline DyingTimeLine;		// 타임라인	
	
	UFUNCTION()
		virtual void TimelineUpdate(float Value); // 값이 변경될때 호출
	
	UFUNCTION()
		virtual void TimelineFinished(); // 타임라인 종료 시 호출
	
	
	UPROPERTY(EditAnywhere, Category = "DyingTimeLine")
		float TimeLinePlayRate = 0.2f;
	
	UPROPERTY(EditAnywhere, Category = "DyingTimeLine")
		class UCurveFloat* DissolveCurve;
	
	
private:
	TArray<class UMaterialInstanceDynamic*> MeshMateriaeDynamic;
};
