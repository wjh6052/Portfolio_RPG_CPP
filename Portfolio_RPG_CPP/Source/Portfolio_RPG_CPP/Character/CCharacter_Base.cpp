#include "CCharacter_Base.h"
#include "../Global.h"

#include "../Object/Combat/CCombat_Base.h"





#include "GameFramework/Controller.h"

#include "Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperSpriteComponent.h"


#define INPUT




ACCharacter_Base::ACCharacter_Base()
{
	PrimaryActorTick.bCanEverTick = true;


	

	//Create Actor Component
	StatComponent = CreateDefaultSubobject<UCStatComponent>(L"StatComponent");
	CombatComponent = CreateDefaultSubobject<UCCombatComponent>(L"CombatComponent");

	
	// Main Mesh
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "SkeletalMesh'/Game/Asset/Characters/UE4_Mannequins/Meshes/UE4_SK_Mannequin.UE4_SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);



	// 매쉬
	CHelpers::CreateSceneComponent(this, &Main_SkeletalMesh, "&Main_SkeletalMesh", GetMesh());
	CHelpers::CreateSceneComponent(this, &OutLine_SkeletalMesh, "OutLine_SkeletalMesh", GetMesh());

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	GetMainMesh()->SetRenderCustomDepth(true);
	GetMainMesh()->CustomDepthStencilValue = 254;

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetVisibility(false);


	// -> MovementComp
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);


	// 맵에 표시될 아이콘
	MapIconComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MapIconComponent"));
	MapIconComponent->SetupAttachment(GetMesh());
	MapIconComponent->SetRelativeRotation(FRotator(0,-180.0f,-90.0f));
	MapIconComponent->SetRelativeLocation(FVector(0,0,250));
	MapIconComponent->SetRelativeScale3D(FVector(0.4f));
	
	// 맵에 보일 아이콘이 카메라에 안보이도록 설정
	MapIconComponent->bVisibleInSceneCaptureOnly = true;



	// 포스트프로세스 설정
	// 캐릭터 카툰 랜더링 설정
	GetMainMesh()->SetRenderCustomDepth(true);
	GetMainMesh()->CustomDepthStencilValue = 250;



}

void ACCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	

	CGameInstance = Cast<UCGameInstance>(GetWorld()->GetGameInstance());
}

void ACCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

float ACCharacter_Base::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	GetCombatComponent()->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	

	return 0.0f;
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

}

void ACCharacter_Base::OnMoveForward_Unarmed(float InAxis)
{
	CheckFalse(GetStatComponent()->IsCanMove());
	FVector direction = FQuat(FRotator(0, GetControlRotation().Yaw, 0)).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}


void ACCharacter_Base::OnMoveRight(float InAxis)
{

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
	
}


void ACCharacter_Base::OnJump()
{
	CheckFalse(GetStatComponent()->IsCanMove());

	if (IsMovementMode(EMovementMode::MOVE_Walking))
	{
		GetCombatComponent()->Current_Combat->bJumpAttack = true;
	}	
	ACharacter::Jump();
}


void ACCharacter_Base::OffJump()
{
	ACharacter::OnJumped();
}
#endif