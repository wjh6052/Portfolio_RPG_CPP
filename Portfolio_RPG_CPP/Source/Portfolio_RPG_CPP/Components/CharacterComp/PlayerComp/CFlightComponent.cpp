#include "CFlightComponent.h"


UCFlightComponent::UCFlightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCFlightComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCFlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

