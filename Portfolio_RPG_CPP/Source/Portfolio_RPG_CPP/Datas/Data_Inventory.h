#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data_Inventory.generated.h"




//---------------------------Enum---------------------------------------------

UENUM(BlueprintType)
enum class EStarRating : uint8 // ��� ����
{
	None,		// �������
	OneStar,	// 1��
	TwoStar,	// 2��
	ThreeStar,	// 3��
	Fourstar,	// 4��
	Fivestar,	// 5��
};


UENUM(BlueprintType)
enum class EItemCategory : uint8 // ������ ī�װ� ����
{
	None,		// �������		
	Material,	// ��� ������	
	Potion,		// ����			
	Equipment,	// ���			
	Weapon		// ����			
};


UENUM(BlueprintType)
enum class EItemUseType : uint8 // �������� ���ó
{
	None,				// �������			
	PotionCraft,		// �������� ���		
	EquipmentUpgrade,	// ��� ��ȭ ���		
	DaggerUpgrade,		// �ܰ� ��ȭ ���		
	BowUpgrade,			// Ȱ ��ȭ ���		
	StaffUpgrade		// ������ ��ȭ ���	
};


//---------------------------struct---------------------------------------------

USTRUCT(BlueprintType)
struct FItemRarityColor // ��޺� ���� ����ü
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor OneStarColor = FColor(255,255,255,255); // ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor TwoStarColor = FColor(60, 121, 125, 255); // �ʷϻ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor ThreeStarColor = FColor(70, 116, 178, 255); // �Ķ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor FourstarColor = FColor(152, 103, 208, 255); // �����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemRarityColor")
		FColor FivestarColor = FColor(197, 162, 113, 255); // �����

};





//---------------------------DataTable---------------------------------------------


USTRUCT(BlueprintType)
struct FMaterialItem_DataTable : public FTableRowBase // �������� ���������̺�
{
	GENERATED_BODY()

public:


	// =====Category=====
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Category")
		EItemCategory ItemCategory; // ������ ī�װ� ����

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Category")
		EItemUseType ItemUseType; // �������� ���ó


	// =====Description=====
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		EStarRating StarRating; //��� ����
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		FString ItmeName; // ������ �̸�

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		int ItemCount = 0; // ������ ����

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		int ItmePrice = 0; // ������ ����
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		UTexture2D* ItmeImage; // ������ ǥ�õ� �̹���
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		FString ItemSimpleDescription; // ������ ���� ����

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Description")
		FString ItemDescription; // ������ ����
	
	
	// �ΰ��ӿ��� ���忡�� ǥ�õ� �������Ʈ ������Ʈ �߰� ����
};




// FPotionItem ���� ������ ���̺� �߰� ����

// FEquipmentItem ��� ������ ���̺� �߰� ����

// FWeaponItem ���� ������ ���̺� �߰� ����











UCLASS()
class PORTFOLIO_RPG_CPP_API UData_Inventory : public UObject
{
	GENERATED_BODY()
	
};
