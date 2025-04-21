#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../../Datas/Data_Enum.h"
#include "CNS_AttackTrace.generated.h"




UCLASS()
class PORTFOLIO_RPG_CPP_API UCNS_AttackTrace : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	void BossNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);




	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;



	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	
	void BossEndNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ECharacterType CharacterType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ESkillDecalType SkillDecalType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bOnDebug = false;

	TArray<class ACCharacter_Base*> TargetArr;
	

	bool OnTarget = false;
};
