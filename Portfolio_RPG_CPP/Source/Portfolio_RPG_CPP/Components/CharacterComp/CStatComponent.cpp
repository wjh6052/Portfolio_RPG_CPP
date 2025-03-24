#include "CStatComponent.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/CCharacter_Base.h"
#include "../../Character/Player/CCharacter_Player.h"
#include "../../Character/AI/Enemy/CCharacter_Enemy.h"
#include "../../Character/AI/NPC/CCharacter_NPC.h"
#include "../../AIController/CAIController.h"
#include "../../Maps/CLevel_Main.h"

#include "TimerManager.h"
#include "AIController.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
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
			OwnerCharacter_Enemy->Enemy_DataTable = Row;

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
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetCurrentStat().Speed.Stop;
		bCanMove = false;
		return;

	case ESpeedType::Walk:
		SpeedType = input;
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetCurrentStat().Speed.Walk;
		break;

	case ESpeedType::Joging:
		SpeedType = input;
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetCurrentStat().Speed.Joging;
		break;

	case ESpeedType::Run:
		SpeedType = input;
		OwnerCharacter_Base->GetCharacterMovement()->MaxWalkSpeed = GetCurrentStat().Speed.Run;
		break;

	case ESpeedType::Sprint:
		SpeedType = input;
		break;

	default:
		break;
	}

	bCanMove = true;
}

void UCStatComponent::Desh_Ragdoll()
{
	// 애니메이션 속도를 0으로 설정
	OwnerCharacter_Base->GetMesh()->GlobalAnimRateScale = 0.0f;

	OwnerCharacter_Base->GetMesh()->SetSimulatePhysics(true);
	OwnerCharacter_Base->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OwnerCharacter_Base->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	if (OwnerCharacter_Enemy)
	{
		GetWorld()->GetTimerManager().SetTimer(RagdollTimerHandle, [this]()
			{
				OwnerCharacter_Enemy->DyingTimeLineStart();
			},
			2.0f, false);
		
	}

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

void UCStatComponent::SetGroggy(float GroggyTime)
{
	SetStateLocked(true);
	SetStateType(EStateType::Groggy);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Groggy, [this]() 
		{
			SetStateLocked(false);
			SetStateType(EStateType::Idling); 
		},
		GroggyTime, false);
}

void UCStatComponent::SetStateType(EStateType input)
{
	if (bIsStateLocked)
		return;

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
