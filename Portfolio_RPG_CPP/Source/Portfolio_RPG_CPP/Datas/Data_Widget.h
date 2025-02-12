#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Data_Widget.generated.h"


//---------------------------Enum---------------------------------------------

UENUM(BlueprintType)
enum class EConversationType : uint8 // NPC종류 열거형
{
	None			UMETA(DisplayName = "비어있음"),
	Dialogue		UMETA(DisplayName = "대화"),
	Shop			UMETA(DisplayName = "퀘스트"),
	Blacksmith		UMETA(DisplayName = "상점"),
	Quest         	UMETA(DisplayName = "대장장이")
};





//---------------------------struct---------------------------------------------





//---------------------------DataTable---------------------------------------------


USTRUCT(BlueprintType)
struct FConversationIcon_DataTable : public FTableRowBase // NPC선택지에 나오는 아이콘 데이터테이블
{
	GENERATED_BODY()

public:
	// 이미지의 타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Type")
		EConversationType ConversationType; 

	// 위젯에 표시될 이미지
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Image")
		UTexture2D* ConversationImage; 
};















UCLASS()
class PORTFOLIO_RPG_CPP_API UData_Widget : public UObject
{
	GENERATED_BODY()
	
};
