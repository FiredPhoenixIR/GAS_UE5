// Fill out your copyright notice in the Description page of Project Settings.


#include "MST_BaseSet.h"

void UMST_BaseSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttributeOnChange(Attribute, NewValue);
}

void UMST_BaseSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttributeOnChange(Attribute, NewValue);
}

void UMST_BaseSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
}
