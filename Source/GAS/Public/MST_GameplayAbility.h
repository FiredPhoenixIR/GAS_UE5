// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAS/GAS.h"
#include "MST_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UMST_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Ability")
	EAbilityInputID AbilityInputID{ EAbilityInputID::None };

public:
	EAbilityInputID GetAbilityInputID() const { return AbilityInputID; };
};
