


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAuraAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInfos)
	{
		if(Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}

	if(bLogNotFound)
		UE_LOG(LogTemp, Error, TEXT("AttributeInfo: Could not find AttributeInfo for tag: %s"), *AttributeTag.ToString());

	return FAuraAttributeInfo();
}
