#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_DamageText.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UDA_DamageText : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// 텍스트를 출력할 나이아가라 시스템
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NiagaraSystem")
		class UNiagaraSystem* NiagaraSystem;

	// 나이아가라 시스템에 숫자가 붙을 오버라이드 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NiagaraSystem")
		FString OverrideName;

	// 나이아가라 시스템에 숫자의 색상 파라미터 이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NiagaraSystem")
		FName ColorParameterName;



	// 일반 데미지 색상
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Color")
		FLinearColor NormalColor;
	// 크리티컬 데미지 색상
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Color")
		FLinearColor CriticalColor;
	// 힐 색상
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Color")
		FLinearColor HealingColor;



	// 텍스쳐 0~9
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Texture")
		TArray<UTexture*> Textures;
	
	UDA_DamageText()
	{
		Textures.SetNum(10);
	}
	
};
