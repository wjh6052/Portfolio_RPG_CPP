#include "CInteraction.h"
#include "../../Global.h"
#include "../../Character/Player/CCharacter_Player.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"



ACInteraction::ACInteraction()
{
	CHelpers::CreateSceneComponent(this, &DefaultRoot, "DefaultRoot", GetRootComponent());
	CHelpers::CreateSceneComponent(this, &StaticMesh, "StaticMesh", DefaultRoot);
	CHelpers::CreateSceneComponent(this, &SphereCollision, "SphereCollision", StaticMesh);


	SphereCollision->SetHiddenInGame(true);	
}

void ACInteraction::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());

	CheckNull(SphereCollision);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACInteraction::OnComponentBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ACInteraction::OnComponentEndOverlap);
}

void ACInteraction::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACCharacter_Player* player = Cast<ACCharacter_Player>(OtherActor);
	CheckNull(player);

	player->GetInteractionComponent()->AddInteraction(this);
}

void ACInteraction::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACCharacter_Player* player = Cast<ACCharacter_Player>(OtherActor);
	CheckNull(player);

	player->GetInteractionComponent()->RemovalInteraction(this);
}



