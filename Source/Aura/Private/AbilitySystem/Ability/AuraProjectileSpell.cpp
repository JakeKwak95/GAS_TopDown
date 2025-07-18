


#include "AbilitySystem/Ability/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include <Interaction/CombatInterface.h>

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	bool bIsServer = HasAuthority(&ActivationInfo);

	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if (!CombatInterface) return;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());
	AActor* OwningActor = GetOwningActorFromActorInfo();

	 auto Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass, 
		SpawnTransform, 
		OwningActor, 
		Cast<APawn>(OwningActor), 
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	 Projectile->FinishSpawning(SpawnTransform);
}
