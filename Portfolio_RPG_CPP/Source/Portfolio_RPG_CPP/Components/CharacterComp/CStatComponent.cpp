#include "CStatComponent.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Character/Player/CCharacter_Player.h"
#include "../../Character/AI/Enemy/CCharacter_Enemy.h"
#include "../../Character/AI/NPC/CCharacter_NPC.h"
#include "../../AIController/CAIController.h"
#include "../../Maps/CLevel_Main.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
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
		Player_Data = CGameInstance->Player_Data_Arr[0];
		SetCurrentStat(CGameInstance->Player_Data_Arr[0].Stat);
		CGameInstance->CombatType = Player_Data.Player_CombatData.CombatData.CombatType;
		
	}
	else
	{
		for (FPlayer_DataTable palyerData : CGameInstance->Player_Data_Arr)
		{
			if (palyerData.Player_CombatData.CombatData.CombatType == CGameInstance->CombatType)
			{			
				Player_Data = palyerData;
				SetCurrentStat(Player_Data.Stat);

				break;
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

	// 데이터테이블의 에너미의 비헤이비어트리를 적용
	for (FEnemy_DataTable Row : CGameInstance->Enemy_Data_Arr)
	{
		if (OwnerCharacter_Enemy->EnemyName == Row.EnemyName)
		{
			// 스텟설정
			SetCurrentStat(Row.Stat);

			// 비헤이비어트리 설정
			OwnerCharacter_Enemy->SetBehaviorTree(Row.BehaviorTree);



			// 기존의 컨트롤러 제거
			OwnerCharacter_Enemy->GetController()->Destroy();
			// 새로 적용될 컨트롤러 월드 상에 스폰 후 저장
			ACAIController* newController = OwnerCharacter_Enemy->GetWorld()->SpawnActor<ACAIController>(Row.AIControllerClass);

			if (newController)
				newController->Possess(OwnerCharacter_Enemy);


			


			break;
		}
	}

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

bool UCStatComponent::AddDamage(float InDamage)
{
	if (CurrentStat.HP - InDamage <= 0) // 죽었을 때
	{
		CurrentStat.HP = 0;

		return true;
	}
	else if (CurrentStat.HP - InDamage >= CurrentStat.HP_Max) // 힐을 받았을때 최대체력을 넘지 않도록 설정
	{
		CurrentStat.HP = CurrentStat.HP_Max;		
	}

	CurrentStat.HP -= InDamage;

	return false;
}

void UCStatComponent::SetStateType(EStateType input)
{
	StateType = input;

	switch (input)
	{
	case EStateType::Idling:
		break;
	case EStateType::Rolling:
		break;
	case EStateType::Attacking:
		break;
	case EStateType::Hitted:
		break;
	case EStateType::Groggy:
		break;
	case EStateType::Dying:
		OwnerCharacter_Base->GetCapsuleComponent()->SetGenerateOverlapEvents(false);
		OwnerCharacter_Base->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
		break;
	default:
		break;
	}
}
