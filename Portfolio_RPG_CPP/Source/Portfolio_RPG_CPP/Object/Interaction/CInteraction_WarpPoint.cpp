#include "CInteraction_WarpPoint.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Datas/DA/DA_MapIcon.h"
#include "../../Character/Player/CCharacter_Player.h"
#include "../../Widgets/CWMain.h"
#include "../../Widgets/Inventory/CWInventory.h"


#include "PaperSpriteComponent.h"




ACInteraction_WarpPoint::ACInteraction_WarpPoint()
{
    ItemName = L"워프 포인트";


    // 큐브 메쉬 컴포넌트 생성
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

        VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }



    // 맵에 표시될 아이콘
    MapIconComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MapIconComponent"));
    MapIconComponent->SetupAttachment(StaticMesh);
    MapIconComponent->SetRelativeRotation(FRotator(0, -180.0f, -90.0f));
    MapIconComponent->SetRelativeLocation(FVector(0, 0, 250));

    // 맵에 보일 아이콘이 카메라에 안보이도록 설정
    MapIconComponent->bVisibleInSceneCaptureOnly = true;


    // 워프포인트 이미지
    UObject* image;
    CHelpers::GetAsset<UObject>(&image, "Texture2D'/Game/Asset/Widget_Asset/Texture/T_WarpPoint.T_WarpPoint'");
    InteractionImage = image;
}


void ACInteraction_WarpPoint::BeginPlay()
{
    Super::BeginPlay();

    

    CGameInstance = Cast<UCGameInstance>(GetWorld()->GetGameInstance());

    if (CGameInstance)
    {
        MapIconComponent->SetSprite(CGameInstance->MapIcon_DA->Warp_Point_Sprite);
    }
    
}

void ACInteraction_WarpPoint::UseInteractionSystem()
{
    Super::UseInteractionSystem();

    if (CGameInstance->GetPlayerCharacter())
    {
        CGameInstance->GetPlayerCharacter()->GetWidgetComponent()->GetMainWidget()->GetInventory()->SwitchTabs(3, true);
        CGameInstance->GetPlayerCharacter()->GetWidgetComponent()->SetViewInventory();
    }
    
}

