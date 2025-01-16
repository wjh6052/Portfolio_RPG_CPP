#include "CCharacter_Inventory.h"
#include "../../Global.h"

#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"


ACCharacter_Inventory::ACCharacter_Inventory()
{
	// StatComp�� ���� ĳ���� �±�
	CharacterType = ECharacterType::Player;


	// ����Ʈ ����Ʈ
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);
	SpotLight->SetRelativeLocation(FVector(200, 0, 240));
	SpotLight->SetRelativeRotation(FRotator(-60, -180, 0));
	SpotLight->Intensity = 9200.f;
	SpotLight->AttenuationRadius = 730.f;
	SpotLight->InnerConeAngle = 36.f;
	SpotLight->OuterConeAngle = 76.f;




	// ī�޶� ������ ��
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->SetRelativeLocation(FVector(0, 0, 40));
	SpringArm->SetRelativeRotation(FRotator(0, -180, 00));
	SpringArm->TargetArmLength = 140.0f;
	

}


void ACCharacter_Inventory::BeginPlay()
{
	Super::BeginPlay();


}


void ACCharacter_Inventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter_Inventory::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}
