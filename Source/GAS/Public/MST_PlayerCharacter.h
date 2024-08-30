// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MST_BaseCharacter.h"
#include "MST_PlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


/**
 * 
 */
UCLASS()
class GAS_API AMST_PlayerCharacter : public AMST_BaseCharacter
{
	GENERATED_BODY()

	AMST_PlayerCharacter();
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArm;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookingAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category = "Input")
	UInputAction* FireAbilityAction;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SendAbilityLocalInput(const FInputActionValue& Value, int32 InpudID);
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void FireAbility(const FInputActionValue& Value);

};
