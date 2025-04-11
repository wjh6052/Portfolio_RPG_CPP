 #include "CGameInstance.h"
#include "Global.h"
#include "Sava/CItmeData_SaveGame.h"
#include "Datas/DA/DA_DamageText.h"
#include "Datas/DA/DA_MapIcon.h"
#include "Character/Player/CCharacter_Player.h"


#include "Kismet/GameplayStatics.h"


UCGameInstance::UCGameInstance()
{
	// 플레이어 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&Player_DataTable, "DataTable'/Game/Data/Player/DT_PlayerData.DT_PlayerData'");

	// 몬스터 데이터 테이블 추가예정
	CHelpers::GetAsset<UDataTable>(&Enemy_DataTable, "DataTable'/Game/Data/DT_Enemy.DT_Enemy'");
	
	// 보스 데이터 테이블 추가예정
	

	//NPC 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&NPC_DataTable, "DataTable'/Game/Data/NPC/DT_NPC.DT_NPC'");
	

	// 퀘스트 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&Quest_DataTable, "DataTable'/Game/Data/NPC/DT_Quest.DT_Quest'");


	// 아이템 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&MaterialItem_DataTable, "DataTable'/Game/Data/DT_MaterialItem.DT_MaterialItem'");
	



	// 위젯 대화 아이콘 배열
	CHelpers::GetAsset<UDataTable>(&ConversationIcon_DataTable, "DataTable'/Game/Data/Widget/DT_ConversationIcon.DT_ConversationIcon'");


	// 강화 조건 데이터 배열
	CHelpers::GetAsset<UDataTable>(&GearEnhancementData_DataTable, "DataTable'/Game/Data/DT_FGearEnhancementData.DT_FGearEnhancementData'");


	// 데미지 텍스트
	CHelpers::GetAsset<UDA_DamageText>(&DamageText_DA, "DA_DamageText'/Game/Data/DA/DA_DamageText.DA_DamageText'");

	// 맵 아이콘 데이터 에셋
	CHelpers::GetAsset<UDA_MapIcon>(&MapIcon_DA, "DA_MapIcon'/Game/Data/DA/DA_MapIcon.DA_MapIcon'");
}

void UCGameInstance::Init()
{
	Super::Init();

	// 아이콘 데이터 업로드
	IconDataTableToArr();

	// 강화 데이터 업로드
	GearEnhancementDataTableToArr();

	// 퀘스트
	QuestDataTableToArr();

	PlayerDataTableToArr();
	EnemyDataTableToArr();
	NPCDataTableToArr();
	
	

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
			{
				Player_Data_Arr.Add(*Row);
			}
		}
	}
}

