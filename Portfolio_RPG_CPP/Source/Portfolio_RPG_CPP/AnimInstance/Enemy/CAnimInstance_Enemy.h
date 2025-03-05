#pragma once

#include "CoreMinimal.h"
#include "../CAnimInstance_Base.h"
#include "CAnimInstance_Enemy.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCAnimInstance_Enemy : public UCAnimInstance_Base
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PawnOwnerIsValid() override;




	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EEnemyName EnemyName;



	class ACCharacter_Enemy* Owner_Enemy;

};
