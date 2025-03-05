#include "CCharacter_NPC.h"
#include "../../../Global.h"
#include "../../../Object/Interaction/CInteraction_NPC.h"
#include "../../../AnimInstance/CAnimInstance_Base.h"


#include "Components/SphereComponent.h"


ACCharacter_NPC::ACCharacter_NPC()
{
	CharacterType = ECharacterType::NPC;


	TSubclassOf<UCAnimInstance_Base> animInstanceClass;
	CHelpers::GetClass<UCAnimInstance_Base>(&animInstanceClass, "AnimBlueprint'/Game/AnimInstance/NPC/ABP_NPC_Mannequins'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);
}


void ACCharacter_NPC::BeginPlay()
{
	Super::BeginPlay();

	


	Interaction_NPC = GetWorld()->SpawnActor<ACInteraction_NPC>(ACInteraction_NPC::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	Interaction_NPC->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("pelvis"));
	Interaction_NPC->OwnerNPC = this;
	Interaction_NPC->ItemName = CHelpers::GetEnumDisplayName<ENPCName>(NPCName);
	//Interaction_NPC->InteractionImage = 

}


