#include "CInteraction_NPC.h"
#include "../../Global.h"
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

	
}