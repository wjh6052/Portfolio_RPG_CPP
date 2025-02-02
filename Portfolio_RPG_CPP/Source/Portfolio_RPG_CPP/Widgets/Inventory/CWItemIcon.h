#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Datas/Data_Inventory.h"
#include "CWItemIcon.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWItemIcon : public UUserWidget
{
	GENERATED_BODY()
	
public: // 
	UFUNCTION(BlueprintCallable)
		void UpdetaMaterialItemData(FMaterialItem_DataTable input);



	// 등급별 색상 및 위젯의 별의 갯수를 조절
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DetermineRating();
	virtual void DetermineRating_Implementation();

	// 버튼에 마우스가 호버 됬을 때 호출
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ButtonHovered(bool OnHovered);
	virtual void ButtonHovered_Implementation(bool OnHovered);

	// 버튼이 클릭 됬을때
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ButtonClick();
	virtual void ButtonClick_Implementation();

	// 아이콘 위젯을 셋팅
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UpdetaIcon();
	virtual void UpdetaIcon_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SetItemData(FMaterialItem_DataTable InputData);
	virtual void SetItemData_Implementation(FMaterialItem_DataTable InputData);


public: // 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UI Data")
		EItemCategory ItemCategory;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI Data")
		FMaterialItem_DataTable MaterialItemData;

	UPROPERTY(BlueprintReadWrite, Category = "UI Data")
		FColor RatingColor;

};
