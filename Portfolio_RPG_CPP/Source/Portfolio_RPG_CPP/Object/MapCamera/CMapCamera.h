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
	void AddRenderingMapIcon(class ACCharacter_Base* SpawnCharacter);


public:	
	
	UPROPERTY(EditAnywhere, Category = MiniMap)
		class USpringArmComponent* MiniMap_SpringArm;
	
	UPROPERTY(EditAnywhere, Category = MiniMap)
		class USceneCaptureComponent2D* MiniMap_SceneCaptureComponent2D;



};
