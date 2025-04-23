// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CInteraction.h"
#include "CItemInteraction_Material.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_RPG_CPP_API ACItemInteraction_Material : public ACInteraction
{
	GENERATED_BODY()

public:
	ACItemInteraction_Material();

	UFUNCTION(BlueprintCallable)
		void SetMaterialItemIcon();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		FInteractionItemMaterial FInteractionItemMaterial;
};
