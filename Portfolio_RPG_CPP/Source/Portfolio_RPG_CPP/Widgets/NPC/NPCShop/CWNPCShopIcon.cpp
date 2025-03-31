#include "CWNPCShopIcon.h"
#include "../../../Datas/Data_DataTable.h"




FColor UCWNPCShopIcon::GetRatingColor()
{
	FItemRarityColor ratingColor;
	return ratingColor.GetRatingColor(ItemData.StarRating);
}