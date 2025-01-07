#include "CStatComponent.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Maps/CLevel_Main.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



UCStatComponent::UCStatComponent()
{
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(OwnerCharacter);
	
}


void UCStatComponent::BeginPlay()
{
	Super::BeginPlay();


	// GameInstance���� ����ĳ������ Ÿ�Ը��� �ٸ� ������ ����
	switch (OwnerCharacter->GetCharacterType())
	{
	case ECharacterType::Player:
		PlayerDataSetting();
		break;

	case ECharacterType::Enemy:
		EnemyDataSetting();
		break;

	case ECharacterType::Boss:
		BossDataSetting();
		break;

	default:
		break;
	}
	
	
	

	SetSpeed(ESpeedType::Joging);
	

}

void UCStatComponent::PlayerDataSetting()
{
	// GameInstance���� ������ ���̺� ��������
	UDataTable* dataTable = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(OwnerCharacter->GetWorld()))->Player_DataTable;
	CheckNull(dataTable);

	// ���������̺��� ��� �� �̸��� ��������
	TArray<FName> rowNames = dataTable->GetRowNames();
	CheckTrue(rowNames.Num() < 0);

	FName firstRowName = rowNames[0];

	// ù ��° �� �����͸� �����ɴϴ�
	Player_DataTable = *dataTable->FindRow<FPlayer_DataTable>(firstRowName, TEXT(""));



	// ���ʿ��� �Ž� �Է�
		
	OwnerCharacter->GetMesh()->SetSkeletalMesh(GetPlayerDataTable().Mesh.MeshAsset);
	OwnerCharacter->GetMesh()->SetRelativeLocation(GetPlayerDataTable().Mesh.Character_Location);
	OwnerCharacter->GetMesh()->SetRelativeRotation(GetPlayerDataTable().Mesh.Character_Rotation);

	// �ִ��ν��Ͻ�
	OwnerCharacter->GetMesh()->SetAnimInstanceClass(GetPlayerDataTable().Mesh.AnimInstance);

	// �ݸ���
	OwnerCharacter->GetCapsuleComponent()->SetCapsuleRadius(GetPlayerDataTable().Mesh.CapsuleRadius);
	OwnerCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(GetPlayerDataTable().Mesh.CapsuleHalfHeight);


	//ī�޶� ����ġ ����
	OwnerCharacter->SpringArm->SetRelativeLocation(GetPlayerDataTable().Mesh.CameraSpringArm_Location);


	
}
void UCStatComponent::EnemyDataSetting()
{
	//// �������� ������ ���̺� ��������
	//UDataTable* dataTable = Cast<ACLevel_Main>(OwnerCharacter->GetWorld()->GetLevelScriptActor())->Character_DataTable;
	//if (dataTable != nullptr)
	//{
	//	const TMap<FName, uint8*>& rowMap = dataTable->GetRowMap();

	//	for (const TPair<FName, uint8*>& Pair : rowMap)
	//	{
	//		FCharacter_DataTable* ch_data = reinterpret_cast<FCharacter_DataTable*>(Pair.Value);
	//		if (ch_data && ch_data->CharacterType == OwnerCharacter->GetCharacterType())
	//		{
	//			CharacterData = *ch_data;
	//			break;
	//		}
	//	}
}

void UCStatComponent::BossDataSetting()
{

}

void UCStatComponent::SetSpeed(ESpeedType input)
{
	CheckNull(OwnerCharacter);

	/*switch (input)
	{
	case ESpeedType::Stop:
		SetSpeedType(ESpeedType::Stop);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCharacterData().Speed.Stop;
		break;

	case ESpeedType::Walk:
		SetSpeedType(ESpeedType::Walk);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCharacterData().Speed.Walk;
		break;

	case ESpeedType::Joging:
		SetSpeedType(ESpeedType::Joging);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCharacterData().Speed.Joging;
		break;

	case ESpeedType::Run:
		SetSpeedType(ESpeedType::Run);
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCharacterData().Speed.Run;
		break;

	case ESpeedType::Sprint:
		SetSpeedType(ESpeedType::Sprint);
		break;

	default:
		break;
	}*/
}
