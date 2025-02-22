#include "CCharacter_Player.h"
#include "../../Global.h"
#include "../../Widgets/CWMain.h"
#include "../../Widgets/Interaction/CWInteractionBox.h"

// Test
#include "../../Object/Combat/CCombat_Base.h"



#include "Components/SkeletalMeshComponent.h"



ACCharacter_Player::ACCharacter_Player()
{
	// StatComp를 위한 캐릭터 태그
	CharacterType = ECharacterType::Player;

	//Create Actor Component
	FlightComponent = CreateDefaultSubobject<UCFlightComponent>(L"FlightComponent");
	WidgetComponent = CreateDefaultSubobject<UCWidgetComponent>(L"WidgetComponent");
	InteractionComponent = CreateDefaultSubobject<UCInteractionComponent>(L"InteractionComponent");


	// 포스트프로세스 설정
	GetMainMesh()->SetRenderCustomDepth(true);
	GetMainMesh()->CustomDepthStencilValue = 255;

}


void ACCharacter_Player::BeginPlay()
{
	Super::BeginPlay();


	// 테스트
	GetCombatComponent()->SpawnCombat();

}


void ACCharacter_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACCharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnWalk);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACCharacter_Player::OffRun);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACCharacter_Player::OffSprint);

	PlayerInputComponent->BindAction("Inventory", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnInventory);
	PlayerInputComponent->BindAction("Interaction", EInputEvent::IE_Pressed, this, &ACCharacter_Player::OnInteraction);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &ACCharacter_Player::OnAttack);


	PlayerInputComponent->BindAction("Test1", EInputEvent::IE_Released, this, &ACCharacter_Player::OnTest1);
	PlayerInputComponent->BindAction("Test2", EInputEvent::IE_Released, this, &ACCharacter_Player::OnTest2);

}


// 테스트 1
void ACCharacter_Player::OnTest1()
{
	GetCombatComponent()->SpawnCombat();
	
}

// 테스트 2
void ACCharacter_Player::OnTest2()
{
	GetCombatComponent()->Current_Combat->SpawnThrowableWeapon("");
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

void ACCharacter_Player::OnCameraZoom(float InAxis)
{
	CheckFalse(InAxis != 0);

	if (GetWidgetComponent()->GetMainWidget()->CanZoomScroll())
	{
		Super::OnCameraZoom(InAxis);
	}
	else
	{
		GetWidgetComponent()->GetMainWidget()->SetInScroll(InAxis);
		
	}
}

// 마우스 왼쪽 클릭
void ACCharacter_Player::OnAttack()
{
	if (GetStatComponent()->IsStatus(EStatusType::Combat))
	{
		GetCombatComponent()->OnAttack();

	}
}


