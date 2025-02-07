#include "CWidgetComponent.h"
#include "../../../Global.h"
#include "../../../Character/Player/CCharacter_Player.h"
#include "../../../Widgets/CWMain.h"
#include "../../../Widgets/Inventory/CWInventory.h"

#include "GameFramework/PlayerController.h"


UCWidgetComponent::UCWidgetComponent()
{
	OwnerPlayer = Cast<ACCharacter_Player>(GetOwner());


	CHelpers::GetClass<UCWMain>(&MainWidgetClass, "WidgetBlueprint'/Game/Widgets/CW_Main.CW_Main_C'");
	CHelpers::GetClass<UCWInventory>(&InventoryClass, "WidgetBlueprint'/Game/Widgets/Inventory/CBP_WInventory.CBP_WInventory_C'");
}


void UCWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<APlayerController>(OwnerPlayer->GetController());
	CheckNull(PlayerController);

	

	// Spawn Widget	
	MainWidget = Cast<UCWMain>(CreateWidget(PlayerController, MainWidgetClass));
	InventoryWidget = Cast<UCWInventory>(CreateWidget(PlayerController, InventoryClass));
	
	

	// 메인 위젯 켜기
	MainWidget->AddToViewport();
}

void UCWidgetComponent::SetViewInventory()
{
	if (!InventoryWidget->IsVisible())
	{
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);

		PlayerController->bShowMouseCursor = InventoryWidget->IsVisible();

		OwnerPlayer->GetStatComponent()->SetSpeedType(ESpeedType::Stop);

	}
	else
	{
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		FInputModeGameOnly InputMode;	
		PlayerController->SetInputMode(InputMode);

		PlayerController->bShowMouseCursor = InventoryWidget->IsVisible();

		OwnerPlayer->GetStatComponent()->SetSpeedType(ESpeedType::Walk);
	}
}


