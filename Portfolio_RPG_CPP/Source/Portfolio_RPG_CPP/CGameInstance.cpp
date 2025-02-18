 #include "CGameInstance.h"
#include "Global.h"
#include "Sava/CItmeData_SaveGame.h"

#include "Kismet/GameplayStatics.h"


UCGameInstance::UCGameInstance()
{
	// 플레이어 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&Player_DataTable, "DataTable'/Game/Data/Player/DT_PlayerData.DT_PlayerData'");

	// 몬스터 데이터 테이블 추가예정
	//CHelpers::GetAsset<UDataTable>(&Enemy_DataTable, "DataTable'/Game/Data/DT_Enemy.DT_Enemy'");
	
	// 보스 데이터 테이블 추가예정
	

	//NPC 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&NPC_DataTable, "DataTable'/Game/Data/DT_NPC.DT_NPC'");
	

	// 아이템 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&MaterialItem_DataTable, "DataTable'/Game/Data/DT_MaterialItem.DT_MaterialItem'");
	

	// 무기 데이터
	CHelpers::GetAsset<UDataTable>(&CombatPlayer_DataTable, "DataTable'/Game/Data/Player/DT_Combat_Player.DT_Combat_Player'");


	// 위젯 대화 아이콘 배열
	CHelpers::GetAsset<UDataTable>(&ConversationIcon_DataTable, "DataTable'/Game/Data/Widget/DT_ConversationIcon.DT_ConversationIcon'");


	
}

void UCGameInstance::Init()
{
	Super::Init();

	PlayerDataTableToArr();
	//EnemyDataTableToArr();
	NPCDataTableToArr();
	IconDataTableToArr();
	CombatPlayerDataTableToArr();

	SaveData();
	//if (!LoadData())
	//{
	//	SaveData();
	//}
}


// ------------------------------------------------DataTable-------------------------------------------------------

void UCGameInstance::PlayerDataTableToArr()
{
	if (!Player_DataTable)
	{
		CLog::Print(L"Player 데이터테이블을 읽어오지 못하였습니다");
	}
	else
	{
		TArray<FPlayer_DataTable*> AllRows;
		Player_DataTable->GetAllRows<FPlayer_DataTable>(L"", AllRows);


		for (FPlayer_DataTable* Row : AllRows)
		{
			if (Row)
				Playe_Data_Arr.Add(*Row);
		}
	}
}

void UCGameInstance::EnemyDataTableToArr()
{
	if (!Enemy_DataTable)
	{
		CLog::Print(L"Enemy 데이터테이블을 읽어오지 못하였습니다");
	}
	else
	{
		TArray<FEnemy_DataTable*> AllRows;
		Enemy_DataTable->GetAllRows<FEnemy_DataTable>(L"", AllRows);


		for (FEnemy_DataTable* Row : AllRows)
		{
			if (Row)
				Enemy_Data_Arr.Add(*Row);
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

void UCGameInstance::CombatPlayerDataTableToArr()
{
	if (!CombatPlayer_DataTable)
	{
		CLog::Print(L"플레이어 무기 데이터테이블을 읽어오지 못하였습니다");
	}
	else
	{
		TArray<FCombatPlayer_DataTable*> AllRows;
		CombatPlayer_DataTable->GetAllRows<FCombatPlayer_DataTable>(L"", AllRows);


		for (FCombatPlayer_DataTable* Row : AllRows)
		{
			if (Row)
				CombatPlayerData_Arr.Add(*Row);
		}
	}
}

void UCGameInstance::IconDataTableToArr()
{
	if (!ConversationIcon_DataTable)
	{
		CLog::Print(L"아이템 데이터테이블을 읽어오지 못하였습니다");
	}
	else
	{
		TArray<FConversationIcon_DataTable*> AllRows;
		ConversationIcon_DataTable->GetAllRows<FConversationIcon_DataTable>(L"", AllRows);


		for (FConversationIcon_DataTable* Row : AllRows)
		{
			if (Row)
				ConversationIcon_Arr.Add(*Row);
		}
	}
}






// ----------------------------------------------------SaveGame-------------------------------------------------------

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
			TriggerUpdataMaterialItem();

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
		TriggerUpdataMoney();



		CLog::Print(FString::Printf(TEXT("%d머니 획득!"), AddMoney));
	}
	else
	{
		if (Money + AddMoney >= 0)
		{
			Money += AddMoney;
			TriggerUpdataMoney();


			CLog::Print(FString::Printf(TEXT("%d머니 소모"), AddMoney));
		}
	}
}



