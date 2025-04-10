#pragma once

#include "CoreMinimal.h"
#include "CInteraction_System.h"
#include "CInteraction_WarpPoint.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACInteraction_WarpPoint : public ACInteraction_System
{
	GENERATED_BODY()

public:
	ACInteraction_WarpPoint();

protected:
	virtual void BeginPlay() override;


protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<UStaticMeshComponent> VisualMesh;


public: 
	virtual void UseInteractionSystem() override;

public:
	// 맵에 표시될 아이콘
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MapIcon")
		class UPaperSpriteComponent* MapIconComponent;




private:
	class UCGameInstance* CGameInstance;
	
};
