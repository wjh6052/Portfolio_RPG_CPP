#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Datas/Data_DataTable.h"
#include "CWMain.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCWMain : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 플레이어 스크롤 관련
	UFUNCTION(BlueprintImplementableEvent)
		bool CanZoomScroll();

	UFUNCTION(BlueprintImplementableEvent)
		void SetInScroll(float InAxis);




	// 위젯 스위쳐
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetWidgetSwitcher(ECurrentUi InCurrentUi);


	// 상태에 따라 다른 상호작용
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UseInteraction();





public: // ------------------------------------------------기본UI------------------------------------------------
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintPure, Category = "GameplayUI")
		class UCWGameplayUI* GetGameplayUI();


public: // ------------------------------------------------NPC대화------------------------------------------------

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintPure, Category = "NPCTalk")
		class UCWNPCTalkUI* GetNPCTalkUI();






	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
		ECurrentUi CurrentUi;

};
