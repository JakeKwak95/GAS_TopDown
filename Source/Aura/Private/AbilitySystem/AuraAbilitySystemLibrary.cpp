


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Game/AuraGameModeBase.h"
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

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	ApplyEffectSpec(ASC, AvatarActor, ClassDefaultInfo, Level, ClassDefaultInfo.PrimaryAttributes);
	ApplyEffectSpec(ASC, AvatarActor, ClassDefaultInfo, Level, CharacterClassInfo->SecondaryAttributes);
	ApplyEffectSpec(ASC, AvatarActor, ClassDefaultInfo, Level, CharacterClassInfo->VitalAttributes);
}

void UAuraAbilitySystemLibrary::ApplyEffectSpec(UAbilitySystemComponent* ASC, AActor* AvatarActor, FCharacterClassDefaultInfo& ClassDefaultInfo, float Level, TSubclassOf<UGameplayEffect> Attributes)
{
	FGameplayEffectContextHandle AttributesContextHandle = ASC->MakeEffectContext();
	AttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle AttributesSpecHandle = ASC->MakeOutgoingSpec(Attributes, Level, AttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*AttributesSpecHandle.Data.Get());
}

void UAuraAbilitySystemLibrary::GiveStartingAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	for (TSubclassOf<UGameplayAbility>& Ability : GetCharacterClassInfo(WorldContextObject)->CommonAbilities)
	{
		if (Ability)
		{
			ASC->GiveAbility(FGameplayAbilitySpec(Ability));
		}
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!AuraGameMode) return nullptr;

	return AuraGameMode->CharacterClassInfo;
}
