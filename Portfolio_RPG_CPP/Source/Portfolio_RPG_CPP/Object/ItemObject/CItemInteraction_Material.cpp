#include "CItemInteraction_Material.h"
#include "../../CGameInstance.h"

ACItemInteraction_Material::ACItemInteraction_Material()
{
	InteractionCategory = EInteractionCategory::Material;

}

void ACItemInteraction_Material::BeginPlay()
{
	Super::BeginPlay();


	UCGameInstance* cGameInstance = Cast<UCGameInstance>(GetGameInstance());

	if (cGameInstance)
	{
		for (int i = 0; i < cGameInstance->MaterialItemItmeData_Arr.Num(); i++)
		{
			if (cGameInstance->MaterialItemItmeData_Arr[i].StarRating == FInteractionItemMaterial.StarRating && 
				cGameInstance->MaterialItemItmeData_Arr[i].ItemUseType == FInteractionItemMaterial.ItemUseType)
			{
				InteractionImage = cGameInstance->MaterialItemItmeData_Arr[i].ItemImage;
			}
		}
	}
}