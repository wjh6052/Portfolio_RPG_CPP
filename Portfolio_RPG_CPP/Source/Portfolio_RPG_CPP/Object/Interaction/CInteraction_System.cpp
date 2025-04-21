#include "CInteraction_System.h"




ACInteraction_System::ACInteraction_System()
{
	InteractionCategory = EInteractionCategory::System;
}

void ACInteraction_System::UseInteractionSystem()
{
	UseInteractionSystem_Blueprint();
}
