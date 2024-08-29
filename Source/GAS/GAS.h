// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Needed for enhanced input interaction
UENUM(BlueprintType)
enum class EAbilityInputID : uint8 
{
	None,
	Confirm,
	Cancel,
	FireAbility
};