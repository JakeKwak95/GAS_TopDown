

#pragma once

#include "GameplayTagContainer.h"
#include "CoreMinimal.h"

struct FAuraGameplayTags 
{
public:
	static const FAuraGameplayTags& Get() { return Instance; }
	static void InitializeNativeGameplayTags();

protected:

private:
	static FAuraGameplayTags Instance;
};
