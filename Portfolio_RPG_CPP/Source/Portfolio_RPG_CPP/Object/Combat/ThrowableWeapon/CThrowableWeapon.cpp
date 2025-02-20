#include "CThrowableWeapon.h"

// Sets default values
ACThrowableWeapon::ACThrowableWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACThrowableWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACThrowableWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

