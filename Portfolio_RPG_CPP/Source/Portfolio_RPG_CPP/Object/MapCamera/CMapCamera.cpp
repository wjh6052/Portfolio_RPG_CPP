#include "CMapCamera.h"
#include "../../Global.h"


#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"


ACMapCamera::ACMapCamera()
{
	// ¹Ì´Ï¸Ê Ä«¸Þ¶ó ¾Ï
	MiniMap_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMap_SpringArm"));
	MiniMap_SpringArm->SetupAttachment(RootComponent);
	MiniMap_SpringArm->TargetArmLength = 1000.0f;
	MiniMap_SpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	
	
	// ¹Ì´Ï¸Ê ¾À Ä¸ÃÄ
	MiniMap_SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMap_SceneCaptureComponent2D"));
	MiniMap_SceneCaptureComponent2D->SetupAttachment(MiniMap_SpringArm);
	
	UCanvasRenderTarget2D* target2D;
	
	CHelpers::GetAsset<UCanvasRenderTarget2D>(&target2D, "CanvasRenderTarget2D'/Game/Asset/Widget_Asset/MiniMap_CanvasRenderTarget2D.MiniMap_CanvasRenderTarget2D'");
	MiniMap_SceneCaptureComponent2D->TextureTarget = target2D;

}


void ACMapCamera::BeginPlay()
{
	Super::BeginPlay();

}




