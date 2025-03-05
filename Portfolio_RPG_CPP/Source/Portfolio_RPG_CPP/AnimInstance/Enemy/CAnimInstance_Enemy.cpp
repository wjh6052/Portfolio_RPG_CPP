#include "CAnimInstance_Enemy.h"
#include "../../Global.h"
#include "../../Character/AI/Enemy/CCharacter_Enemy.h"




void UCAnimInstance_Enemy::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}


void UCAnimInstance_Enemy::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Owner_Enemy == nullptr)
		Owner_Enemy = Cast<ACCharacter_Enemy>(TryGetPawnOwner());

	CheckNull(Owner_Enemy);

	EnemyName = Owner_Enemy->EnemyName;

}

void UCAnimInstance_Enemy::PawnOwnerIsValid()
{
}
