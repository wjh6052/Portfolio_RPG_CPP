#include "CMapCamera.h"
#include "../../Global.h"


#include "Components/SceneCaptureComponent2D.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"


ACMapCamera::ACMapCamera()
{
	// �̴ϸ� �� ĸ��
	MiniMap_SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMap_SceneCaptureComponent2D"));
	MiniMap_SceneCaptureComponent2D->SetupAttachment(RootComponent);
	MiniMap_SceneCaptureComponent2D->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	MiniMap_SceneCaptureComponent2D->SetRelativeLocation(FVector(0.0f, 0.0f, 1000.0f));

	UCanvasRenderTarget2D* target2D;
	
	CHelpers::GetAsset<UCanvasRenderTarget2D>(&target2D, "CanvasRenderTarget2D'/Game/Asset/Widget_Asset/MiniMap_CanvasRenderTarget2D.MiniMap_CanvasRenderTarget2D'");
	MiniMap_SceneCaptureComponent2D->TextureTarget = target2D;


    // �����Ϳ� ���� �� ĸ���� �ڽ�
    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(RootComponent);

    // �⺻ ť�� �޽� �Ҵ�
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));

    if (CubeMesh.Succeeded())
    {
        VisualMesh->SetStaticMesh(CubeMesh.Object);
        VisualMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // ���ϴ� ũ��� ����
        VisualMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Ŭ�� �����ϰ�
        VisualMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
        VisualMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
        VisualMesh->SetHiddenInGame(true); // ���ӿ����� ����� �����Ϳ����� ���̰�
    }
}


void ACMapCamera::BeginPlay()
{
	Super::BeginPlay();

}




