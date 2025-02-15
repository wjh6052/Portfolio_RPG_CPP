#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWidgetComponent.generated.h"


UENUM(BlueprintType)
enum class ECurrentUi : uint8
{
	InGameUI = 0     UMETA(DisplayName = "인게임 UI"),
	Inventory = 1    UMETA(DisplayName = "인벤토리"),
	NPCDialogue = 2  UMETA(DisplayName = "NPC 대화")
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_RPG_CPP_API UCWidgetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCWidgetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	// 인벤토리를 출력 및 지울때
	void SetViewInventory();


public:
	FORCEINLINE class UCWMain* GetMainWidget() { return MainWidget; }
	FORCEINLINE ECurrentUi GetCurrentUi() { return CurrentUi; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetCurrentUi(ECurrentUi Input) { CurrentUi = Input; }

	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<class UCWMain> MainWidgetClass;


public:
	ECurrentUi CurrentUi = ECurrentUi::InGameUI;
	ECurrentUi BackCurrentUi = ECurrentUi::InGameUI;


private:
	class APlayerController* PlayerController;
	class ACCharacter_Player* OwnerPlayer;

	class UCWMain* MainWidget;



};
