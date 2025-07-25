


#include "Character/AuraEnemy.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include <AbilitySystem/AuraAttributeSet.h>
#include "Components/WidgetComponent.h"
#include "UI/Widget/AuraUserWidget.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"


void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();

	const auto HealthBar = Cast<UAuraUserWidget>(HealthBarWidget->GetUserWidgetObject());
	if (HealthBar)
		HealthBar->SetWidgetController(this);

	const auto AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	OnHealthChanged.Broadcast(AuraAS->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->OnAbilityActorActorInfoSet();

	InitializeDefaultAttributes();
}

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBarWidget->SetupAttachment(GetRootComponent());
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel() const
{
	 return Level; 
}

void AAuraEnemy::InitializeDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}