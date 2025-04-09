#include "CMapCamera.h"
#include "../../Global.h"


#include "Components/SceneCaptureComponent2D.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"


ACMapCamera::ACMapCamera()
{
	// 미니맵 씬 캡쳐
	MiniMap_SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMap_SceneCaptureComponent2D"));
	MiniMap_SceneCaptureComponent2D->SetupAttachment(RootComponent);
	MiniMap_SceneCaptureComponent2D->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	MiniMap_SceneCaptureComponent2D->SetRelativeLocation(FVector(0.0f, 0.0f, 1000.0f));

	UCanvasRenderTarget2D* target2D;
	
	CHelpers::GetAsset<UCanvasRenderTarget2D>(&target2D, "CanvasRenderTarget2D'/Game/Asset/Widget_Asset/MiniMap_CanvasRenderTarget2D.MiniMap_CanvasRenderTarget2D'");
	MiniMap_SceneCaptureComponent2D->TextureTarget = target2D;


    // 에디터에 보일 씬 캡쳐의 박스
    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(RootComponent);

    // 기본 큐브 메시 할당
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));

    if (CubeMesh.Succeeded())
    {
        VisualMesh->SetStaticMesh(CubeMesh.Object);
        VisualMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // 원하는 크기로 조절
        VisualMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // 클릭 가능하게
        VisualMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
        VisualMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
        VisualMesh->SetHiddenInGame(true); // 게임에서는 숨기고 에디터에서만 보이게
    }
}


void ACMapCamera::BeginPlay()
{
	Super::BeginPlay();

}




