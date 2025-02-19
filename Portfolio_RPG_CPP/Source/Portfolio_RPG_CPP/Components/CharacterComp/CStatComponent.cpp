#include "CStatComponent.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Character/Player/CCharacter_Player.h"
#include "../../Character/Enemy/CCharacter_Enemy.h"
#include "../../Character/NPC/CCharacter_NPC.h"
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


	CGameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(OwnerCharacter_Base->GetWorld()));

	
	switch (OwnerCharacter_Base->GetCharacterType())
	{
	case ECharacterType::Player:		
		PlayerDataSetting();
		break;

	case ECharacterType::Enemy:
		EnemyDataSetting();
		break;

	case ECharacterType::Boss:
		//BossDataSetting();
		break;

	case ECharacterType::NPC:
		NPCDataSetting();
		break;

	default:
		break;
	}
	
	
	

	SetSpeed(ESpeedType::Joging);
	

}

void UCStatComponent::PlayerDataSetting()
{
	OwnerACCharacter_Player = Cast<ACCharacter_Player>(OwnerCharacter_Base);

	// 나중에 무기마다 캐릭터 변경될 예정


	// 데이터테이블에서 가져온 데이터를 변수에 대입
	Player_DataTable = CGameInstance->Playe_Data_Arr[0];



	// 매쉬
	OwnerACCharacter_Player->GetMainMesh()->SetSkeletalMesh(GetPlayerDataTable().Mesh.MeshAsset);
	OwnerACCharacter_Player->GetMainMesh()->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	OwnerACCharacter_Player->GetMainMesh()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	OwnerACCharacter_Player->GetMesh()->SetRelativeLocation(GetPlayerDataTable().Mesh.Character_Location);
	OwnerACCharacter_Player->GetMesh()->SetRelativeRotation(GetPlayerDataTable().Mesh.Character_Rotation);

	// 매쉬 OutLine 
	OwnerACCharacter_Player->GetOutLineMesh()->SetSkeletalMesh(GetPlayerDataTable().Mesh.MeshOutLineAsset);

	// 애님인스턴스
	OwnerACCharacter_Player->GetMainMesh()->SetAnimInstanceClass(GetPlayerDataTable().Mesh.AnimInstance);
	OwnerACCharacter_Player->GetOutLineMesh()->SetAnimInstanceClass(GetPlayerDataTable().Mesh.AnimInstance);


	// 매쉬 콜리전 크기 조정
	OwnerACCharacter_Player->GetCapsuleComponent()->SetCapsuleRadius(GetPlayerDataTable().Mesh.CapsuleRadius);
	OwnerACCharacter_Player->GetCapsuleComponent()->SetCapsuleHalfHeight(GetPlayerDataTable().Mesh.CapsuleHalfHeight);

	// 카메라 스프링암 위지 조정
	OwnerACCharacter_Player->SpringArm->SetRelativeLocation(GetPlayerDataTable().Mesh.CameraSpringArm_Location);

}

