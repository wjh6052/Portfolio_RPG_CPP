 #include "CGameInstance.h"
#include "Global.h"
#include "Sava/CSaveGame.h"
#include "Datas/DA/DA_DamageText.h"
#include "Datas/DA/DA_MapIcon.h"
#include "Datas/DA/DA_AttackRangeDecal.h"
#include "Character/Player/CCharacter_Player.h"


#include "Kismet/GameplayStatics.h"


UCGameInstance::UCGameInstance()
{
	// 플레이어 데이터 테이블
	CHelpers::GetAsset<UDataTable>(&Player_DataTable, "DataTable'/Game/Data/Player/DT_PlayerData.DT_PlayerData'");

	// 몬스터 데이터 테이블 추가예정
	CHelpers::GetAsset<UDataTable>(&Enemy_DataTable, "DataTable'/Game/Data/DT_Enemy.DT_Enemy'");
	
	// 보스 데이터 테이블 추가예정
	CHelpers::GetAsset<UDataTable>(&Boss_DataTable, "DataTable'/Game/Data/DT_Boss.DT_Boss'");



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


	// 몬스터의 범위 공격에 표시될 데칼 머티리얼
	CHelpers::GetAsset<UDA_AttackRangeDecal>(&AttackRangeDecal_DA, "DA_MapIcon'/Game/Data/DA/DA_AttackRangeDecal.DA_AttackRangeDecal'");
	
}

void UCGameInstance::Init()
{
	Super::Init();

	// 아이콘 데이터 업로드
	IconDataTableToArr();


	// 데이터 테이블에서 기본값 불러오기
	ItemDataTableToArr();


	// 강화 데이터 업로드
	GearEnhancementDataTableToArr();

	// 퀘스트
	QuestDataTableToArr();

	PlayerDataTableToArr();
	EnemyDataTableToArr();
	BossDataTableToArr();
	NPCDataTableToArr();
	
	
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
				SettingPlayerDataStats(Row->Player_CombatData.CombatData.CombatType);
			}
		}
	}
}

void UCGameInstance::SettingPlayerDataStats(ECombatType InCombatType)
{
	for (int i = 0; i < Player_Data_Arr.Num(); i++)
		if (Player_Data_Arr[i].Player_CombatData.CombatData.CombatType == InCombatType)
		{
			
			// 캐릭터의 기본스텟 적용
			Player_Data_Arr[i].Stat = Player_Data_Arr[i].Character_BaseStat;
			

			// 무기 스텟 추가
			{
				FGearStets tmep = GetGearStets(EGearType::Weapon, InCombatType, Player_Data_Arr[i].Player_CombatData.WeaponEnhancementLevel);

				Player_Data_Arr[i].Stat.HP_Max += tmep.HP_Max;
				Player_Data_Arr[i].Stat.Damage += tmep.Damage;
				Player_Data_Arr[i].Stat.Defense += tmep.Defense;
				Player_Data_Arr[i].Stat.Critical_Damage += tmep.Critical_Damage;
				Player_Data_Arr[i].Stat.Critical_Chance += tmep.Critical_Chance;
				Player_Data_Arr[i].Stat.Stance += tmep.Stance;
			}
			

			// 모자 스텟 추가
			{
				FGearStets tmep = GetGearStets(EGearType::Helmet, InCombatType, Player_Data_Arr[i].Gear_Helmet.GearEnhancementLevel);

				Player_Data_Arr[i].Stat.HP_Max += tmep.HP_Max;
				Player_Data_Arr[i].Stat.Damage += tmep.Damage;
				Player_Data_Arr[i].Stat.Defense += tmep.Defense;
				Player_Data_Arr[i].Stat.Critical_Damage += tmep.Critical_Damage;
				Player_Data_Arr[i].Stat.Critical_Chance += tmep.Critical_Chance;
				Player_Data_Arr[i].Stat.Stance += tmep.Stance;

				
			}
			

			// 상의 스텟 추가
			{
				FGearStets tmep = GetGearStets(EGearType::Armor, InCombatType, Player_Data_Arr[i].Gear_Armor.GearEnhancementLevel);

				Player_Data_Arr[i].Stat.HP_Max += tmep.HP_Max;
				Player_Data_Arr[i].Stat.Damage += tmep.Damage;
				Player_Data_Arr[i].Stat.Defense += tmep.Defense;
				Player_Data_Arr[i].Stat.Critical_Damage += tmep.Critical_Damage;
				Player_Data_Arr[i].Stat.Critical_Chance += tmep.Critical_Chance;
				Player_Data_Arr[i].Stat.Stance += tmep.Stance;
			}
			

			// 장갑 스텟 추가
			{
				FGearStets tmep = GetGearStets(EGearType::Gloves, InCombatType, Player_Data_Arr[i].Gear_Gloves.GearEnhancementLevel);

				Player_Data_Arr[i].Stat.HP_Max += tmep.HP_Max;
				Player_Data_Arr[i].Stat.Damage += tmep.Damage;
				Player_Data_Arr[i].Stat.Defense += tmep.Defense;
				Player_Data_Arr[i].Stat.Critical_Damage += tmep.Critical_Damage;
				Player_Data_Arr[i].Stat.Critical_Chance += tmep.Critical_Chance;
				Player_Data_Arr[i].Stat.Stance += tmep.Stance;
			}
			

			// 신발 스텟 추가
			{
				FGearStets tmep = GetGearStets(EGearType::Boots, InCombatType, Player_Data_Arr[i].Gear_Boots.GearEnhancementLevel);

				Player_Data_Arr[i].Stat.HP_Max += tmep.HP_Max;
				Player_Data_Arr[i].Stat.Damage += tmep.Damage;
				Player_Data_Arr[i].Stat.Defense += tmep.Defense;
				Player_Data_Arr[i].Stat.Critical_Damage += tmep.Critical_Damage;
				Player_Data_Arr[i].Stat.Critical_Chance += tmep.Critical_Chance;
				Player_Data_Arr[i].Stat.Stance += tmep.Stance;
			}


			return;
			
		}
}

