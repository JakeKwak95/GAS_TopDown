


#include "AbilitySystem/Ability/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include <Interaction/CombatInterface.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>
#include "Aura/public/AuraGameplayTags.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if (!CombatInterface) return;

	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	Rotation.Pitch = 0;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	AActor* OwningActor = GetOwningActorFromActorInfo();

	auto Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		OwningActor,
		Cast<APawn>(OwningActor),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const auto SourceASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);

	const auto SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

	FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, Damage.GetValueAtLevel(GetAbilityLevel()));

	Projectile->DamageEffectSpecHandle = SpecHandle;

	Projectile->FinishSpawning(SpawnTransform);
}
