#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWings.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API ACWings : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWings();


protected:
	virtual void BeginPlay() override;


public:
	void SpawnWings(bool input);
	void AttachTo(FName InSocketName);

	void SetSprint(bool input);


public:
	//Get
	FORCEINLINE FVector GetWing_L() const { return Wing_L; }
	FORCEINLINE FVector GetWing_R() const { return Wing_R; }
	



	UFUNCTION(BlueprintCallable)
		FORCEINLINE void WingsMoveReset() { Wing_L = FVector::ZeroVector; Wing_R = FVector::ZeroVector; }


	UFUNCTION(BlueprintCallable)
		void SetWingsMove(float input);



public:	// �������Ʈ���� ȣ��� �̺�Ʈ

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnWingsImpact();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void WingsMove();

	UFUNCTION(BlueprintImplementableEvent)
		void WingsStop();



public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USkeletalMeshComponent* WingsMesh;



private:
	class ACCharacter_Player* OwnerPlayer;

	// ���� ������
	FVector Wing_L;
	FVector Wing_R;


};
