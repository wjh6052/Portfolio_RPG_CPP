#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAISpawner.generated.h"


USTRUCT(BlueprintType)
struct FAISpawnerInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ACCharacter_AI> SpawnAI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ACPatrolPath* AIPatrol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RESpawnTime = 5.0f;

	// 스폰 지점이 스포너의 위치인지 (true = 스포너의 위치에서 스폰)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bSpawnerSpawn = false;

	FTimerHandle TimerHandle;
};



UCLASS()
class PORTFOLIO_RPG_CPP_API ACAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAISpawner();

protected:
	virtual void BeginPlay() override;

	void AISpawn(int32 index);

public:
	void ReSpawn(int32 index);


protected:
	TObjectPtr<UStaticMeshComponent> VisualMesh;



public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAISpawnerInfo> FAISpawnerInfo;




	class UCGameInstance* CGameInstance;
};
