#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CW_AI_Name.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCW_AI_Name : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// AI 이름 설정
	UFUNCTION(BlueprintImplementableEvent)
		void SetAIName(const FString& InAIName);
};
