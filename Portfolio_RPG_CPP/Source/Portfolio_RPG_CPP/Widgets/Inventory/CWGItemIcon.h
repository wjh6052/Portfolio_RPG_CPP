#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Datas/Data_Inventory.h"
#include "CWGItemIcon.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCWGItemIcon : public UUserWidget
{
	GENERATED_BODY()
	
public: // 함수
	UFUNCTION(BlueprintCallable)
		void UpdetaMaterialItemData(FMaterialItem_DataTable input);



	// 블루프린트에서 재정의 할 함수
	UFUNCTION(BlueprintImplementableEvent) // 등급에 맞는 아이콘세팅
		void DetermineRating();

	UFUNCTION(BlueprintImplementableEvent) // 버튼에 마우스가 올라갔을때
		void ButtonHovered(bool OnHovered);

	UFUNCTION(BlueprintImplementableEvent) // 버튼을 클릭 했을대
		void ButtonClick();

	UFUNCTION(BlueprintImplementableEvent) // 아이콘 재설정
		void UpdetaIcon();
	



public: // 변수
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "UI Data")
		EItemCategory ItemCategory;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI Data")
		FMaterialItem_DataTable MaterialItemData;

	UPROPERTY(BlueprintReadWrite, Category = "UI Data")
		FColor RatingColor;

};
