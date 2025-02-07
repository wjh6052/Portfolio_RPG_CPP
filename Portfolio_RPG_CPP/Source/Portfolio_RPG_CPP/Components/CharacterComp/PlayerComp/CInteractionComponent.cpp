#include "CInteractionComponent.h"
#include "../../../Global.h"
#include "../../../Character/Player/CCharacter_Player.h"
#include "../../../Widgets/CWMain.h"



UCInteractionComponent::UCInteractionComponent()
{

}


void UCInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<ACCharacter_Player>(GetOwner());
	CheckNull(OwnerPlayer);
}

void UCInteractionComponent::AddInteraction(AActor* InIteminteraction)
{
	OwnerPlayer->GetWidgetComponent()->GetMainWidget()->AddInteraction(InIteminteraction);
}

void UCInteractionComponent::RemovalInteraction(AActor* InIteminteraction)
{
	OwnerPlayer->GetWidgetComponent()->GetMainWidget()->RemovalInteraction(InIteminteraction);
}


