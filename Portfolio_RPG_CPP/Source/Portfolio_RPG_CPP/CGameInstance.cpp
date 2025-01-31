 #include "CGameInstance.h"
#include "Global.h"
#include "Sava/CItmeData_SaveGame.h"

#include "Kismet/GameplayStatics.h"


UCGameInstance::UCGameInstance()
{
	CHelpers::GetAsset<UDataTable>(&Player_DataTable, "DataTable'/Game/Data/DT_PlayerData.DT_PlayerData'");

	// 몬스터와 보스 데이터 테이블 추가예정
	

	CHelpers::GetAsset<UDataTable>(&MaterialItem_DataTable, "DataTable'/Game/Data/DT_MaterialItem.DT_MaterialItem'");
	
}

void UCGameInstance::Init()
{
	Super::Init();

	LoadData();
	if (ItmeData_SaveGame == nullptr)
	{
		DataTableToMaterialItemData();
		//SaveData();

	}
}




void UCGameInstance::DataTableToMaterialItemData()
{
	CheckNull(MaterialItem_DataTable);

	//TArray<FName> rowNames = MaterialItem_DataTable->GetRowNames();
	//CheckTrue(rowNames.Num() < 0);

	TArray<FMaterialItem_DataTable*> AllRows;
	MaterialItem_DataTable->GetAllRows<FMaterialItem_DataTable>(L"", AllRows);

	for (FMaterialItem_DataTable* Row : AllRows)
	{
		if (Row)
		{
			MaterialItemItmeData_Arr.Add(*Row);
		}
	}
	
}

void UCGameInstance::AddMaterialItem(EItemUseType ItemUseType, EStarRating ItemRating, int AddCount)
{
}



void UCGameInstance::SaveData(int Index)
{
	if (ItmeData_SaveGame != nullptr)
	{
		ItmeData_SaveGame = Cast<UCItmeData_SaveGame>(UGameplayStatics::CreateSaveGameObject(UCItmeData_SaveGame::StaticClass()));
	}

	ItmeData_SaveGame->Save_MaterialItemItmeData_Arr = MaterialItemItmeData_Arr;


	bool a = UGameplayStatics::SaveGameToSlot(ItmeData_SaveGame, TEXT("SaveData"), Index);
	if (a)
	{
		CLog::Print("세이브를 성공했습니다");
	}
	else
	{
		CLog::Print("세이브를 실패했습니다");
	}   
	
}

void UCGameInstance::LoadData(int Index)
{


	UCItmeData_SaveGame* LoadedGame = Cast<UCItmeData_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveData"), Index));


	if (LoadedGame)
	{
		ItmeData_SaveGame = LoadedGame;
		MaterialItemItmeData_Arr = ItmeData_SaveGame->Save_MaterialItemItmeData_Arr;

		CLog::Print("로드를 성공했습니다");
	}
	else
	{
		CLog::Print("로드를 실패했습니다");
		CLog::Log("로드를 실패했습니다");
		CLog::Print("1244444444");
	}

	
}



void UCGameInstance::DeleteData(int Index)
{
}
