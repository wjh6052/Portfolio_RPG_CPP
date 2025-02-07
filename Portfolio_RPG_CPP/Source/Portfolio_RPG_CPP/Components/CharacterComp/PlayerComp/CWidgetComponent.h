#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWidgetComponent.generated.h"




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


	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<class UCWMain> MainWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<class UCWInventory> InventoryClass;

private:
	class APlayerController* PlayerController;
	class ACCharacter_Player* OwnerPlayer;

	class UCWMain* MainWidget;
	class UCWInventory* InventoryWidget;
};
