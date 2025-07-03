


#include "Character/AuraCharacterBase.h"
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


