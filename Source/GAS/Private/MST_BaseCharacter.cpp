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
}

void AMST_BaseCharacter::InitializeEffects()
{
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

