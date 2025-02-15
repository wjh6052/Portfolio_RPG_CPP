#include "CWidgetComponent.h"
#include "../../../Global.h"
#include "../../../Character/Player/CCharacter_Player.h"
#include "../../../Widgets/CWMain.h"
#include "../../../Widgets/Inventory/CWInventory.h"

#include "GameFramework/PlayerController.h"


UCWidgetComponent::UCWidgetComponent()
{
	OwnerPlayer = Cast<ACCharacter_Player>(GetOwner());


	CHelpers::GetClass<UCWMain>(&MainWidgetClass, "WidgetBlueprint'/Game/Widgets/CWB_Main.CWB_Main_C'");
}


void UCWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<APlayerController>(OwnerPlayer->GetController());
	CheckNull(PlayerController);

	

	// Spawn Widget	
	MainWidget = Cast<UCWMain>(CreateWidget(PlayerController, MainWidgetClass));
	
	

	// 메인 위젯 켜기
	GetMainWidget()->AddToViewport();
	
}

void UCWidgetComponent::SetViewInventory()
{
	if (CurrentUi != ECurrentUi::Inventory)
	{
		BackCurrentUi = CurrentUi;
		CurrentUi = ECurrentUi::Inventory;


		GetMainWidget()->SetWidgetSwitcher(CurrentUi);
	}
	else
	{
		CurrentUi = BackCurrentUi;

		GetMainWidget()->SetWidgetSwitcher(CurrentUi);
	}
}


