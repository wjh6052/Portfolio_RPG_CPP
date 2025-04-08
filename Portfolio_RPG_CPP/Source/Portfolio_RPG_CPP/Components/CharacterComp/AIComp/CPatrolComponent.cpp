#include "CPatrolComponent.h"
#include "../../../Global.h"


#include "Components/SplineComponent.h"



UCPatrolComponent::UCPatrolComponent()
{

}


void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();


	CheckNull(Path)
	
}


void UCPatrolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



}


bool UCPatrolComponent::GetMoveTo(FVector& OutLocation, float& OutAcceptanceRadius)
{
	OutLocation = GetOwner()->GetActorLocation();
	OutAcceptanceRadius = AcceptanceRadius;
	CheckNullResult(Path, false);


	OutLocation = Path->GetSplineComp()->GetLocationAtSplinePoint(SplineIndex, ESplineCoordinateSpace::World);
	return true;
}

void UCPatrolComponent::SplineUpdateNextIndex()
{
	CheckNull(Path);
	SplineCount = Path->GetSplineComp()->GetNumberOfSplinePoints();


	// Reverse
	if (bReverse)
	{
		if (SplineIndex > 0)
		{
			SplineIndex--;
			return;
		}

		if (Path->GetSplineComp()->IsClosedLoop())
		{
			SplineIndex = SplineCount - 1;
			return;
		}

		SplineIndex = 1;
		bReverse = false;

		return;
	}

	//Forward
	if (SplineIndex < SplineCount - 1)
	{
		SplineIndex++;
		
		return;
	}

	if (Path->GetSplineComp()->IsClosedLoop())
	{
		SplineIndex = 0;
		return;
	}

	SplineIndex = SplineCount - 2;
	bReverse = true;
}
