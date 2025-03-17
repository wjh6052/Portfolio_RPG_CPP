#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPatrolPath.generated.h"





UCLASS()
class PORTFOLIO_RPG_CPP_API ACPatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPatrolPath();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;


public:
	FORCEINLINE class USplineComponent* GetSplineComp() { return Spline; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class USplineComponent* Spline;


private:
	UPROPERTY(EditInstanceOnly, Category = "Spline")
		bool bLoop;
};
