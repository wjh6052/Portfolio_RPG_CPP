## ▶️ 데모 시연 영상 (이미지 클릭↓)




## 프로젝트 개요
|항목|내용|
|------|---|
|프로젝트명|UE5.2_Portfolio_RPG_CPP|
|개발 기간|2025.1 - 2025.04 (4개월)|
|사용 Tool|UnrealEngine5, Visual Studio, KawaiiPhysics, SPCRJointDynamics|
|목표|'원신'을 모티브로 잡으며 RPG 전투 시스템과 캐릭터 교체 기능을 구현|
|주요 기능|캐릭터 교체 시스템, 툰 렌더링, 액션 시스템(콤보공격/스킬/궁극기), 상호 작용, 미니맵 및 UI 개발|
|기여도|1인 개발 (설계부터 구현까지 전체 담당)|


***
## 프로젝트 목표
상점, 퀘스트, 전투 필드 등 RPG의 핵심 시스템을 구현하여 적을 처치하고 마을을 지켜내는 컨셉의 게임을 제작

***

## 주요 기능 및 기술적 구현

|기능명|설명 및 구현 방식|
|------|---|
|캐릭터 교체 시스템|다양한 캐릭터로 교체하며 무기에 맞는 액션 시스템 사용 가능|
|액션 및 전투 시스템|일반 공격, 스킬 등의 액션|
|상호작용|아이템, NPC 등 다양한 오브젝트와 상호작용|
|렌더링|머티리얼을 통한 렌더링 제작|
|미니맵 및 지도|SceneCaptureComponent2D를 활용하여 실시간 미니맵 렌더링|

***

## 목차

