 #include "CGameInstance.h"
#include "Global.h"
#include "Sava/CItmeData_SaveGame.h"

#include "Kismet/GameplayStatics.h"


UCGameInstance::UCGameInstance()
{
	// 플레이어 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&Player_DataTable, "DataTable'/Game/Data/DT_PlayerData.DT_PlayerData'");

	// 몬스터와 보스 데이터 테이블 추가예정

	
	//NPC 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&NPC_DataTable, "DataTable'/Game/Data/DT_NPC.DT_NPC'");
	


	// 아이템 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&MaterialItem_DataTable, "DataTable'/Game/Data/DT_MaterialItem.DT_MaterialItem'");
	
}

void UCGameInstance::Init()
{
	Super::Init();

	NPCDataTableToArr();

	if (!LoadData())
	{
		SaveData();
	}
}




void UCGameInstance::ItemDataTableToArr()
{
	if (!MaterialItem_DataTable)
	{
		CLog::Print(L"아이템 데이터테이블을 읽어오지 못하였습니다");
	}
	else
	{
		TArray<FMaterialItem_DataTable*> AllRows;
		MaterialItem_DataTable->GetAllRows<FMaterialItem_DataTable>(L"", AllRows);


		for (FMaterialItem_DataTable* Row : AllRows)
		{
			if (Row)
				MaterialItemItmeData_Arr.Add(*Row);
		}
	}	
	
}

void UCGameInstance::NPCDataTableToArr()
{
	if (!NPC_DataTable)
	{
		CLog::Print(L"NPC 데이터테이블을 읽어오지 못하였습니다");
	}
	else
	{
		TArray<FNPC_DataTable*> AllRows;
		NPC_DataTable->GetAllRows<FNPC_DataTable>(L"", AllRows);


		for (FNPC_DataTable* Row : AllRows)
		{
			if (Row)
				NPCData_Arr.Add(*Row);
		}
	}
}



void UCGameInstance::SaveData(FString SlotName, int Index)
{
	if (!ItmeData_SaveGame)
	{
		ItmeData_SaveGame = Cast<UCItmeData_SaveGame>(UGameplayStatics::CreateSaveGameObject(UCItmeData_SaveGame::StaticClass()));
	}


	if (ItmeData_SaveGame) //데이터 저장
	{
		// 세이브 게임의 기존 값 삭제
		ItmeData_SaveGame->Save_MaterialItemItmeData_Arr.Empty();


		// 데이터 테이블에서 기본값 불러오기
		ItemDataTableToArr();

		// 데이터 저장
		ItmeData_SaveGame->Save_MaterialItemItmeData_Arr = MaterialItemItmeData_Arr;
		ItmeData_SaveGame->Save_Money = Money;


		UGameplayStatics::SaveGameToSlot(ItmeData_SaveGame, SlotName, Index);
	}

	
	if (UGameplayStatics::DoesSaveGameExist(SlotName, Index))
	{
		CLog::Print(L"세이브를 성공했습니다");		
	}
	else
	{
		CLog::Print(L"세이브를 실패했습니다");
	}
	
}

bool UCGameInstance::LoadData(FString SlotName, int Index)
{


	UCItmeData_SaveGame* loadData = Cast<UCItmeData_SaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, Index));





	if (loadData)
	{
		ItmeData_SaveGame = loadData;
		
		// 기존의 값 삭제
		MaterialItemItmeData_Arr.Empty();

		// 아이템데이터 저장
		MaterialItemItmeData_Arr = ItmeData_SaveGame->Save_MaterialItemItmeData_Arr;
		Money = ItmeData_SaveGame->Save_Money;


		CLog::Print(L"로드를 성공했습니다");	
		return true;
	}
	else
	{
		CLog::Print(L"로드를 실패했습니다");
		return false;
	}

	
}

void UCGameInstance::DeleteData(FString SlotName, int Index)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, Index))
	{
		// 데이터 삭제
		UGameplayStatics::DeleteGameInSlot(SlotName, Index);
		if (UGameplayStatics::DoesSaveGameExist(SlotName, Index))
		{
			CLog::Print(L"데이터 제거를 성공했습니다");
		}
		else
		{
			CLog::Print(L"데이터 제거를 실패했습니다");
		}
	}
	else
	{
		CLog::Print(L"제거할 데이터를 찾지 못 하였습니다");
	}
}


void UCGameInstance::AddMaterialItem(EItemUseType ItemUseType, EStarRating ItemRating, int AddCount)
{
	for (int i = 0; i < MaterialItemItmeData_Arr.Num(); i++)
	{
		if (MaterialItemItmeData_Arr[i].ItemUseType == ItemUseType && MaterialItemItmeData_Arr[i].StarRating == ItemRating)
		{
			MaterialItemItmeData_Arr[i].ItemCount += AddCount;
			TriggerUpdateMaterialItem();

			UEnum* enumUseType = StaticEnum<EItemUseType>();
			FString eUseType = enumUseType->GetDisplayNameTextByIndex(static_cast<int64>(ItemUseType)).ToString();
			UEnum* EnumRating = StaticEnum<EStarRating>();
			FString eStarRating = EnumRating->GetDisplayNameTextByIndex(static_cast<int64>(ItemRating)).ToString();
			

			CLog::Print(FString::Printf(TEXT(" %s / %s / %d개 획득"), *eUseType, *eStarRating, AddCount));
			return;
		}
	}
}

void UCGameInstance::AddMoney(int AddMoney)
{
	if (AddMoney >= 0)
	{
		Money += AddMoney;
		TriggerUpdateMoney();



		CLog::Print(FString::Printf(TEXT("%d머니 획득!"), AddMoney));
	}
	else
	{
		if (Money + AddMoney <= 0)
		{
			Money += AddMoney;
			TriggerUpdateMoney();


			CLog::Print(FString::Printf(TEXT("%d머니 소모"), AddMoney));
		}
	}
}

