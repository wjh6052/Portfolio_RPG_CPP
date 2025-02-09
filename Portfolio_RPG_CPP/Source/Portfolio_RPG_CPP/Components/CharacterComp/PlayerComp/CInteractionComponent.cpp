#include "CInteractionComponent.h"
#include "../../../Global.h"
#include "../../../Character/Player/CCharacter_Player.h"
#include "../../../Character/NPC/CCharacter_NPC.h"
#include "../../../Object/Interaction/CInteraction_NPC.h"
#include "../../../Datas/Data_NPC.h"


#include "../../../Widgets/CWMain.h"



UCInteractionComponent::UCInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<ACCharacter_Player>(GetOwner());
	CheckNull(OwnerPlayer);
}

void UCInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UCInteractionComponent::AddInteraction(AActor* InIteminteraction)
{
	OwnerPlayer->GetWidgetComponent()->GetMainWidget()->AddInteraction(InIteminteraction);
}

void UCInteractionComponent::RemovalInteraction(AActor* InIteminteraction)
{
	OwnerPlayer->GetWidgetComponent()->GetMainWidget()->RemovalInteraction(InIteminteraction);
}




void UCInteractionComponent::StartNPCInteraction(AActor* InNpc)
{
	ACInteraction_NPC* interaction_NPC = Cast<ACInteraction_NPC>(InNpc);
	FString a = CHelpers::GetEnumDisplayName<ENPCName>(interaction_NPC->OwnerNPC->NPCName);
	a += L"NPC대화시작";

	CLog::Print(a);
}


