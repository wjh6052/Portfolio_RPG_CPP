#include "CStatComponent.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Character/Player/CCharacter_Player.h"
#include "../../Maps/CLevel_Main.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



UCStatComponent::UCStatComponent()
{
	OwnerCharacter_Base = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(OwnerCharacter_Base);


	
	
}


void UCStatComponent::BeginPlay()
{
	Super::BeginPlay();


	// GameInstance���� ����ĳ������ Ÿ�Ը��� �ٸ� ������ ����
	switch (OwnerCharacter_Base->GetCharacterType())
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
	OwnerACCharacter_Player = Cast<ACCharacter_Player>(OwnerCharacter_Base);

	// GameInstance���� ������ ���̺� ��������
	UDataTable* dataTable = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(OwnerACCharacter_Player->GetWorld()))->Player_DataTable;
	CheckNull(dataTable);

	// ���������̺��� ��� �� �̸��� ��������
	TArray<FName> rowNames = dataTable->GetRowNames();
	CheckTrue(rowNames.Num() < 0);

	FName firstRowName = rowNames[0];

	// ù ��° �� �����͸� �����ɴϴ�
	Player_DataTable = *dataTable->FindRow<FPlayer_DataTable>(firstRowName, TEXT(""));



	// ���ʿ��� ���� �Ž� �Է�		
	OwnerACCharacter_Player->GetMainMesh()->SetSkeletalMesh(GetPlayerDataTable().Mesh.MeshAsset);
	OwnerACCharacter_Player->GetMesh()->SetRelativeLocation(GetPlayerDataTable().Mesh.Character_Location);
	OwnerACCharacter_Player->GetMesh()->SetRelativeRotation(GetPlayerDataTable().Mesh.Character_Rotation);

	// ������ OutLine �Ž� �Է�
	OwnerACCharacter_Player->GetOutLineMesh()->SetSkeletalMesh(GetPlayerDataTable().MeshOutLineAsset);

	// �ִ��ν��Ͻ�
	OwnerACCharacter_Player->GetMainMesh()->SetAnimInstanceClass(GetPlayerDataTable().Mesh.AnimInstance);
	OwnerACCharacter_Player->GetOutLineMesh()->SetAnimInstanceClass(GetPlayerDataTable().Mesh.AnimInstance);


	



	

	// �ݸ���
	OwnerACCharacter_Player->GetCapsuleComponent()->SetCapsuleRadius(GetPlayerDataTable().Mesh.CapsuleRadius);
	OwnerACCharacter_Player->GetCapsuleComponent()->SetCapsuleHalfHeight(GetPlayerDataTable().Mesh.CapsuleHalfHeight);


	//ī�޶� ����ġ ����
	OwnerACCharacter_Player->SpringArm->SetRelativeLocation(GetPlayerDataTable().Mesh.CameraSpringArm_Location);


	
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
	CheckNull(OwnerCharacter_Base);

	switch (input)
	{
	case ESpeedType::Stop:
		SetSpeedType(ESpeedType::Stop);
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetPlayerDataTable().Speed.Stop;
		break;

	case ESpeedType::Walk:
		SetSpeedType(ESpeedType::Walk);
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetPlayerDataTable().Speed.Walk;
		break;

	case ESpeedType::Joging:
		SetSpeedType(ESpeedType::Joging);
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetPlayerDataTable().Speed.Joging;
		break;

	case ESpeedType::Run:
		SetSpeedType(ESpeedType::Run);
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetPlayerDataTable().Speed.Run;
		break;

	case ESpeedType::Sprint:
		SetSpeedType(ESpeedType::Sprint);
		break;

	default:
		break;
	}
}