[1. 데이터 기반 시스템](#1-데이터-기반-시스템)  
[2. 캐릭터 교체, 액션 및 전투 시스템](#2-캐릭터-교체-액션-및-전투-시스템)  
[3. AI 시스템](#3-ai-시스템)  
[4. 상호작용](#4-상호작용)  
[5. UI 시스템 및 미니맵](#5-ui-시스템-및-미니맵)  
[6. 툰 렌더링](#6-렌더링)  
[7. 디테일](#7-디테일)  
[8. 세이브 및 로드](#8-세이브-및-로드)  
[9. 포트폴리오 관련 링크](#9-포트폴리오-관련-링크)

***

## 1. 데이터 기반 시스템
**🛠 데이터 테이블을 통한 관리**

  🔹 플레이어 데이터 테이블
    + 플레이어 캐릭터, 전투 데이터
    플레이어의 각 매쉬, 콜리전의 크기, 플레이어 스텟, 해당 캐릭터가 가질 무기의 설정 및 애니메이션을 담당  
<img src="https://github.com/user-attachments/assets/e83aded3-450b-4d8b-8d12-fd1d02de7da2" width="500"/><br>
    + 플레이어 비행 데이터
      플레이어의 비행시 속도 스탯, 지형과의 상호작용하여 나올 임팩트 등을 설정
<img src="https://github.com/user-attachments/assets/126560af-cbd4-4b56-b9f0-b5205ef67089" width="500"/><br>

🔹 NPC
  + NPC 데이터
    NPC의 타입, NPC가 보유할 퀘스트의 ID, 대화 목록 배열을 설정 NPC의 이름을 열거형으로 정리하여 해당 NPC캐릭터에게 데이터를 저장한다  
  + 퀘스트
    퀘스트 ID, 퀘스트 이름, 스토리, 보상, 퀘스트 오브젝트* 등 퀘스트와 관련된 데이터를 저장
    [퀘스트 오브젝트는 퀘스트 전, 진행 중, 클리어 후의 데이터를 담을 액터]

🔹 몬스터 및 보스
  + 몬스터
    몬스터의 이름 열거형으로 해당 몬스터의 종류를 판단한다
    몬스터의 스텟, 전투와 관련된 데이터, 무기 오브젝트, 죽었을 때의 드랍정보를 저장한다
    
  + 보스
    기본적으로 몬스터와 동일하나 보스인 경우 범위 공격을 하기 때문에 범위 공격과 관련된 데이터를 추가로 적용한다  
    
🔹 강화 데이터  
   + 플레이어의 무기, 장비에 대한 강화 정보를 관리한다
     장비의 종류, 캐릭터의 종류를 각 열거형으로 나눠 정보를 판단한다
     강화 단계에 따른 확률, 천장의 배율, 강화 성공시 추가될 스텟을 저장 및 관리한다
  
🔹 아이템 데이터  
   + 재료아이템 포션 등을 저장 및 관리하는 데이터
     아이템의 종류, 아이템의 쓰임세, 아이템의 등급을 열거형으로 관리한다
     아이템의 이름, 보유갯수, UI에 표시될 텍스쳐, 설명, 판매/구매 가격를 담당한다

**🛠 데이터 에셋을 통한 관리**
🔹 범위공격 에셋
  + 주로 보스몬스터에게 사용될 범위공격의 범위를 보여줄 댑스의 머티리얼의 에셋을 관리한다
  <img src="https://github.com/user-attachments/assets/52e9198a-05b4-460f-8689-67599c1a3763" width="500"/><br>

🔹 데미지 나이아가라 에셋
  + 전투 중 데미지를 숫자로 표시할 나이아가라 시스템의 에셋을 관리한다
 <img src="https://github.com/user-attachments/assets/fcf4aa09-5202-4405-b3fc-e2995c623eb3" width="500"/><br>


🔹 맵 아이콘 에셋
  + 맵이나 미니맵에 사용될 스프라이트 에셋을 관리하는 데이터 에셋
 <img src="https://github.com/user-attachments/assets/890609fc-2a5e-4126-856b-910a31df7004" width="500"/><br>


## 2. 캐릭터 교체, 액션 및 전투 시스템

**🛠 캐릭터 교체**
+ 게임 플레이 도중 Tab키를 눌러 무기 변경 UI를 화면에 띄운 후 마우스 커서가 있는 무기로 변경하여 무기에 해당하는 캐릭터의 매쉬, 스킬을 변경하는 기능합니다
  
<img src="https://github.com/user-attachments/assets/72608d01-5aa0-4a2c-ae1a-bc14652b59e5" width="500"/>
<img src="https://github.com/user-attachments/assets/881af940-fbe3-43cc-a436-49c750ed6cc4" width="500"/><br>

<br> <br>

**🛠 액션 및 전투 시스템**

🔹 전투 클래스 구조
<pre>
  CombatComponent 
  │ 
  ActionBase 
  │ 
  ├── CAction 
  │     ├── StartWeapon (무기를 꺼낼 때) 
  │     ├── ComboAttack (일반공격) 
  │     └── StartSkill (스킬) 
  │ 
  └── CCombat_Melee 
  </pre>

🔹 전투 실행 흐름
<pre>
  void ACCombat_Base::ComboAttack()마우스 좌클릭 또는 공격입력
{
	CheckTrue(bSkill); // 스킬 사용 중일 경우 입력을 받지 않도록 설정

	if (bCanNextComboTiming) // 현재 공격중일 특정 타이밍일 경우 다음 콤보를 체크
	{
		bCanNextCombo = true;
	}
	
	// 공격 애니메이션을 실행
	if (!OwnerCharacter->GetStatComponent()->IsState(EStateType::Attacking))
	{
		OwnerCharacter->PlayAnimMontage(CombatData.Combo_Attack[ComboNum].AnimMontage.AnimMontage, CombatData.Combo_Attack[ComboNum].AnimMontage.PlayRate);
	}
}

void ACCombat_Base::NextComboAttack()
{
	//bCanNextCombo == true인 경우 다음 콤보 애니메이션 실행
}

 </pre>

🔹 스킬
  1, 2, 3번을 눌러 스킬을 발동.
  스킬 사용 후 쿨타임이 돌아가며 전투 데이터에서 설정한 에니메이션이 실행, 애님노티파이에 의해서 다음 스킬 애니메이션이 자동으로 실행됩니다
  다른 연출을 위해  각 스킬마다 노티파이를 설정했습니다

🔹 데미지 적용 및 영향
  무기의 콜리전 충돌 -> 충돌될 캐릭터의 UCCombatComponent::TakeDamage호출 -> 중복확인 -> 데미지, 사망처리 -> 히트 연출 및 데미지 텍스트 스폰


## 3. AI 시스템
🔹 CCharacter_Base를 상속 받은 CCharacter_AI 클래스로 구성

  
**🛠 몬스터 및 보스**<br>
+ AIController 및 Behavior Tree를 활용하여 AI 상태 관리
+ CAISpawner를 통해 몬스터를 스폰 및 리스폰 구현
+ USplineComponent를 소유한 CPatrolPath를 통하여 몬스터, 보스의 경계 루트 구현
<img src="https://github.com/user-attachments/assets/a5bf5a9e-f510-4ffa-b571-329f6a1d9a52" width="500"/><br>

**🛠 NPC**<br>
+ NPC는 상호작용 클레스 CInteraction를 상속 받은 CInteraction_NPC를 스폰하여 캐릭터에 붙여 플레어와 상호작용 하도록 설정

## 4. 상호작용
**🛠 상호작용**<br>

<img src="https://github.com/user-attachments/assets/0a48d0e5-46b2-4c41-99c2-622451ab6278" width="500"/><br>
|상호작용 오브젝트|동작|
|---|---|
|아이템, 머니|아이템, 머니를 획득|
|NPC|NPC와 대화 시작|
|시스템 오브젝트|해당 오브젝트에 따라 다른 상호작용|

🔹 ACInteraction 클래스를 상속 받아 ACInteraction에 있는 콜리전을 통해 상호작용을 구현
  + 플레이어가 콜리전에 진입시 상호작용 오브젝트의 데이터를 받아와 위젯 배열에 저장, F키를 입력 시 현재 선택된 오브젝트와 상호작용합니다
    <br>



## 5. UI 시스템 및 미니맵<br>
<img src="https://github.com/user-attachments/assets/3c8029f1-e6d9-47cd-b3f4-1b4307911304" width="500"/><br>
🔹 UI의 전체 흐름
 <pre>
CWB_Main
│
├── 위젯스위처
│   ├── WB_GameplayUI (기본 게임 화면)
│   ├── CBP_WInventory(인벤토리 및 메뉴)
│   ├── CWB_NPCTalkUI (NPC 상호작용)
│   └── WB_PlayerDie  (플레이어가 죽었을 때)
│
└── WB_AddItmeBarBox (아이템, 돈 획득 아이콘)
│
└── WB_ProgressTextBox (시스템 메세지)
 </pre> <br>



 
**🛠 기본 게임 화면**<br>
<img src="https://github.com/user-attachments/assets/f4ae3e3f-12ca-453f-a414-179159ebd16f" width="500"/><br>

🔹 미니맵
  + 플레이어의 상단에 ceneCaptureComponent2D를 활용한 실시간 미니맵 구현
<br>
🔹 상호작용 바
  + 상호작용 오브젝트의 콜리전에 충돌 시 UI로 오브젝트의 이름,아이콘, 갯수를 표시합니다
  + 마우스 휠을 통하여 위아래로 움직여 선택이 가능하며 F를 눌러 상호작용 합니다
<br>

* UI 종류
|UI 유형|기능|
|---|---|
|인벤토리|보유중인 아이템, 캐릭터 + 장비 스텟 등을 보여주며 메뉴의 역활도 한다|
|NPC 상호작용|NPC와의 상호작용 대화,상점,대장장이,퀘스트를 담당한다|
|플레이어 다이|플레이어가 죽었을때 나오는 창으로 새로하기, 로드하기, 로비로 이동이 표시된다|
|아이템 획득 바|아이템, 돈을 획득이나 잃었을때 플레이어에게 알려주는 역활을 한다|
|시스템 메시지|대표적으로 세이브,로드등을 하였을때 플레이어에게 알려주는 역활을 한다|


**추가 설명**<br>
* 📄 [UI 상세 설명 PPT (Google Drive)](https://drive.google.com/drive/folders/1O-1oLa-TYRhBmjl65HDWEK9a34n4Tsav?usp=drive_link)
 <br>
 <br>

 
## 6. 렌더링
**🛠 카툰 렌더링**<br>
<img src="https://github.com/user-attachments/assets/d301ac33-012b-4c1d-bd2f-e2f7de71376b" width="500"/><br>
<img src="https://github.com/user-attachments/assets/2f90bd1b-0254-43ba-9769-5b5fe9c311ea" width="500"/><br>
🔹 카툰 렌더링 머티리얼 제작
+ 포스트프로세스 머티리얼를 제작하여 카툰 렌더링을 구현, 언리얼의 그래픽을 최대한 이용하기 위해 커스텀 뎁스를 통해 캐릭터만 툰 렌더링을 사용
+ 머티리얼 인스턴스의 값을 수정하여 렌더링의 설정을 변경할 수 있도록 설계


**🛠 오클루전 시스템**<br>
<img src="https://github.com/user-attachments/assets/c5bf02fb-e263-44f1-a33f-97ce20791e08" width="500"/><br>
🔹 오클루전 머티리얼
+ 커스텀 뎁스를 통하여카메라와 캐릭터의 사이에 오브젝트가 들어와 있으면 가려진 부분을 회색으로 보이게 하여 캐릭터를 찾을 수 있도록 하였습니다
  
<br>
<br>

## 7. 디테일
<br>
🔹 캐릭터 리타겟팅
+ 베이스가 될 마네킹 밑에 보여질 캐릭터 메쉬, 메쉬 아웃라인을 통해 마네킹 애니메이션 만으로도 모든 캐릭터의 애니메이션 인스턴스를 구성했습니다
<br><img src="https://github.com/user-attachments/assets/7a9169d9-9e23-471b-be2f-e9c083c82d58" width="250"/><br>

<br>
🔹 캐릭터의 머리카락, 옷 효과
+ 캐릭터의 머리카락, 옷의 부드러운 움직임을 위해 KawaiiPhysics, SPCRJointDynamics플러그인을 이용하여 표현
언리얼의 클로딩 시스템 보다 자연스러운 연출이 가능했으며 최적화 부분에서도 효율이 좋아 플러그인을 사용하도록 결정하였습니다
<br><img src="https://github.com/user-attachments/assets/50fa12bf-1f2b-4f1e-81b6-a6771a1e08f4" width="500"/><br>

<br>
🔹 무기 매쉬 임팩트
+ 무기를 들었을 때 뺐을 때 무기가 서서히 보이도록/사라지도록 구현
  - 서서히 사라지는 머티리얼을 제작, 무기의 머티리얼을 다이나믹 인스턴스로 교체 후 머티리얼의 값을 타임라인으로 조정하여 서서히 사라지는 효과를 구현했습니다



## 8. 세이브 및 로드
<br>
🔹 UCSaveGame를 통해 각종 데이터를 저장
<pre>
UCLASS()
class PORTFOLIO_RPG_CPP_API UCSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	// 저장했던 당시의 레벨
	UPROPERTY(SaveGame)
		FName Save_SpawnLevelName;

	// 저장했던 당시의 위치
	UPROPERTY(SaveGame)
		FVector Save_PlayerSpawnPoint;


	// 플레이어 데이터
	UPROPERTY(SaveGame)
		TArray<FPlayer_DataTable> Save_Player_Data_Arr;

	// 보유 아이템 데이터
	UPROPERTY(SaveGame)
		TArray<FMaterialItem_DataTable> Save_MaterialItemItmeData_Arr;
	
	// 보유 머니 아이템
	UPROPERTY(SaveGame)
		int Save_Money;


	// 현제 강화 데이터
	UPROPERTY(SaveGame)
		TArray<FGearEnhancementData_DataTable> Save_GearEnhancementData_Arr;

	// 퀘스트 진행도
	UPROPERTY(SaveGame)
		TArray<FQuest_DataTable> Save_QuestData_Arr;
}; 
 </pre> <br>
 <br>
🔹 UI를 통해 세이브 데이터를 저장, 로드, 삭제를 구현
<br><img src="https://github.com/user-attachments/assets/a3bd9529-f3d5-4fce-b783-7e3d3f583e25" width="500"/><br>
<br>

## 9. 포트폴리오 관련 링크
<br>

[포트폴리오 영상 보기](https://www.youtube.com/watch?v=PboJuj6Sku8)  
[GitHub 소스코드 확인](https://github.com/wjh6052/Portfolio_RPG_CPP)  
[게임 데모, UI 정리 PPT 다운로드](https://drive.google.com/drive/folders/1sUIedU8rEOF7PQWR05eeySVDdqj9V2ri?usp=drive_link)  
