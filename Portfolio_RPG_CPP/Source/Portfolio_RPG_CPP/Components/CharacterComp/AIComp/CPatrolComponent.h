#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../../Object/AIObject/CPatrolPath.h"
#include "CPatrolComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_RPG_CPP_API UCPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPatrolComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	FORCEINLINE class ACPatrolPath* GetPath() { return Path; }
	FORCEINLINE int32 GetSplineIndex() { return SplineIndex; }

	bool GetMoveTo(FVector& OutLocation, float& OutAcceptanceRadius);
	void SplineUpdateNextIndex();
	

protected:
	UPROPERTY(EditInstanceOnly, Category = "PatrolPath")
		class ACPatrolPath* Path;

	int32 SplineIndex = 0;
	int32 SplineCount = 0;

	bool bReverse;
	float AcceptanceRadius = 10.f;
};
