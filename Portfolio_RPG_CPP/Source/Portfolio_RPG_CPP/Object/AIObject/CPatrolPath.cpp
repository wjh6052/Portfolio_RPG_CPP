#include "CPatrolPath.h"
#include "../../Global.h"

#include "Components/SplineComponent.h"


ACPatrolPath::ACPatrolPath()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Spline, "Spline", Root);

	Spline->SetRelativeLocation(FVector(0, 0, 30));
	//Spline->ScaleVisualizationWidth = 30.f;
	//Spline->bShouldVisualizeScale = true;
	//Spline->EditorUnselectedSplineSegmentColor = FLinearColor::Red;
}

void ACPatrolPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Spline->SetClosedLoop(bLoop);
}

void ACPatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
}


