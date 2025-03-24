#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CW_EnemyHpBar.generated.h"


UCLASS()
class PORTFOLIO_RPG_CPP_API UCW_EnemyHpBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 상태에 따라 다른 상호작용
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UpdataHpBar(float InMaxHp, float InCurHp);


	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float MaxHp = 0.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float CurrentHP = 0.0f;
};
