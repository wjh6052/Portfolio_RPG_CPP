#include "CCharacter_NPC.h"
#include "../../../Global.h"
#include "../../../CGameInstance.h"
#include "../../../Object/Interaction/CInteraction_NPC.h"
#include "../../../AnimInstance/CAnimInstance_Base.h"


#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"



ACCharacter_NPC::ACCharacter_NPC()
{
	CharacterType = ECharacterType::NPC;


	TSubclassOf<UCAnimInstance_Base> animInstanceClass;
	CHelpers::GetClass<UCAnimInstance_Base>(&animInstanceClass, "AnimBlueprint'/Game/AnimInstance/NPC/ABP_NPC_Mannequins'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);


	// �̴ϸʿ� ���� ������
	UPaperSprite* mapIcon;
	ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteFinder(
		TEXT("PaperSprite'/Game/Asset/Widget_Asset/Texture/MapIcon/T_Map_NPC_Sprite.T_Map_NPC_Sprite'")
	);
	if (SpriteFinder.Succeeded())
	{
		mapIcon = SpriteFinder.Object;
		MapIconComponent->SetSprite(mapIcon);
	}
}


void ACCharacter_NPC::BeginPlay()
{
	Super::BeginPlay();

	


	Interaction_NPC = GetWorld()->SpawnActor<ACInteraction_NPC>(ACInteraction_NPC::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	Interaction_NPC->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("pelvis"));
	Interaction_NPC->ItemName = CHelpers::GetEnumDisplayName<ENPCName>(NPCName);
	Interaction_NPC->SettingInteraction_NPC(this);
	//Interaction_NPC->InteractionImage = 



	CGameInstance = Cast<UCGameInstance>(GetWorld()->GetGameInstance());

	CGameInstance->Update_Quest.AddDynamic(this, &ACCharacter_NPC::UpdateInteractionQuestData);



	// AI�̸� ����
	UEnum* npcEnum = Cast<UEnum>(StaticEnum<ENPCName>());

	// UEnum�� ���� GetDisplayNameTextByValue ȣ��
	if (npcEnum)
	{
		CW_AIName->SetAIName(npcEnum->GetDisplayNameTextByValue(static_cast<int32>(NPCName)).ToString());
	}
}

void ACCharacter_NPC::UpdateInteractionQuestData(FQuest_DataTable NewQuest_Data, EQuestDetailsUpdateType QuestDetailsUpdateType, FString InName)
{
	Interaction_NPC->SettingInteraction_NPC(this);
}
