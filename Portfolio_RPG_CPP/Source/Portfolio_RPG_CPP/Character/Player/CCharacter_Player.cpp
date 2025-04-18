﻿#include "CCharacter_Player.h"
#include "../../Global.h"
#include "../../Widgets/CWMain.h"
#include "../../Widgets/Interaction/CWInteractionBox.h"
#include "../../AnimInstance/CAnimInstance_Player.h"
#include "../../Object/MapCamera/CMapCamera.h"
#include "../../Datas/DA/DA_MapIcon.h"



#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"



ACCharacter_Player::ACCharacter_Player()
{
	// StatComp를 위한 캐릭터 태그
	CharacterType = ECharacterType::Player;


	// 카메라 암
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;

	// 포스트프로세스를 통해 캐릭터를 회색으로 표현하기 위해 카메라 암을 물체들에 막히지 않도록 설정
	SpringArm->bDoCollisionTest = false;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;




	//Create Actor Component
	FlightComponent = CreateDefaultSubobject<UCFlightComponent>(L"FlightComponent");
	WidgetComponent = CreateDefaultSubobject<UCWidgetComponent>(L"WidgetComponent");
	InteractionComponent = CreateDefaultSubobject<UCInteractionComponent>(L"InteractionComponent");

	TSubclassOf<UCAnimInstance_Player> animInstanceClass;
	CHelpers::GetClass<UCAnimInstance_Player>(&animInstanceClass, "AnimBlueprint'/Game/AnimInstance/Player/ABP_Player_Mannequins'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);



	// 포스트프로세스 설정
	GetMainMesh()->CustomDepthStencilValue = 255;

}


void ACCharacter_Player::BeginPlay()
{
	Super::BeginPlay();

	// 미니맵 스폰
	{
		FActorSpawnParameters Params;
		ACMapCamera* minimap = GetWorld()->SpawnActor<ACMapCamera>(
			ACMapCamera::StaticClass(),
			GetActorLocation() + FVector(0, 0, 250),
			GetActorRotation(),
			Params
			);
		minimap->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}

	if (CGameInstance->MapIcon_DA != nullptr)
	{
		MapIconComponent->SetSprite(CGameInstance->MapIcon_DA->Player_Sprite);
	}
	
}


void ACCharacter_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACCharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 걷기
	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnWalk);

	// 뛰기
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACCharacter_Player::OffRun);

	// 스프린트
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACCharacter_Player::OffSprint);

	// 인벤토리
	PlayerInputComponent->BindAction("Inventory", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnInventory);

	// 상호작용
	PlayerInputComponent->BindAction("Interaction", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnInteraction);


	// 무기 선택 창
	PlayerInputComponent->BindAction("WeaponChoice", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnWeaponChoice);
	PlayerInputComponent->BindAction("WeaponChoice", EInputEvent::IE_Released, this, &ACCharacter_Player::OffWeaponChoice);


	//공격
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &ACCharacter_Player::OnAttack);
	PlayerInputComponent->BindAction("Skill_1", EInputEvent::IE_Released, this, &ACCharacter_Player::OnSkill_1);
	PlayerInputComponent->BindAction("Skill_2", EInputEvent::IE_Released, this, &ACCharacter_Player::OnSkill_2);
	PlayerInputComponent->BindAction("Skill_3", EInputEvent::IE_Released, this, &ACCharacter_Player::OnSkill_3);


	


	// 테스트
	PlayerInputComponent->BindAction("Test1", EInputEvent::IE_Released, this, &ACCharacter_Player::OnTest1);
	PlayerInputComponent->BindAction("Test2", EInputEvent::IE_Released, this, &ACCharacter_Player::OnTest2);

}


// 테스트 1
void ACCharacter_Player::OnTest1()
{
	GetCombatComponent()->EquipCombat();
	
}

// 테스트 2
void ACCharacter_Player::OnTest2()
{
	
}


void ACCharacter_Player::OnMoveForward(float InAxis)
{

	if (GetStatComponent()->IsStatus(EStatusType::Flight) && GetStatComponent()->GetSpeedType() == ESpeedType::Sprint)
		GetFlightComponent()->OnMoveForward_Flight(1);

	Super::OnMoveForward(InAxis);


	if (InAxis == 0.f)
	{
		if (GetStatComponent()->IsSpeedType(ESpeedType::Run))
		{
			GetStatComponent()->SetSpeed(ESpeedType::Joging);
		}
	}




	switch (GetStatComponent()->GetStatusType())
	{

	case EStatusType::Flight:
		GetFlightComponent()->OnMoveForward_Flight(InAxis);
		break;

	case EStatusType::Climbing:
		break;



	default:
		OnMoveForward_Unarmed(InAxis);
		break;
	}
}

