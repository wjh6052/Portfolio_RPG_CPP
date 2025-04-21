#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../../Datas/Data_DataTable.h"
#include "CAN_SpawnLandingVFX.generated.h"



UCLASS()
class PORTFOLIO_RPG_CPP_API UCAN_SpawnLandingVFX : public UAnimNotify
{
	GENERATED_BODY()
	

public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;



	bool NotifiLineTracetoUpVector(float vectorLength, FHitResult& hitResult);


	class UNiagaraComponent* SpawnNiagaraAtLocationOrAttach(bool isAttach, UNiagaraSystem* SystemTemplate, USceneComponent* AttachToComponent, FVector Location, FRotator Rotation);



	class ACCharacter_Base* Character;

	float VectorLength = -500.f;


	UPROPERTY(EditAnywhere)
		FName SocketName = "root";
};
