


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <UI/HUD/AuraHUD.h>
#include <Player/AuraPlayerState.h>

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
    auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if(!PC) return nullptr;

	auto AuraHUD = Cast<AAuraHUD>( PC->GetHUD());
	if (!AuraHUD) return nullptr;

	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();
	const FWidgetControllerParams Params(PC,PS, ASC, AS);

	auto OverlayWidgetController = AuraHUD->GetOverlayWidgetController(Params);
	
	if (OverlayWidgetController) return OverlayWidgetController;
	else return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!PC) return nullptr;

	auto AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (!AuraHUD) return nullptr;

	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();
	const FWidgetControllerParams Params(PC, PS, ASC, AS);

	auto AttributeMenuWidgetController = AuraHUD->GetAttributeMenuWidgetController(Params);

	if (AttributeMenuWidgetController) return AttributeMenuWidgetController;
	else return nullptr;
}
