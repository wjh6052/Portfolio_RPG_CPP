 #include "CGameInstance.h"
#include "Global.h"
#include "Sava/CItmeData_SaveGame.h"

#include "Kismet/GameplayStatics.h"


UCGameInstance::UCGameInstance()
{
	// 플레이어 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&Player_DataTable, "DataTable'/Game/Data/DT_PlayerData.DT_PlayerData'");

	// 몬스터와 보스 데이터 테이블 추가예정
	
	// 아이템 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&MaterialItem_DataTable, "DataTable'/Game/Data/DT_MaterialItem.DT_MaterialItem'");
	
}

void UCGameInstance::Init()
{
	Super::Init();

	DataTableToMaterialItemData();
	//LoadData();
	//if (ItmeData_SaveGame == nullptr)
	//{		
	//	SaveData();
	//
	//}
}




void UCGameInstance::DataTableToMaterialItemData()
{
	if (!MaterialItem_DataTable)
	{
		CLog::Print(L"아이템 데이터테이블을 읽어오지 못하였습니다");
		return;
	}


	TArray<FMaterialItem_DataTable*> AllRows;
	MaterialItem_DataTable->GetAllRows<FMaterialItem_DataTable>(L"", AllRows);


	for (FMaterialItem_DataTable* Row : AllRows)
	{
		if(Row)
			MaterialItemItmeData_Arr.Add(*Row);
	}
	
	
}

void UCGameInstance::AddMaterialItem(EItemUseType ItemUseType, EStarRating ItemRating, int AddCount)
{
}



void UCGameInstance::SaveData(int Index)
{
	if (ItmeData_SaveGame == nullptr)
	{
		ItmeData_SaveGame = Cast<UCItmeData_SaveGame>(UGameplayStatics::CreateSaveGameObject(UCItmeData_SaveGame::StaticClass()));
	}

	ItmeData_SaveGame->Save_MaterialItemItmeData_Arr = MaterialItemItmeData_Arr;
	ItmeData_SaveGame->Money = Money;

	if (UGameplayStatics::SaveGameToSlot(ItmeData_SaveGame, TEXT("SaveData"), Index))
	{
		CLog::Print(L"세이브를 성공했습니다");
	}
	else
	{
		CLog::Print(L"세이브를 실패했습니다");
	}   
	
}

void UCGameInstance::LoadData(int Index)
{


	UCItmeData_SaveGame* LoadedGame = Cast<UCItmeData_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveData"), Index));


	if (LoadedGame)
	{
		ItmeData_SaveGame = LoadedGame;
		MaterialItemItmeData_Arr = ItmeData_SaveGame->Save_MaterialItemItmeData_Arr;
		Money = ItmeData_SaveGame->Money;

		CLog::Print(L"로드를 성공했습니다");
	}
	else
	{
		CLog::Print(L"로드를 실패했습니다");
	}

	
}



void UCGameInstance::DeleteData(int Index)
{
}

void UCGameInstance::TriggerUpdateMoney(int InMoney)
{
	Money += InMoney;

	Update_Money.Broadcast(Money);
}
