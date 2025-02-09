#include "CCharacter_NPC.h"
#include "../../Global.h"
#include "../../Object/Interaction/CInteraction_NPC.h"

#include "Components/SphereComponent.h"


ACCharacter_NPC::ACCharacter_NPC()
{
	CharacterType = ECharacterType::NPC;
}


void ACCharacter_NPC::BeginPlay()
{
	Super::BeginPlay();

	
	if (InteractionNPC_Class)
	{
		Interaction_NPC = GetWorld()->SpawnActor<ACInteraction_NPC>(InteractionNPC_Class, FVector::ZeroVector, FRotator::ZeroRotator);		
	}
	else
	{
		Interaction_NPC = GetWorld()->SpawnActor<ACInteraction_NPC>(ACInteraction_NPC::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	}

	Interaction_NPC->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("pelvis"));
	Interaction_NPC->OwnerNPC = this;
	Interaction_NPC->ItemName = CHelpers::GetEnumDisplayName<ENPCName>(NPCName);
	//Interaction_NPC->InteractionImage = 

}