void UCGameInstance::PlayerAddDamage(ECombatType InCombatType, float InDamage)
{
	for (int i = 0; i < Player_Data_Arr.Num(); i++)
	{
		if (Player_Data_Arr[i].Player_CombatData.CombatData.CombatType == InCombatType)
		{
			Player_Data_Arr[i].Stat.HP -= InDamage;
			TriggerUpdatePlayerData(InCombatType);
			break;
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
			SettingPlayerDataStats(InCombatType);

			TriggerUpdatePlayerData(InCombatType);
			return;
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


void UCGameInstance::BossDataTableToArr()
{
	if (!Boss_DataTable)
	{
		CLog::Print(L"Boss 데이터테이블을 읽어오지 못하였습니다");
	}
	else
	{
		TArray<FBoss_DataTable*> AllRows;
		Boss_DataTable->GetAllRows<FBoss_DataTable>(L"", AllRows);


		for (FBoss_DataTable* Row : AllRows)
		{
			if (Row)
				Boss_Data_Arr.Add(*Row);
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

FGearStets UCGameInstance::GetGearStets(EGearType InGearType, ECombatType InCombatType, int InLevel)
{
	FGearEnhancementData_DataTable tempData = GetGearEnhancementData(InGearType, InCombatType);
	FGearStets tempStets;

	for (int i = 0; i < tempData.GearEnhancementDataArr.Num(); i++)
	{
		if (i < InLevel)
		{
			tempStets.HP_Max += tempData.GearEnhancementDataArr[i].AddGearStats.HP_Max;
			tempStets.Damage += tempData.GearEnhancementDataArr[i].AddGearStats.Damage;
			tempStets.Defense += tempData.GearEnhancementDataArr[i].AddGearStats.Defense;
			tempStets.Critical_Damage += tempData.GearEnhancementDataArr[i].AddGearStats.Critical_Damage;
			tempStets.Critical_Chance += tempData.GearEnhancementDataArr[i].AddGearStats.Critical_Chance;
			tempStets.Stance += tempData.GearEnhancementDataArr[i].AddGearStats.Stance;
		}
		else
			break;
	}

	return tempStets;
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







// ------------------------------------------------Level-------------------------------------------------------

void UCGameInstance::MoveToLevel(FName InLevelName, FVector InSpawnPotin)
{
	PlayerSpawnPoint = InSpawnPotin;


	UGameplayStatics::OpenLevel(this, InLevelName);
}



// ----------------------------------------------------SaveGame-------------------------------------------------------
void UCGameInstance::SaveData(int Index)
{

	CSaveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));

	
	// 레벨
	FString FullName = GetWorld()->GetMapName(); // "UEDPIE_0_MyLevel"
	FString CleanName = FullName;

	// PIE 접두어 제거
	const FString PIEPrefix = TEXT("UEDPIE_");
	if (CleanName.StartsWith(PIEPrefix))
	{
		int32 PrefixEndIndex = CleanName.Find(TEXT("_"), ESearchCase::IgnoreCase, ESearchDir::FromStart, PIEPrefix.Len());
		if (PrefixEndIndex != INDEX_NONE)
		{
			// "UEDPIE_0_MyLevel" → "MyLevel"
			CleanName = CleanName.Mid(PrefixEndIndex + 1);
		}
	}
	CSaveGame->Save_SpawnLevelName = FName(CleanName);
		
	// 위치
	CSaveGame->Save_PlayerSpawnPoint = GetPlayerCharacter()->GetActorLocation();
	

	// 아이템
	CSaveGame->Save_MaterialItemItmeData_Arr.Empty();
	CSaveGame->Save_MaterialItemItmeData_Arr = MaterialItemItmeData_Arr;

	// 머니
	CSaveGame->Save_Money = Money;


	// 강화
	CSaveGame->Save_GearEnhancementData_Arr.Empty();
	CSaveGame->Save_GearEnhancementData_Arr = GearEnhancementData_Arr;

	// 퀘스트
	CSaveGame->Save_QuestData_Arr.Empty();
	CSaveGame->Save_QuestData_Arr = QuestData_Arr;

	
	UGameplayStatics::SaveGameToSlot(CSaveGame, ("SaveData_" + FString::FromInt(Index)), 0);
	CLog::Print(("SaveData_" + FString::FromInt(Index)));
	

	
	if (UGameplayStatics::DoesSaveGameExist(("SaveData_" + FString::FromInt(Index)), 0))
	{
		FString s = FString::FromInt(Index);
		s += L"의 세이브를 성공했습니다";
		TriggerSystemAlarm(s);
	}
	else
	{
		FString s = FString::FromInt(Index);
		s += L"의 세이브를 실패했습니다";
		TriggerSystemAlarm(s);
	}
	
}

bool UCGameInstance::LoadData(int Index)
{
	UCSaveGame* loadData = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot(("SaveData_" + FString::FromInt(Index)), 0));



	if (loadData)
	{
		CSaveGame = loadData;
		
		// 기존의 값 삭제
		{
			MaterialItemItmeData_Arr.Empty();
			QuestData_Arr.Empty();
		}
		


		// 저장된 정보 덮어씌우기
		{
			// 레벨
			SpawnLevelName = CSaveGame->Save_SpawnLevelName;

			// 위치
			PlayerSpawnPoint = CSaveGame->Save_PlayerSpawnPoint;


			// 아이템
			MaterialItemItmeData_Arr = CSaveGame->Save_MaterialItemItmeData_Arr;

			// 머니
			Money = CSaveGame->Save_Money;


			// 강화
			GearEnhancementData_Arr = CSaveGame->Save_GearEnhancementData_Arr;

			// 퀘스트
			QuestData_Arr = CSaveGame->Save_QuestData_Arr;
		}
		


		MoveToLevel(SpawnLevelName, PlayerSpawnPoint);


		FString s = FString::FromInt(Index);
		s += L"의 로드를 성공했습니다";
		LoadAlarm = s;
		

		
		return true;
	}
	else
	{

		FString s = FString::FromInt(Index);
		s += L"의 로드를 실패했습니다";
		TriggerSystemAlarm(s);

		return false;
	}

}

void UCGameInstance::DeleteData(int Index)
{
	if (UGameplayStatics::DoesSaveGameExist(("SaveData_" + FString::FromInt(Index)), 0))
	{
		// 데이터 삭제
		if (UGameplayStatics::DeleteGameInSlot(("SaveData_" + FString::FromInt(Index)), 0))
		{
			
			FString s = FString::FromInt(Index);
			s += L"의 데이터 제거를 성공했습니다";
			TriggerSystemAlarm(s);
		}
		else
		{
			FString s = FString::FromInt(Index);
			s += L"의 데이터 제거를 실패했습니다";
			TriggerSystemAlarm(s);
		}
	}
	else
	{
		FString s = FString::FromInt(Index);
		s += L"의 데이터를 찾지 못 하였습니다";
		TriggerSystemAlarm(s);
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



