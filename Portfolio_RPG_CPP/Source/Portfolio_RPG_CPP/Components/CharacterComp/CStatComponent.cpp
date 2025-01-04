#include "CStatComponent.h"
#include "../../Global.h"
#include "../../Character/CCharacter_Base.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



UCStatComponent::UCStatComponent()
{
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(OwnerCharacter);

	
	// ���ʿ��� �Ž� �Է�
	CHelpers::GetAsset<UCCharacterDataAsset>(&InPut_CharacterDataAsset, "Portfolio_RPG_CPP.CCharacterDataAsset'/Game/Data/DA_CharacterPlayer.DA_CharacterPlayer'");
	CheckNull(InPut_CharacterDataAsset);
	CharacterDataAsset = InPut_CharacterDataAsset;

	OwnerCharacter->GetMesh()->SetAnimInstanceClass(GetCharacterDataAsset()->Mesh.AnimInstance);

	OwnerCharacter->GetMesh()->SetSkeletalMesh(GetCharacterDataAsset()->Mesh.MeshAsset);
	OwnerCharacter->GetMesh()->SetRelativeLocation(GetCharacterDataAsset()->Mesh.Character_Location);
	OwnerCharacter->GetMesh()->SetRelativeRotation(GetCharacterDataAsset()->Mesh.Character_Rotation);

	OwnerCharacter->GetCapsuleComponent()->SetCapsuleRadius(GetCharacterDataAsset()->Mesh.CapsuleRadius);
	OwnerCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(GetCharacterDataAsset()->Mesh.CapsuleHalfHeight);

	//ī�޶� ����ġ ����
	OwnerCharacter->SpringArm->SetWorldLocation(GetCharacterDataAsset()->Mesh.CameraSpringArm_Location);
}


void UCStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetSpeed(ESpeedType::Joging);
	
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

	case ESpeedType::Run:
		SetSpeedType(ESpeedType::Run);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCharacterDataAsset()->Speed.Run;
		break;

	case ESpeedType::Sprint:
		SetSpeedType(ESpeedType::Sprint);
		break;

	default:
		break;
	}
}
