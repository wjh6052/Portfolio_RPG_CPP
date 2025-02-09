#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data_Character.h"
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


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		FMesh Mesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		class USkeletalMesh* MeshOutLineMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
		class UClass* MannequinAnimInstance;

	
};





UCLASS()
class PORTFOLIO_RPG_CPP_API UData_NPC : public UObject
{
	GENERATED_BODY()
	
};
