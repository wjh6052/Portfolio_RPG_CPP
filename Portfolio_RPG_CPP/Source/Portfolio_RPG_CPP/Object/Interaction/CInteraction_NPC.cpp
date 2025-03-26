#include "CInteraction_NPC.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Datas/Data_NPC.h"
#include "../../Character/AI/NPC/CCharacter_NPC.h"

#include "Components/SphereComponent.h"


ACInteraction_NPC::ACInteraction_NPC()
{
	InteractionCategory = EInteractionCategory::NPC;

	SphereCollision->SetSphereRadius(200.f);
	

	UObject* NPC_Image;
	///Script/Engine.Texture2D'/Game/Asset/Widget_Asset/Texture/interaction/T_NPCInteraction.T_NPCInteraction'
	CHelpers::GetAsset<UObject>(&NPC_Image, "Texture2D'/Game/Asset/Widget_Asset/Texture/interaction/T_NPCInteraction.T_NPCInteraction'");
	InteractionImage = NPC_Image;
}


void ACInteraction_NPC::BeginPlay()
{
	Super::BeginPlay();

	


	//Quest_DataTable
	
}

void ACInteraction_NPC::SettingInteraction_NPC(class ACCharacter_NPC* InOwnerNPC)
{
	OwnerNPC = InOwnerNPC;

	UCGameInstance* gameInstance = Cast<UCGameInstance>(GetWorld()->GetGameInstance());

	for (FNPC_DataTable arr : gameInstance->NPCData_Arr)
	{
		if (OwnerNPC->NPCName == arr.NPCName && arr.ConversationArr.Num() > 0)
		{
			NPC_DataTable = arr;
			break;
		}

	}

	for (FQuest_DataTable quest_Arr : gameInstance->QuestData_Arr)
	{
		for (int32 quest_List : NPC_DataTable.QuestList)
		{
			if (quest_List == quest_Arr.QuestID)
			{
				Quest_DataTable_Arr.Add(quest_Arr);
			}
		}


	}
}