#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Components/CharacterComp/CStatComponent.h"
#include "CAnimInstance_Base.generated.h"


UCLASS()
class PORTFOLIO_RPG_CPP_API UCAnimInstance_Base : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PawnOwnerIsValid();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bFalling;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EStateType StateType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EStatusType StatusType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		ECombatType CombatType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bLookOn;


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class ACCharacter_Base* OwnerCharacter;
	
};
