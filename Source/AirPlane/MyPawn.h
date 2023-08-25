// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

//���漱�� �ϱ� ��ƴ�. (�����ͷ� �޴¾ֵ鸸 ���漱������ �޴´�)
#include "InputActionValue.h"
#include "MyPawn.generated.h"
//MyPawn.generated.h ���� include�ؾ���.

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UFloatingPawnMovement;
class UMyActorComponent;

UCLASS()
class AIRPLANE_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Visible�̸� ���̱⸸ �ϴ°ǵ� �ٸ� �������� �ٲ� �� �ִ°� UBoxComponent�ȿ� �Ӽ��� ���� �׷��� �����Ǿ� �־��.
	// BlueprintReadOnly Get�� ����
	// BlueprintReadWrite �ϸ� �Ѵ� ���´�.
	// show Inherited Varied �ϸ� ������ �������� ���. 
	// ������Ʈ�� get�� ����. (�ʱ�ȭ �Ǹ� �ȵǴϱ�)

	// public�� �ƴҶ� �ܺο��� �������� meta�� ���� ��.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UBoxComponent* Box;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Body;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Right;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UFloatingPawnMovement* Movement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMyActorComponent* MyActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float PropellerRotationSpeed = 3060;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float BoostValue = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Gold = 100;

	//UFUNCTION X
	void Pitch(float Value);
	
	void Roll(float Value);

	void Fire();
	void Boost();
	void UnBoost();

	// Digital, Axis1D, Axis2D, Axis3D�� ���� �ҷ��� �� �ְ� const FInputActionValue&�� �־��
	void EnhancedBoost(const FInputActionValue& Value);

	void EnhancedUnBoost(const FInputActionValue& Value);

	void EnhancedFire(const FInputActionValue& Value);

	void EnhancedPitchAndRoll(const FInputActionValue& Value);



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	class UInputAction* IA_Boost;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_PitchAndRoll;


};


