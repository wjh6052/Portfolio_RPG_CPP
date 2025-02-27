#include "CCharacter_Enemy.h"
#include "../../Global.h"
#include "../../AnimInstance/CAnimInstance_Base.h"



ACCharacter_Enemy::ACCharacter_Enemy()
{
	// StatComp를 위한 캐릭터 태그
	CharacterType = ECharacterType::Enemy;

	TSubclassOf<UCAnimInstance_Base> animInstanceClass;
	CHelpers::GetClass<UCAnimInstance_Base>(&animInstanceClass, "AnimBlueprint'/Game/AnimInstance/Enemy/ABP_Enemy_Mannequins'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);
}

void ACCharacter_Enemy::BeginPlay()
{
	Super::BeginPlay();






}
