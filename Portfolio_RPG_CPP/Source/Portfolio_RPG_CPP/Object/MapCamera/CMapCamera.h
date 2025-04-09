#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMapCamera.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACMapCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMapCamera();

protected:
	virtual void BeginPlay() override;




public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MiniMap")
		class USceneCaptureComponent2D* MiniMap_SceneCaptureComponent2D;

	TObjectPtr<UStaticMeshComponent> VisualMesh;


};
