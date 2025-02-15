#include "CWNPCShopIcon.h"
#include "../../../Datas/Data_Inventory.h"




FColor UCWNPCShopIcon::GetRatingColor()
{
	FItemRarityColor ratingColor;
	return ratingColor.GetRatingColor(ItemData.StarRating);
}