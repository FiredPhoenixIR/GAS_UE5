// Fill out your copyright notice in the Description page of Project Settings.


#include "MST_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "MST_GameplayAbility.h"
#include "MST_HealthSet.h"

// Sets default values
AMST_BaseCharacter::AMST_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HealthSet = CreateDefaultSubobject<UMST_HealthSet>(TEXT("HealthSet"));

}

// Called when the game starts or when spawned
void AMST_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Subscribe function to delegate
	HealthSet->OnDamageTaken.AddUObject(this, &AMST_BaseCharacter::OnDamageTakenChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetHealthAttribute()).AddUObject(this, &AMST_BaseCharacter::OnHealthAttributeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetShieldAttribute()).AddUObject(this, &AMST_BaseCharacter::OnShieldAttributeChanged);

}

UAbilitySystemComponent* AMST_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMST_BaseCharacter::InitializeAbilities()
{
	if (!HasAuthority() || !AbilitySystemComponent) {
		return;
	}

	for (TSubclassOf<UMST_GameplayAbility>& Ability : DefaultAbilities) {
		FGameplayAbilitySpecHandle AbilityHandle = AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(Ability, 1,
				static_cast<int32>(Cast<UMST_GameplayAbility>(Ability->GetDefaultObject())->GetAbilityInputID()), 
				// Cause GetDefault returns UOBJECT* we need to cast again
				this));
	}
}

void AMST_BaseCharacter::InitializeEffects()
{
	if (!AbilitySystemComponent) {
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect>& Effect : DefaultEffects) {
		FGameplayEffectSpecHandle EffectHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContext);
		if (EffectHandle.IsValid()) {
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectHandle.Data.Get());
		}
	}
}

void AMST_BaseCharacter::PostInitializeComponents()
{
	if (!AbilitySystemComponent)
		return;

	AbilitySystemComponent->InitAbilityActorInfo(this // It would be player state if it was the owner but i attached to character
		, this);

	InitializeAbilities();
	InitializeEffects();
}

void AMST_BaseCharacter::OnDamageTakenChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayTagContainer& GameplayTagConstainer, float Damage)
{
	OnDamageTaken(DamageInstigator, DamageCauser, GameplayTagConstainer, Damage);
}


void AMST_BaseCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}


void AMST_BaseCharacter::OnShieldAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnShieldChanged(Data.OldValue, Data.NewValue);
}


// Called every frame
void AMST_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMST_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

