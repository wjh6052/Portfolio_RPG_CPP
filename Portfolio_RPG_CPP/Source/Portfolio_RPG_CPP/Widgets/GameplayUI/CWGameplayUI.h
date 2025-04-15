#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Datas/Data_DataTable.h"
#include "CWGameplayUI.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCWGameplayUI : public UUserWidget
{
	GENERATED_BODY()

public:
	
	 


public: // ------------------------------------------------��ȣ�ۿ�------------------------------------------------

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
		void AddInteraction(AActor* InActor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
		void RemovalInteraction(AActor* InActor);
	
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintPure, Category = "Interaction")
		class UCWInteractionBox* GetWInteractionBox();
	
	
public: // ------------------------------------------------��ų������------------------------------------------------

	UFUNCTION(BlueprintImplementableEvent, Category = "SkillIconBox")
		void SetSkillCooldownTime(ECombatType InCombatType, int InSkillNum, float InCurrentCooldown);

	UFUNCTION(BlueprintImplementableEvent, Category = "SkillIconBox")
		void SetWidgetSwitcher(bool InOnCombat, ECombatType InCombatType);

	UFUNCTION(BlueprintImplementableEvent, Category = "SkillIconBox")
		void SetIconOpacity(bool InOffSkill, ECombatType InCombatType, int InSkillNum);


public: // ------------------------------------------------���� ���� â------------------------------------------------

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Choice")
		void OnWeaponWheel(bool IbOn);


public: // ------------------------------------------------���� ���� â------------------------------------------------

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Choice")
		void BeginHPBar(float InHP, float InMaxHp);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Choice")
		void SetHPBar(float InHP);


public: // ------------------------------------------------���� HPBar------------------------------------------------

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "BossHpBar")
		void OnBossHpBar(bool bOnHpBar, FBoss_DataTable InBoss_DataTable);

	UFUNCTION(BlueprintImplementableEvent, Category = "BossHpBar")
		void AddDamageBossHpBar(float InDamage);
};