void UCGameInstance::UpdatePlayerData(ECombatType InCombatType, FPlayer_DataTable InPlayerData)
{
	for (int32 i = 0; i < Player_Data_Arr.Num(); i++)
	{
		if (Player_Data_Arr[i].Player_CombatData.CombatData.CombatType == InCombatType)
		{
			Player_Data_Arr[i] = InPlayerData;
			TriggerUpdatePlayerData(InCombatType);
			break;
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

void UCGameInstance::QuestDataTableToArr()
{
	if (!Quest_DataTable)
	{
		CLog::Print(L"퀘스트 데이터테이블을 읽어오지 못하였습니다");
	}
	else
	{
		TArray<FQuest_DataTable*> AllRows;
		Quest_DataTable->GetAllRows<FQuest_DataTable>(L"", AllRows);


		for (FQuest_DataTable* Row : AllRows)
		{
			if (Row)
				QuestData_Arr.Add(*Row);
		}
	}
}

void UCGameInstance::UpdateQuestDate(FQuest_DataTable Input, EQuestDetailsUpdateType QuestDetailsUpdateType, FString InName)
{
	for (int i = 0; i < QuestData_Arr.Num(); i++)
	{
		if(Input.QuestID == QuestData_Arr[i].QuestID)
		{
			QuestData_Arr[i] = Input;
			TriggerUpdateQuest(Input, QuestDetailsUpdateType, InName);
			return;
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


void UCGameInstance::IconDataTableToArr()
{
	if (!ConversationIcon_DataTable)
	{
		CLog::Print(L"아이콘 데이터테이블을 읽어오지 못하였습니다");
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



void UCGameInstance::GearEnhancementDataTableToArr()
{
	if (!GearEnhancementData_DataTable)
	{
		CLog::Print(L"장비 강화 데이터테이블을 읽어오지 못하였습니다");
	}
	else
	{
		TArray<FGearEnhancementData_DataTable*> AllRows;
		GearEnhancementData_DataTable->GetAllRows<FGearEnhancementData_DataTable>(L"", AllRows);


		for (FGearEnhancementData_DataTable* Row : AllRows)
		{
			if (Row)
				GearEnhancementData_Arr.Add(*Row);
		}
	}
}

FGearEnhancementData_DataTable UCGameInstance::GetGearEnhancementData(EGearType InGearType, ECombatType InCombatType)
{
	FGearEnhancementData_DataTable reData;

	for (FGearEnhancementData_DataTable data : GearEnhancementData_Arr)
	{
		if (data.GearType == InGearType && data.WeaponType == InCombatType)
		{
			reData = data;
			break;
		}
	}


	return reData;
}

FColor UCGameInstance::GetRatingColor(EStarRating InRating)
{
	switch (InRating)
	{
	case EStarRating::OneStar:
		return RatingColor.OneStarColor;

	case EStarRating::TwoStar:
		return RatingColor.TwoStarColor;

	case EStarRating::ThreeStar:
		return RatingColor.ThreeStarColor;

	case EStarRating::Fourstar:
		return RatingColor.FourstarColor;

	case EStarRating::Fivestar:
		return RatingColor.FivestarColor;

	}

		//RatingColor
	return FColor();
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


		// 전체 퀘스트 진행도 추가 예정
		QuestData_Arr.Empty();

		// 현제 플레이어의 퀘스트 정보


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
			if (AddCount > 0)
			{
				MaterialItemItmeData_Arr[i].ItemCount += AddCount;
				TriggerUpdataMaterialItem(ItemUseType, ItemRating, AddCount);

				UEnum* enumUseType = StaticEnum<EItemUseType>();
				FString eUseType = enumUseType->GetDisplayNameTextByIndex(static_cast<int64>(ItemUseType)).ToString();
				UEnum* EnumRating = StaticEnum<EStarRating>();
				FString eStarRating = EnumRating->GetDisplayNameTextByIndex(static_cast<int64>(ItemRating)).ToString();


				//CLog::Print(FString::Printf(TEXT(" %s / %s / %d개 획득"), *eUseType, *eStarRating, AddCount));
			}
			else if (AddCount < 0)
			{
				MaterialItemItmeData_Arr[i].ItemCount += AddCount;
				TriggerUpdataMaterialItem(ItemUseType, ItemRating, AddCount);

				UEnum* enumUseType = StaticEnum<EItemUseType>();
				FString eUseType = enumUseType->GetDisplayNameTextByIndex(static_cast<int64>(ItemUseType)).ToString();
				UEnum* EnumRating = StaticEnum<EStarRating>();
				FString eStarRating = EnumRating->GetDisplayNameTextByIndex(static_cast<int64>(ItemRating)).ToString();


				//CLog::Print(FString::Printf(TEXT(" %s / %s / %d개 소모"), *eUseType, *eStarRating, AddCount));
			}			


			// 변경된 아이템이 퀘스트 관련 아이템인지 확인
			for (int q = 0; q < QuestData_Arr.Num(); q++)
			{
				if (QuestData_Arr[q].QuestDetails.bRequireItemCollection == true)
				{
					for (int j = 0; j < QuestData_Arr[q].QuestDetails.RequiredItems.Num(); j++)
					{
						if (QuestData_Arr[q].QuestDetails.RequiredItems[j].ItemUseType == ItemUseType && QuestData_Arr[q].QuestDetails.RequiredItems[j].StarRating == ItemRating && QuestData_Arr[q].QuestState == EQuestState::InProgress)
						{
							UpdateQuestDate(QuestData_Arr[q], EQuestDetailsUpdateType::Itme, MaterialItemItmeData_Arr[i].ItemName);
						}
					}
					
				}
			}
			
			//
			//UpdateQuestDate
			return;
		}
	}
}

void UCGameInstance::AddMoney(int AddMoney)
{
	if (AddMoney > 0)
	{
		Money += AddMoney;
		TriggerUpdataMoney(AddMoney);



		//CLog::Print(FString::Printf(TEXT("%d머니 획득!"), AddMoney));
	}
	else if (AddMoney < 0)
	{
		Money += AddMoney;
		TriggerUpdataMoney(AddMoney);
		//CLog::Print(FString::Printf(TEXT("%d머니 소모"), AddMoney));
	}
}

ACCharacter_Player* UCGameInstance::GetPlayerCharacter()
{
	ACCharacter_Player* playerCharacter = Cast<ACCharacter_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());

	return playerCharacter;
}



