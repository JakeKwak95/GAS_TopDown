


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Aura/Aura.h"

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacterBase::InitializePrimaryAttributes() const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	check(DefaultPrimaryAttributes);

    const FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
    const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.0f, EffectContext);
	ASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), ASC);
}


