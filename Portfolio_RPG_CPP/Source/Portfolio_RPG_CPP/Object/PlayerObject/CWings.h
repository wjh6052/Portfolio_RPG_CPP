#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWings.generated.h"

UCLASS()
class PORTFOLIO_RPG_CPP_API ACWings : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWings();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
