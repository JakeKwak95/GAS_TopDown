

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AuraInputConfig.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputCinfig, UserClass* Object, PressedFuncType PressedFun, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
inline void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputCinfig, UserClass* Object, PressedFuncType PressedFun, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	if (!InputCinfig) return;

	for (const FAuraInputAction& Action : InputCinfig->AbilityActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFun)
			{
				BindAction(Action.Action, ETriggerEvent::Started, Object, PressedFun, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.Action, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.Action, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
