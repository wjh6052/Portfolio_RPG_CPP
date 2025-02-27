#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Data_Character.h"
#include "Data_Widget.h"
#include "Data_NPC.generated.h"




//---------------------------Enum---------------------------------------------

UENUM(BlueprintType)
enum class ENPCType : uint8 // NPC종류 열거형
{
	None			UMETA(DisplayName = "비어있음"),
	Common			UMETA(DisplayName = "일반 NPC"),
	Merchant		UMETA(DisplayName = "상인"),
	Blacksmith 		UMETA(DisplayName = "대장장이")

};


UENUM(BlueprintType)
enum class ENPCName : uint8 // NPC이름 열거형
{
	None		UMETA(DisplayName = "비어있음"),
	Aventurine  UMETA(DisplayName = "어벤츄린"),
	Citlali		UMETA(DisplayName = "시틀라리"),
	Navia 		UMETA(DisplayName = "나비아")

};


//---------------------------struct---------------------------------------------


USTRUCT(BlueprintType)
struct FConversation // NPC대화의 내용과 선택지id를 설정하는 구조체
{
	GENERATED_BODY()

public:
	// 선택지 Id
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Id")
		int ConversationId;

	// 선택지 ID 목록 (선택지가 없으면 비움)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Id")
		TArray<int32> NextChoices;


	// 대화 선택지의 타입
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Choice")
		EConversationType ChoiceType;


	// 위젯에서나올 선택지이름
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Choice")
		FText ChoiceName;




	// 선택지를 선택했을때 나올 대화
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dialogue")
		TArray<FText> ConversationTextArr;
};


//---------------------------DataTable---------------------------------------------

USTRUCT(BlueprintType)
struct FNPC_DataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPCType")
		ENPCType NPCType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPCType")
		ENPCName NPCName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPCType")
		FText NPCTitle;


	// 말을 걸었을때 처음 나올 대화
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Conversation")
		FText FirstConversationText;
	
	// 대화를 시작해서 나오는 내용을 담은 FConversation
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Conversation")
		TArray<FConversation> ConversationArr;

};





UCLASS()
class PORTFOLIO_RPG_CPP_API UData_NPC : public UObject
{
	GENERATED_BODY()
	
};
