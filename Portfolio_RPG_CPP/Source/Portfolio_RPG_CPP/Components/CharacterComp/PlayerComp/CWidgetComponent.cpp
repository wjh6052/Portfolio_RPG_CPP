#include "CWidgetComponent.h"
#include "../../../Global.h"
#include "../../../Character/Player/CCharacter_Player.h"
#include "../../../Widgets/Inventory/CWInventory.h"

#include "GameFramework/PlayerController.h"


UCWidgetComponent::UCWidgetComponent()
{
	OwnerPlayer = Cast<ACCharacter_Player>(GetOwner());

	
	CHelpers::GetClass<UCWInventory>(&InventoryClass, "WidgetBlueprint'/Game/Widgets/Inventory/CBP_WInventory.CBP_WInventory_C'");
}


void UCWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<APlayerController>(OwnerPlayer->GetController());
	CheckNull(PlayerController);

	

	// Spawn Widget
	
	InventoryWidget = Cast<UCWInventory>(CreateWidget(PlayerController, InventoryClass));
	
	
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


