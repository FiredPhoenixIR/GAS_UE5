// Fill out your copyright notice in the Description page of Project Settings.


#include "MST_HealthSet.h"
#include "GameplayEffectExtension.h"

UMST_HealthSet::UMST_HealthSet() 
	:Health(40.f), MaxHealth(60.f), Shield(0.f), MaxShield(50.f), ShieldRegen(5.f)
{}

void UMST_HealthSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetShieldAttribute()){
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxShield());
	}
}

void UMST_HealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetInDamageAttribute())
	{
		float InDamageDone = GetInDamage();
		SetInDamage(0.f);
		if (InDamageDone > 0.f) {
			if (OnDamageTaken.IsBound()) {
				const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
				AActor* Instigator = EffectContext.GetOriginalInstigator();
				AActor* Causer = EffectContext.GetEffectCauser();

				OnDamageTaken.Broadcast(Instigator, Causer, Data.EffectSpec.CapturedSourceTags.GetSpecTags(), Data.EvaluatedData.Magnitude);
			}

			if (GetShield() > 0.f) {
				const float NewShield = GetShield() - InDamageDone;
				InDamageDone -= GetShield();
				SetShield(FMath::Clamp(NewShield, 0.f, GetMaxShield()));
			}
			if (InDamageDone > 0.f || GetHealth() > 0.f) {
				const float NewHealth = GetHealth() - InDamageDone;
				SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			}
		}
	}
}
