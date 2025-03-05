#include "CInteractionComponent.h"
#include "../../../Global.h"

#include "../../../CGameInstance.h"
#include "../../../Character/Player/CCharacter_Player.h"
#include "../../../Character/AI/NPC/CCharacter_NPC.h"
#include "../../../Object/Interaction/CInteraction_NPC.h"

#include "../../../Widgets/CWMain.h"
#include "../../../Widgets/NPC/CWNPCTalkUI.h"
#include "../../../Widgets/GameplayUI/CWGameplayUI.h"



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
	OwnerPlayer->GetWidgetComponent()->GetMainWidget()->GetGameplayUI()->AddInteraction(InIteminteraction);
}

void UCInteractionComponent::RemovalInteraction(AActor* InIteminteraction)
{
	OwnerPlayer->GetWidgetComponent()->GetMainWidget()->GetGameplayUI()->RemovalInteraction(InIteminteraction);
}




void UCInteractionComponent::StartNPCTalk(AActor* InNpc)
{
	ACCharacter_NPC* Character_NPC = Cast<ACInteraction_NPC>(InNpc)->OwnerNPC;

	if (CGameInstance == nullptr && Character_NPC == nullptr)
		return;


	for(FNPC_DataTable arr : CGameInstance->NPCData_Arr)
	{		
		if (Character_NPC->NPCName == arr.NPCName && arr.ConversationArr.Num() > 0)
		{

			OwnerPlayer->GetWidgetComponent()->CurrentUi = ECurrentUi::NPCDialogue;
			OwnerPlayer->GetWidgetComponent()->GetMainWidget()->SetWidgetSwitcher(OwnerPlayer->GetWidgetComponent()->CurrentUi);

			// 대화 ui에 택스트 변경
			OwnerPlayer->GetWidgetComponent()->GetMainWidget()->GetNPCTalkUI()->SetNPCTalkUI(arr);
			break;
		}

	}

		
}

void UCInteractionComponent::EndNPCTalk(AActor* InNpc)
{

	//OwnerPlayer->GetWidgetComponent()->CurrentUi = ECurrentUi::NPCDialogue;
	//OwnerPlayer->GetWidgetComponent()->GetMainWidget()->SetWidgetSwitcher(OwnerPlayer->GetWidgetComponent()->CurrentUi);
}


