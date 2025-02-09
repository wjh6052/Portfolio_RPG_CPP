#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Datas/Data_Inventory.h"
#include "CInteraction.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACInteraction();

protected:
	virtual void BeginPlay() override;


protected:
	UFUNCTION()
		virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
	// Get
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE FString GetItemName() { return ItemName; }
	FORCEINLINE class USphereComponent* GetSphereCollision() { return SphereCollision; }



protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* DefaultRoot;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USphereComponent* SphereCollision;


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		EInteractionCategory InteractionCategory;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		class UObject* InteractionImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		FString ItemName;


	class ACCharacter_Base* OwnerCharacter;

};
