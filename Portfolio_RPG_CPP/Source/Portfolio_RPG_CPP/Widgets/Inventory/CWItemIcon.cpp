#include "CWItemIcon.h"

void UCWItemIcon::UpdetaMaterialItemData(FMaterialItem_DataTable input)
{
	MaterialItemData = input;

	RatingColor = FItemRarityColor().GetRatingColor(MaterialItemData.StarRating);
	
	UpdetaIcon();
}

void UCWItemIcon::DetermineRating_Implementation()
{
	FItemRarityColor a;
	RatingColor = a.GetRatingColor(MaterialItemData.StarRating);
}

void UCWItemIcon::ButtonHovered_Implementation(bool OnHovered)
{
}

void UCWItemIcon::ButtonClick_Implementation()
{
}

void UCWItemIcon::UpdetaIcon_Implementation()
{
}

void UCWItemIcon::SetItemData_Implementation(FMaterialItem_DataTable InputData)
{
	MaterialItemData = InputData;

	UpdetaIcon();
}
