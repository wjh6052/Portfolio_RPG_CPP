#include "CItemInteraction_Money.h"
#include "../../Global.h"


#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"



ACItemInteraction_Money::ACItemInteraction_Money()
{
	InteractionCategory = EInteractionCategory::Money;
	ItemName = L"돈";


	// 머니 스태틱 메시 설정
	UStaticMesh* money_Mesh;
	CHelpers::GetAsset<UStaticMesh>(&money_Mesh, "StaticMesh'/Game/Asset/Object/Money/Mora.Mora'");
	StaticMesh->SetStaticMesh(money_Mesh);
	StaticMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	StaticMesh->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

	
	// 콜리젼 크기 설정
	SphereCollision->SetSphereRadius(100.f);
	SphereCollision->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));


	// 머니 이미지 설정
	UObject* money_Image;
	CHelpers::GetAsset<UObject>(&money_Image, "Texture2D'/Game/Asset/Widget_Asset/Texture/Item_Icon/Item_Mora.Item_Mora'");
	InteractionImage = money_Image;


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