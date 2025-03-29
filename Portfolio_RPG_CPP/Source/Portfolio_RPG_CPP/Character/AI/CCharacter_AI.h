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
	virtual void DyingTimeLineStart(); // Ÿ�Ӷ����� ���� �� ������ �Լ�
	
protected:
	// Ÿ�Ӷ���
	FTimeline DyingTimeLine;		// Ÿ�Ӷ���	
	
	UFUNCTION()
		virtual void TimelineUpdate(float Value); // ���� ����ɶ� ȣ��
	
	UFUNCTION()
		virtual void TimelineFinished(); // Ÿ�Ӷ��� ���� �� ȣ��
	
	
	UPROPERTY(EditAnywhere, Category = "DyingTimeLine")
		float TimeLinePlayRate = 0.2f;
	
	UPROPERTY(EditAnywhere, Category = "DyingTimeLine")
		class UCurveFloat* DissolveCurve;
	
	
private:
	TArray<class UMaterialInstanceDynamic*> MeshMateriaeDynamic;
};
