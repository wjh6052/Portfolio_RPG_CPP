#include "CQuestActor.h"
#include "../../CGameInstance.h"




ACQuestActor::ACQuestActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACQuestActor::BeginPlay()
{
	Super::BeginPlay();

	CGameInstance = Cast<UCGameInstance>(GetGameInstance());
	
}

void ACQuestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

