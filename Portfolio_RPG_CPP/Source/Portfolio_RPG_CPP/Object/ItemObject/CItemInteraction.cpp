#include "CItemInteraction.h"
#include "../../Global.h"
#include "../../Character/Player/CCharacter_Player.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"



ACItemInteraction::ACItemInteraction()
{
	CHelpers::CreateSceneComponent(this, &DefaultRoot, "DefaultRoot", GetRootComponent());
	CHelpers::CreateSceneComponent(this, &StaticMesh, "StaticMesh", DefaultRoot);
	CHelpers::CreateSceneComponent(this, &SphereComponent, "SphereComponent", StaticMesh);
}

void ACItemInteraction::BeginPlay()
{
	Super::BeginPlay();
	

	CheckNull(SphereComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACItemInteraction::OnComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ACItemInteraction::OnComponentEndOverlap);
}

void ACItemInteraction::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACCharacter_Player* player = Cast<ACCharacter_Player>(OtherActor);
	CheckNull(player);

	player->GetInteractionComponent()->AddInteraction(this);
}

void ACItemInteraction::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACCharacter_Player* player = Cast<ACCharacter_Player>(OtherActor);
	CheckNull(player);

	player->GetInteractionComponent()->RemovalInteraction(this);
}


