#pragma once

//-----------------------------------------------------------------------------
//Macros
//-----------------------------------------------------------------------------
#define CheckNull(p) { if(p == nullptr) return; }
#define CheckNullResult(p, result) { if(p == nullptr) return result; }

#define CheckTrue(p) { if(p == true) return; }
#define CheckTrueResult(p, result) { if(p == true) return result; }

#define CheckFalse(p) { if(p == false) return; }
#define CheckFalseResult(p, result) { if(p == false) return result; }

//-----------------------------------------------------------------------------
//CHelpers
//-----------------------------------------------------------------------------
class PORTFOLIO_RPG_CPP_API CHelpers
{
public:
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), TEXT("Class Not Found"));
		
		*OutClass = asset.Class;
	}

	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), TEXT("Asset Not Found"));

		*OutObject = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* object = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
		verifyf(!!object, TEXT("Asset Not Found - Dynamic"));

		*OutObject = object;
	}

	template<typename T>
	static void CreateSceneComponent(AActor* InActor, T** OutComponent, FName InName, USceneComponent* InParent = nullptr)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
		
		if (!!InParent)
		{
			(*OutComponent)->SetupAttachment(InParent);
			return;
		}
		
		InActor->SetRootComponent(*OutComponent);
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComponent, FName InName)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
	}

	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	template<typename T>
	static FString GetEnumDisplayName(T EnumValue)
	{
		static_assert(TIsEnum<T>::Value, "T must be an enum type"); // 열거형 타입인지 확인

		const UEnum* EnumPtr = StaticEnum<T>(); // 열거형의 UEnum 정보 가져오기
		if (!EnumPtr) return TEXT("Invalid");

		return EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString();
	}

};