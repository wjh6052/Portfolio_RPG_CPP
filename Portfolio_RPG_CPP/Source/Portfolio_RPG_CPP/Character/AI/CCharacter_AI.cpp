#include "CCharacter_AI.h"
#include "../../Global.h"




ACCharacter_AI::ACCharacter_AI()
{
	bUseControllerRotationYaw = true;

	CHelpers::CreateActorComponent(this, &PatrolComponent, "PatrolComponent");
}

