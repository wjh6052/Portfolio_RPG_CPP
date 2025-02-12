#include "CInteractionComponent.h"
#include "../../../Global.h"

#include "../../../CGameInstance.h"
#include "../../../Character/Player/CCharacter_Player.h"
#include "../../../Character/NPC/CCharacter_NPC.h"
#include "../../../Object/Interaction/CInteraction_NPC.h"



#include "../../../Widgets/CWMain.h"



UCInteractionComponent::UCInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<ACCharacter_Player>(GetOwner());
	
	CGameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(OwnerPlayer->GetWorld()));
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
	ACCharacter_NPC* Character_NPC = Cast<ACInteraction_NPC>(InNpc)->OwnerNPC;

	if (CGameInstance == nullptr && Character_NPC == nullptr)
		return;


	for(FNPC_DataTable arr : CGameInstance->NPCData_Arr)
	{		
		if (Character_NPC->NPCName == arr.NPCName && arr.Conversation.Num() > 0)
		{
			Conversation = arr.Conversation;			
			break;
		}

	}
	
	CLog::Print(Conversation[0].ConversationName.ToString());
}


