#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Datas/Data_Widget.h"
#include "CWGameplayUI.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCWGameplayUI : public UUserWidget
{
	GENERATED_BODY()

public:
	
	 


public: // ------------------------------------------------상호작용------------------------------------------------

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
		void AddInteraction(AActor* InActor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
		void RemovalInteraction(AActor* InActor);
	
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintPure, Category = "Interaction")
		class UCWInteractionBox* GetWInteractionBox();
	
	
public: // ------------------------------------------------스킬아이콘------------------------------------------------

	UFUNCTION(BlueprintImplementableEvent, Category = "SkillIconBox")
		void SetSkillCooldownTime(ECombatType InCombatType, int InSkillNum, float InCurrentCooldown);

	UFUNCTION(BlueprintImplementableEvent, Category = "SkillIconBox")
		void SetWidgetSwitcher(bool InOnCombat, ECombatType InCombatType);

	UFUNCTION(BlueprintImplementableEvent, Category = "SkillIconBox")
		void SetIconOpacity(bool InOffSkill, ECombatType InCombatType, int InSkillNum);


public: // ------------------------------------------------무기 선택 창------------------------------------------------

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Choice")
		void OnWeaponWheel(bool IbOn);

};
