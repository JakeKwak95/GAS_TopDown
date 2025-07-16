


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InputTag, bool bLogWhenNotFound) const
{
	for (const auto& InputAction : AbilityInputActions)
	{
		if(InputAction.InputTag.MatchesTagExact(InputAction.InputTag))
		{
			return InputAction.InputAction;
		}
	}

	if(bLogWhenNotFound)
		UE_LOG(LogTemp, Error, TEXT("Input Action with tag [%s] not found in InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));

	return nullptr;
}
