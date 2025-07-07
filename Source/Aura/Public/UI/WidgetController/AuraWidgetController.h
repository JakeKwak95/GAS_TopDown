

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS){}
};



/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "WidgetController")
	void SetWidgetControllerParams(const FWidgetControllerParams& Params);

	virtual void BroadcastInitialValues();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
