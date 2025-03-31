#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Datas/Data_DataTable.h"
#include "CWNPCTalkUI.generated.h"

UENUM(BlueprintType)
enum class ENPCTalkUI : uint8
{
	NPCDialogue = 0  UMETA(DisplayName = "NPC 대화"),
	Shop = 1		 UMETA(DisplayName = "상점"),
	Enhancement = 2	 UMETA(DisplayName = "강화"),
	QuestLog = 3	 UMETA(DisplayName = "퀘스트창"),
	TalkEnd = 4	 UMETA(DisplayName = "대화종료")
};


UCLASS()
class PORTFOLIO_RPG_CPP_API UCWNPCTalkUI : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetNPCTalkUI(class ACInteraction_NPC* InNPCData);


	UPROPERTY(BlueprintReadWrite)
		ENPCTalkUI NPCTalkUI;
};
