#include "CCharacter_Base.h"
#include "../Global.h"
#include "Player/CAnimInstance_Player.h"



#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"


#define INPUT




ACCharacter_Base::ACCharacter_Base()
{
	PrimaryActorTick.bCanEverTick = true;


	// 카메라 암
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;
	

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;


	//Create Actor Component
	StatComponent = CreateDefaultSubobject<UCStatComponent>(L"StatComponent");

	
	// Main Mesh
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "SkeletalMesh'/Game/Asset/Characters/UE4_Mannequins/Meshes/UE4_SK_Mannequin.UE4_SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);
	TSubclassOf<UCAnimInstance_Player> animInstanceClass;
	CHelpers::GetClass<UCAnimInstance_Player>(&animInstanceClass, "AnimBlueprint'/Game/Characters/Player/ABP_Player_Mannequins'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);


	// 매쉬
	CHelpers::CreateSceneComponent(this, &Main_SkeletalMesh, "&Main_SkeletalMesh", GetMesh());
	CHelpers::CreateSceneComponent(this, &OutLine_SkeletalMesh, "OutLine_SkeletalMesh", GetMesh());

	Main_SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, -80.f));
	Main_SkeletalMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));


	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetVisibility(false);


	// -> MovementComp
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
}

void ACCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACCharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACCharacter_Base::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACCharacter_Base::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACCharacter_Base::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACCharacter_Base::OnVerticalLook);
	PlayerInputComponent->BindAxis("CameraZoom", this, &ACCharacter_Base::OnCameraZoom);


	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACCharacter_Base::OnJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACCharacter_Base::OffJump);
}


#ifdef INPUT

void ACCharacter_Base::OnMoveForward(float InAxis)
{
	CheckTrue(InAxis == 0);
	CheckFalse(GetStatComponent()->IsCanMove());
}

void ACCharacter_Base::OnMoveForward_Unarmed(float InAxis)
{
	CheckFalse(GetStatComponent()->IsCanMove());
	FVector direction = FQuat(FRotator(0, GetControlRotation().Yaw, 0)).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}


void ACCharacter_Base::OnMoveRight(float InAxis)
{
	CheckFalse(GetStatComponent()->IsCanMove());
	CheckTrue(InAxis == 0);
}

void ACCharacter_Base::OnMoveRight_Unarmed(float InAxis)
{
	CheckFalse(GetStatComponent()->IsCanMove());
	FVector direction = FQuat(FRotator(0, GetControlRotation().Yaw, 0)).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}


void ACCharacter_Base::OnHorizontalLook(float InAxis)
{
	AddControllerYawInput(InAxis);
}


void ACCharacter_Base::OnVerticalLook(float InAxis)
{
	AddControllerPitchInput(InAxis);
}


void ACCharacter_Base::OnCameraZoom(float InAxis)
{
	SpringArm->TargetArmLength = FMath::Clamp((InAxis * 10) + SpringArm->TargetArmLength, 150.f, 1000.f);
}


void ACCharacter_Base::OnJump()
{
	CheckFalse(GetStatComponent()->IsCanMove());
	ACharacter::Jump();
}


void ACCharacter_Base::OffJump()
{
	ACharacter::OnJumped();
}
#endif