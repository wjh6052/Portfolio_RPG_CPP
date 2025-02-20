#include "CHUD.h"
#include "Global.h"
#include "Character/CCharacter_Base.h"

#include "Engine/Canvas.h"
#include "GameFramework/Character.h"



ACHUD::ACHUD()
{

}

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	BaseCharacter = Cast<ACCharacter_Base>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	CheckNull(BaseCharacter);
	CheckNull(BaseCharacter->GetStatComponent());
	
	FString srt = "";

	srt = StaticEnum<ESpeedType>()->GetDisplayNameTextByValue(static_cast<int64>(BaseCharacter->GetStatComponent()->GetSpeedType())).ToString();
	DrawText("Speed Type : " + srt, FLinearColor::Red, 10, Canvas->ClipY - 50, nullptr, 1.75f);

	float WalkSpeed = BaseCharacter->GetCharacterMovement()->MaxWalkSpeed;
	DrawText("Speede : " + FString::FromInt(WalkSpeed), FLinearColor::Red, 10, Canvas->ClipY - 80, nullptr, 1.75f);

	srt = StaticEnum<EStatusType>()->GetDisplayNameTextByValue(static_cast<int64>(BaseCharacter->GetStatComponent()->GetStatusType())).ToString();
	DrawText("Status Type : " + srt, FLinearColor::Red, 10, Canvas->ClipY - 110, nullptr, 1.75f);

	srt = StaticEnum<EStateType>()->GetDisplayNameTextByValue(static_cast<int64>(BaseCharacter->GetStatComponent()->GetStateType())).ToString();
	DrawText("State Type : " + srt, FLinearColor::Red, 10, Canvas->ClipY - 140, nullptr, 1.75f);
}


