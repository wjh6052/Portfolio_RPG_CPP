#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Datas/Data_Inventory.h"
#include "CItemInteraction.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API ACItemInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACItemInteraction();

protected:
	virtual void BeginPlay() override;


private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
	// Get
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE FString GetItemName() { return ItemName; }



protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* DefaultRoot;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USphereComponent* SphereComponent;


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		EInteractionCategory InteractionCategory;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		class UObject* InteractionImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setting")
		FString ItemName;

};
