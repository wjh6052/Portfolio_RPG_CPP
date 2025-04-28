#include "CAISpawner.h"
#include "../../Global.h"
#include "../../CGameInstance.h"
#include "../../Character/AI/CCharacter_AI.h"


#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"




ACAISpawner::ACAISpawner()
{
    // 큐브 메쉬 컴포넌트 생성
    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    RootComponent = VisualMesh;

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

void ACAISpawner::BeginPlay()
{
	Super::BeginPlay();

    CGameInstance = Cast<UCGameInstance>(GetWorld()->GetGameInstance());

    for (int i = 0; i < FAISpawnerInfo.Num(); i++)
        AISpawn(i);
    

   
	
}

void ACAISpawner::AISpawn(int32 index)
{
    if (FAISpawnerInfo[index].SpawnAI == nullptr || FAISpawnerInfo[index].AIPatrol == nullptr)
        return;


    

    FActorSpawnParameters Params;
    ACCharacter_AI* spawnAi = GetWorld()->SpawnActor<ACCharacter_AI>(
        FAISpawnerInfo[index].SpawnAI,
        FAISpawnerInfo[index].bSpawnerSpawn ? GetActorLocation() : FAISpawnerInfo[index].AIPatrol->GetSplineComp()->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World),
        FRotator::ZeroRotator,
        Params
        );
    spawnAi->SpawnDefaultController();
    spawnAi->PatrolComponent->SetPath(FAISpawnerInfo[index].AIPatrol);
    spawnAi->AISpawner = this;
    spawnAi->Spawnindex = index;


}

void ACAISpawner::ReSpawn(int32 index)
{
    GetWorld()->GetTimerManager().SetTimer(
        FAISpawnerInfo[index].TimerHandle,
        FTimerDelegate::CreateLambda([=]()
            {
                AISpawn(index);
            }),
        FAISpawnerInfo[index].RESpawnTime,
        false   
    );
}




