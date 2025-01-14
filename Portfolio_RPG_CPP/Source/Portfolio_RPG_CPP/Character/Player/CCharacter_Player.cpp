#include "CCharacter_Player.h"
#include "../../Global.h"


#include "Components/SkeletalMeshComponent.h"



ACCharacter_Player::ACCharacter_Player()
{
	// StatComp를 위한 캐릭터 태그
	CharacterType = ECharacterType::Player;

	//Create Actor Component
	FlightComponent = CreateDefaultSubobject<UCFlightComponent>(L"FlightComponent");

}


void ACCharacter_Player::BeginPlay()
{
	Super::BeginPlay();


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


	case EStatusType::Melee:
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

	case EStatusType::Melee:
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

	case EStatusType::Unarmed:
		if (IsMovementMode(EMovementMode::MOVE_Falling))
		{
			if (GetStatComponent()->IsStatus(EStatusType::Unarmed))
				GetFlightComponent()->StartFlight();
		}
		Super::OnJump();
		break;

	case EStatusType::Flight:
		GetFlightComponent()->EndFlight();
		break;

	case EStatusType::Climbing:
		break;

	case EStatusType::Melee:
		break;


	default:
		break;
	}
}

void ACCharacter_Player::OffJump()
{
	Super::OffJump();

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
	GetWorld()->GetTimerManager().SetTimer(RunTimer, this, &ACCharacter_Player::RunDelay, GetStatComponent()->GetPlayerDataTable().Run_Time, false);
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


	PlayAnimMontage(GetStatComponent()->GetPlayerDataTable().RollAnimMontage.AnimMontage, GetStatComponent()->GetPlayerDataTable().RollAnimMontage.PlayRate);
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


