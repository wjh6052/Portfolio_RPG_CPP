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


	
	if (CGameInstance->CombatType == ECombatType::None)
	{		
		Player_Data = CGameInstance->Playe_Data_Arr[0];
		CGameInstance->CombatType = Player_Data.CombatType;
	}
	else
	{
		for (FPlayer_DataTable palyerData : CGameInstance->Playe_Data_Arr)
		{
			if (palyerData.CombatType == CGameInstance->CombatType)
			{
				Player_Data = palyerData;
			}
		}
	}
	

	

	// 매쉬
	OwnerACCharacter_Player->GetMainMesh()->SetSkeletalMesh(GetPlayerData().Mesh.MeshAsset);
	OwnerACCharacter_Player->GetOutLineMesh()->SetSkeletalMesh(GetPlayerData().Mesh.MeshOutLineAsset);

	OwnerACCharacter_Player->GetMesh()->SetRelativeLocation(FVector(0, 0, -GetPlayerData().Mesh.CapsuleHalfHeight));
	

	// 애님인스턴스
	OwnerACCharacter_Player->GetMainMesh()->SetAnimInstanceClass(GetPlayerData().Mesh.AnimInstance);
	OwnerACCharacter_Player->GetOutLineMesh()->SetAnimInstanceClass(GetPlayerData().Mesh.AnimInstance);


	// 매쉬 콜리전 크기 조정
	OwnerACCharacter_Player->GetCapsuleComponent()->SetCapsuleRadius(GetPlayerData().Mesh.CapsuleRadius);
	OwnerACCharacter_Player->GetCapsuleComponent()->SetCapsuleHalfHeight(GetPlayerData().Mesh.CapsuleHalfHeight);

	// 카메라 스프링암 위지 조정
	OwnerACCharacter_Player->SpringArm->SetRelativeLocation(FVector(0, 0, GetPlayerData().Mesh.CapsuleHalfHeight / 2));

}

void UCStatComponent::EnemyDataSetting()
{
	OwnerCharacter_Enemy = Cast<ACCharacter_Enemy>(OwnerCharacter_Base);


}

void UCStatComponent::BossDataSetting()
{

}

void UCStatComponent::NPCDataSetting()
{
	OwnerACCharacter_NPC = Cast<ACCharacter_NPC>(OwnerCharacter_Base);




}





void UCStatComponent::SetSpeed(ESpeedType input)
{
	CheckNull(OwnerCharacter_Base);

	
	switch (input)
	{
	case ESpeedType::Stop:
		SpeedType = input;
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetPlayerData().Speed.Stop;
		bCanMove = false;
		return;

	case ESpeedType::Walk:
		SpeedType = input;
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetPlayerData().Speed.Walk;
		break;

	case ESpeedType::Joging:
		SpeedType = input;
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetPlayerData().Speed.Joging;
		break;

	case ESpeedType::Run:
		SpeedType = input;
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetPlayerData().Speed.Run;
		break;

	case ESpeedType::Sprint:
		SpeedType = input;
		break;

	default:
		break;
	}

	bCanMove = true;
}
