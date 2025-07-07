


#include "UI/HUD/AuraHUD.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();


}

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set in BP_AuraHUD!"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set in BP_AuraHUD!"));

	UAuraUserWidget* UserWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	if (!UserWidget) return;

	const FWidgetControllerParams Params(PC, PS, ASC, AS);
	OverlayWidgetController = GetOverlayWidgetController(Params);
	UserWidget->SetWidgetController(OverlayWidgetController);

	OverlayWidgetController->BroadcastInitialValues();

	UserWidget->AddToViewport();
}
