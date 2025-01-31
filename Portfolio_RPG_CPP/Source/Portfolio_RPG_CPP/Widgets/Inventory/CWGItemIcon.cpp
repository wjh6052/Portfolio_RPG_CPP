#include "CWGItemIcon.h"

void UCWGItemIcon::UpdetaMaterialItemData(FMaterialItem_DataTable input)
{
	MaterialItemData = input;

	RatingColor = FItemRarityColor().GetRatingColor(MaterialItemData.StarRating);
	
	UpdetaIcon();
}