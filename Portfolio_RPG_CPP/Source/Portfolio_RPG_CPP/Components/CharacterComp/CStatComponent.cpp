#include "CStatComponent.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Global.h"


#include "GameFramework/CharacterMovementComponent.h"



UCStatComponent::UCStatComponent()
{
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(OwnerCharacter);


	CharacterDataAsset = InPut_CharacterDataAsset;
}


void UCStatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCStatComponent::SetSpeed(ESpeedType input)
{
	CheckNull(OwnerCharacter);

	switch (input)
	{
	case ESpeedType::Stop:
		SetSpeedType(ESpeedType::Stop);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCharacterDataAsset()->Speed.Stop;
		break;

	case ESpeedType::Walk:
		SetSpeedType(ESpeedType::Walk);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCharacterDataAsset()->Speed.Walk;
		break;

	case ESpeedType::Joging:
		SetSpeedType(ESpeedType::Joging);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCharacterDataAsset()->Speed.Joging;
		break;

	case ESpeedType::Sprint:
		SetSpeedType(ESpeedType::Sprint);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCharacterDataAsset()->Speed.Sprint;
		break;

	default:
		break;
	}
}
