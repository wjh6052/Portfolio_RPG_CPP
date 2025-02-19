#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_DamageText.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UDA_DamageText : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// �ؽ�Ʈ�� ����� ���̾ư��� �ý���
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NiagaraSystem")
		class UNiagaraSystem* NiagaraSystem;

	// ���̾ư��� �ý��ۿ� ���ڰ� ���� �������̵� �̸�
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NiagaraSystem")
		FString OverrideName;

	// ���̾ư��� �ý��ۿ� ������ ���� �Ķ���� �̸�
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NiagaraSystem")
		FName ColorParameterName;



	// �Ϲ� ������ ����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Color")
		FLinearColor NormalColor;
	// ũ��Ƽ�� ������ ����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Color")
		FLinearColor CriticalColor;
	// �� ����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Color")
		FLinearColor HealingColor;



	// �ؽ��� 0~9
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Texture")
		TArray<UTexture*> Textures;
	
	UDA_DamageText()
	{
		Textures.SetNum(10);
	}
	
};