void ACCharacter_Player::OnMoveRight(float InAxis)
{
	Super::OnMoveRight(InAxis);


	switch (GetStatComponent()->GetStatusType())
	{

	case EStatusType::Flight:
		GetFlightComponent()->OnMoveRight_Flight(InAxis);
		break;

	case EStatusType::Climbing:
		break;



	default:
		OnMoveRight_Unarmed(InAxis);
		break;
	}
}


void ACCharacter_Player::OnJump()
{
	switch (GetStatComponent()->GetStateType())
	{

	case EStateType::Idling:
		break;

	default:
		return;
		break;
	}

	switch (GetStatComponent()->GetStatusType())
	{



	case EStatusType::Flight:
		GetFlightComponent()->EndFlight();
		break;

	case EStatusType::Climbing:
		break;



	default:
		if (IsMovementMode(EMovementMode::MOVE_Falling))
		{
			if (GetStatComponent()->IsStatus(EStatusType::Unarmed))
				GetFlightComponent()->StartFlight();
		}
		Super::OnJump();
		break;
	}
}

void ACCharacter_Player::OffJump()
{
	Super::OffJump();
}


void ACCharacter_Player::OnHorizontalLook(float InAxis)
{
	if(GetWidgetComponent()->CurrentUi == ECurrentUi::InGameUI)
		Super::OnHorizontalLook(InAxis);
}

void ACCharacter_Player::OnVerticalLook(float InAxis)
{
	if (GetWidgetComponent()->CurrentUi == ECurrentUi::InGameUI)
		Super::OnVerticalLook(InAxis);
}


void ACCharacter_Player::OnWalk()
{
	switch (GetStatComponent()->GetSpeedType())
	{
	case ESpeedType::Walk:
		GetStatComponent()->SetSpeed(ESpeedType::Joging);
		break;

	default:
		GetStatComponent()->SetSpeed(ESpeedType::Walk);
		break;
	}

}


void ACCharacter_Player::OnRun()
{
	++Run;

	if (Run >= 2)
	{
		GetStatComponent()->SetSpeed(ESpeedType::Run);
		Run = 0;
	}
}

void ACCharacter_Player::OffRun()
{
	GetWorld()->GetTimerManager().SetTimer(RunTimer, this, &ACCharacter_Player::RunDelay, GetStatComponent()->GetPlayerData().Run_Time, false);
}


void ACCharacter_Player::RunDelay()
{
	Run = 0;
}


void ACCharacter_Player::OnSprint()
{
	CheckFalse(GetStatComponent()->IsCanMove());

	GetStatComponent()->SetSprint(true);

	if (GetStatComponent()->IsStatus(EStatusType::Flight))
	{
		CheckNull(GetFlightComponent());
		GetFlightComponent()->SetSprint(GetStatComponent()->GetSprint());


		return;
	}

	CheckFalse(GetStatComponent()->IsState(EStateType::Idling));
}

void ACCharacter_Player::OffSprint()
{
	GetStatComponent()->SetSprint(false);

	
	if (GetStatComponent()->IsStatus(EStatusType::Flight) && GetStatComponent()->GetSpeedType() == ESpeedType::Sprint)
	{
		GetFlightComponent()->SetSprint(GetStatComponent()->GetSprint());

		return;
	}
	CheckFalse(GetStatComponent()->IsStatus(EStatusType::Flight));
	

}


// 인벤토리창 열기
void ACCharacter_Player::OnInventory()
{
	GetWidgetComponent()->SetViewInventory();
}


// 상호작용
void ACCharacter_Player::OnInteraction()
{
	GetWidgetComponent()->GetMainWidget()->UseInteraction();

}

// 마우스 휠
void ACCharacter_Player::OnCameraZoom(float InAxis)
{
	CheckFalse(InAxis != 0);

	if (GetWidgetComponent()->GetMainWidget()->CanZoomScroll())
	{
		SpringArm->TargetArmLength = FMath::Clamp((InAxis * 10) + SpringArm->TargetArmLength, 150.f, 1000.f);
	}
	else
	{
		GetWidgetComponent()->GetMainWidget()->SetInScroll(InAxis);
		
	}
}


// 무기 선택 창
void ACCharacter_Player::OnWeaponChoice()
{
	GetWidgetComponent()->OnWeaponChoice(true);
}

void ACCharacter_Player::OffWeaponChoice()
{
	GetWidgetComponent()->OnWeaponChoice(false);
}


// 마우스 왼쪽 클릭
void ACCharacter_Player::OnAttack()
{
	if (GetStatComponent()->IsStatus(EStatusType::Combat))
	{
		GetCombatComponent()->OnAttack();

	}
}

void ACCharacter_Player::OnSkill_1()
{
	GetCombatComponent()->Skill_1();
}

void ACCharacter_Player::OnSkill_2()
{
	GetCombatComponent()->Skill_2();
}

void ACCharacter_Player::OnSkill_3()
{
	GetCombatComponent()->Skill_3();
}


