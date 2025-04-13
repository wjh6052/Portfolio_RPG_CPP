#pragma once

#include "CoreMinimal.h"
#include "../CCharacter_AI.h"
#include "CCharacter_Enemy.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACCharacter_Enemy : public ACCharacter_AI
{
	GENERATED_BODY()

public:
	ACCharacter_Enemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		EEnemyName EnemyName;


	FEnemy_DataTable Enemy_DataTable;

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
		class UWidgetComponent* HPBarWidget;


	class UCW_EnemyHpBar* CW_EnemyHpBar;

};
