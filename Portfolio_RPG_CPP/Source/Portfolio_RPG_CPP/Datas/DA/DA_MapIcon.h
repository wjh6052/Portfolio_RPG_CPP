#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_MapIcon.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UDA_MapIcon : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// Enemy
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Enemy")
		class UPaperSprite* Enemy_Sprite;


	// Boss
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Boss")
		class UPaperSprite* Boss_Sprite;


	// �Ϲ� NPC
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPC_Normal")
		class UPaperSprite* NPC_Normal_Sprite;


	// ���� NPC
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPC_Shop")
		class UPaperSprite* NPC_Shop_Sprite;


	// �������� NPC
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPC_Blacksmith")
		class UPaperSprite* NPC_Blacksmith_Sprite;


	// ��������Ʈ
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Warp_Point")
		class UPaperSprite* Warp_Point_Sprite;


	// �÷��̾�
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player")
		class UPaperSprite* Player_Sprite;

};
