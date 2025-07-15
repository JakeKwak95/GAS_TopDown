

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	FGameplayTag AttributeTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float AttributeValue = 0.0f;
};

/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FAuraAttributeInfo FindAuraAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	TArray<FAuraAttributeInfo> AttributeInfos;
};
