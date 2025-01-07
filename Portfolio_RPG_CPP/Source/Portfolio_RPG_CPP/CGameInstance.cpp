#include "CGameInstance.h"
#include "Global.h"


UCGameInstance::UCGameInstance()
{
	CHelpers::GetAsset<UDataTable>(&Player_DataTable, "DataTable'/Game/Data/DT_PlayerData.DT_PlayerData'");

	// 몬스터와 보스 추가예정
}