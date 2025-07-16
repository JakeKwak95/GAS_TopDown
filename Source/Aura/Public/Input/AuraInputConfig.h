

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FAuraInputAction {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag InputTag = FGameplayTag::EmptyTag;
};

class UInputAction;

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InputTag, bool bLogWhenNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FAuraInputAction> AbilityInputActions;
	
};
