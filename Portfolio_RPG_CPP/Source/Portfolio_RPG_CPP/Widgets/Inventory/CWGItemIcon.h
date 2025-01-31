#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Datas/Data_Inventory.h"
#include "CWGItemIcon.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWGItemIcon : public UUserWidget
{
	GENERATED_BODY()
	
public: // �Լ�
	UFUNCTION(BlueprintCallable)
		void UpdetaMaterialItemData(FMaterialItem_DataTable input);



	// �������Ʈ���� ������ �� �Լ�
	UFUNCTION(BlueprintImplementableEvent) // ��޿� �´� �����ܼ���
		void DetermineRating();

	UFUNCTION(BlueprintImplementableEvent) // ��ư�� ���콺�� �ö�����
		void ButtonHovered(bool OnHovered);

	UFUNCTION(BlueprintImplementableEvent) // ��ư�� Ŭ�� ������
		void ButtonClick();

	UFUNCTION(BlueprintImplementableEvent) // ������ �缳��
		void UpdetaIcon();
	



public: // ����
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UI Data")
		EItemCategory ItemCategory;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI Data")
		FMaterialItem_DataTable MaterialItemData;

	UPROPERTY(BlueprintReadWrite, Category = "UI Data")
		FColor RatingColor;

};
