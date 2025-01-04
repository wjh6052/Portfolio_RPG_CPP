
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CFlightComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_RPG_CPP_API UCFlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCFlightComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