void UCStatComponent::EnemyDataSetting()
{
	OwnerCharacter_Enemy = Cast<ACCharacter_Enemy>(OwnerCharacter_Base);

	// 데이터테이블에서 가져와 매쉬에 적용 예정
	if (OwnerCharacter_Enemy->EnemyName != EEnemyName::None)
	{
		
		for (int i = 0; i < CGameInstance->Enemy_Data_Arr.Num(); i++)
		{
			if (OwnerCharacter_Enemy->EnemyName == CGameInstance->Enemy_Data_Arr[i].EnemyName)
			{
				// 매쉬
				OwnerCharacter_Enemy->GetMainMesh()->SetSkeletalMesh(CGameInstance->Enemy_Data_Arr[i].Mesh.MeshAsset);
				OwnerCharacter_Enemy->GetMainMesh()->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
				OwnerCharacter_Enemy->GetMainMesh()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
				OwnerCharacter_Enemy->GetMesh()->SetRelativeLocation(CGameInstance->Enemy_Data_Arr[i].Mesh.Character_Location);
				OwnerCharacter_Enemy->GetMesh()->SetRelativeRotation(CGameInstance->Enemy_Data_Arr[i].Mesh.Character_Rotation);


				// 매쉬 OutLine 
				OwnerCharacter_Enemy->GetOutLineMesh()->SetSkeletalMesh(CGameInstance->Enemy_Data_Arr[i].Mesh.MeshOutLineAsset);


				// 애님인스턴스
				OwnerCharacter_Enemy->GetMesh()->SetAnimInstanceClass(CGameInstance->Enemy_Data_Arr[i].MannequinAnimInstance);
				OwnerCharacter_Enemy->GetMainMesh()->SetAnimInstanceClass(CGameInstance->Enemy_Data_Arr[i].Mesh.AnimInstance);
				OwnerCharacter_Enemy->GetOutLineMesh()->SetAnimInstanceClass(CGameInstance->Enemy_Data_Arr[i].Mesh.AnimInstance);


				// 매쉬 콜리전 크기 조정
				OwnerCharacter_Enemy->GetCapsuleComponent()->SetCapsuleRadius(CGameInstance->Enemy_Data_Arr[i].Mesh.CapsuleRadius);
				OwnerCharacter_Enemy->GetCapsuleComponent()->SetCapsuleHalfHeight(CGameInstance->Enemy_Data_Arr[i].Mesh.CapsuleHalfHeight);

				

				break;
			}
		}
	}

}

void UCStatComponent::BossDataSetting()
{

}

void UCStatComponent::NPCDataSetting()
{
	OwnerACCharacter_NPC = Cast<ACCharacter_NPC>(OwnerCharacter_Base);

	// 데이터테이블에서 가져와 매쉬에 적용 예정
	if (OwnerACCharacter_NPC->NPCName != ENPCName::None)
	{
		for (int i = 0; i < CGameInstance->NPCData_Arr.Num(); i++)
		{
			if (OwnerACCharacter_NPC->NPCName == CGameInstance->NPCData_Arr[i].NPCName)
			{
				// 매쉬
				OwnerACCharacter_NPC->GetMainMesh()->SetSkeletalMesh(CGameInstance->NPCData_Arr[i].Mesh.MeshAsset);
				OwnerACCharacter_NPC->GetMainMesh()->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
				OwnerACCharacter_NPC->GetMainMesh()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
				OwnerACCharacter_NPC->GetMesh()->SetRelativeLocation(CGameInstance->NPCData_Arr[i].Mesh.Character_Location);
				OwnerACCharacter_NPC->GetMesh()->SetRelativeRotation(CGameInstance->NPCData_Arr[i].Mesh.Character_Rotation);

				
				// 매쉬 OutLine 
				OwnerACCharacter_NPC->GetOutLineMesh()->SetSkeletalMesh(CGameInstance->NPCData_Arr[i].Mesh.MeshOutLineAsset);


				// 애님인스턴스
				OwnerACCharacter_NPC->GetMesh()->SetAnimInstanceClass(CGameInstance->NPCData_Arr[i].MannequinAnimInstance);
				OwnerACCharacter_NPC->GetMainMesh()->SetAnimInstanceClass(CGameInstance->NPCData_Arr[i].Mesh.AnimInstance);
				OwnerACCharacter_NPC->GetOutLineMesh()->SetAnimInstanceClass(CGameInstance->NPCData_Arr[i].Mesh.AnimInstance);
				

				// 매쉬 콜리전 크기 조정
				OwnerACCharacter_NPC->GetCapsuleComponent()->SetCapsuleRadius(CGameInstance->NPCData_Arr[i].Mesh.CapsuleRadius);
				OwnerACCharacter_NPC->GetCapsuleComponent()->SetCapsuleHalfHeight(CGameInstance->NPCData_Arr[i].Mesh.CapsuleHalfHeight);

				break;
			}
		}
	}


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
