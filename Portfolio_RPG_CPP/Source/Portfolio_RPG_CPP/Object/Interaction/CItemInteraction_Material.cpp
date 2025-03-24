#include "CItemInteraction_Material.h"
#include "../../Global.h"
#include "../../CGameInstance.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"



ACItemInteraction_Material::ACItemInteraction_Material()
{
	InteractionCategory = EInteractionCategory::Material;

	// 재료아이템 스테틱 메시 설정
	UStaticMesh* material_Mesh;
	CHelpers::GetAsset<UStaticMesh>(&material_Mesh, "StaticMesh'/Game/Asset/Object/Bailu_Bottle/Bailu_Bottle.Bailu_Bottle'");
	StaticMesh->SetStaticMesh(material_Mesh);
	

	// 콜리젼 크기 설정
	SphereCollision->SetSphereRadius(100.f);


	// 콜리전 설정을 활성화
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// 캐릭터와의 충돌을 무시하고 다른 오브젝트와 충돌하도록 설정
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);  // 캐릭터 충돌 무시
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);  // 다른 아이템 오브젝트와 충돌 무시
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); // 월드 정적 오브젝트와 충돌
	StaticMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);   // 가시성 오브젝트와 충돌

	



	// 스테틱매쉬에게 중력적용
	StaticMesh->SetSimulatePhysics(true);
}


void ACItemInteraction_Material::BeginPlay()
{
	Super::BeginPlay();

	SetMaterialItemIcon();
	
}

void ACItemInteraction_Material::SetMaterialItemIcon()
{
	UCGameInstance* cGameInstance = Cast<UCGameInstance>(GetGameInstance());

	if (cGameInstance)
	{
		for (int i = 0; i < cGameInstance->MaterialItemItmeData_Arr.Num(); i++)
		{
			if (cGameInstance->MaterialItemItmeData_Arr[i].StarRating == FInteractionItemMaterial.StarRating &&
				cGameInstance->MaterialItemItmeData_Arr[i].ItemUseType == FInteractionItemMaterial.ItemUseType)
			{
				InteractionImage = cGameInstance->MaterialItemItmeData_Arr[i].ItemImage;
				ItemName = cGameInstance->MaterialItemItmeData_Arr[i].ItemName;
			}
		}
	}
}