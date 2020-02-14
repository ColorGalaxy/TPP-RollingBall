// Fill out your copyright notice in the Description page of Project Settings.

#include "SphereBase.h"
#include "Components/StaticMeshComponent.h"//Meshͷ�ļ�
#include "GameFramework/SpringArmComponent.h"//������ֱ�ͷ�ļ�
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/InputComponent.h"//���밴����ͷ�ļ�
#include "Engine.h"

// Sets default values
ASphereBase::ASphereBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsInput = true;
	SphereSpeed = 300.0f;
	SpeedMin = SphereSpeed;
	SpeedMax = 500.0f;
	ZoomValue = 0.5f;

	//�������
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SphereMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereBaseComp"));
	CameraArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArmComp"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	//�����ϵ
	SphereMeshComp->SetupAttachment(RootComp);
	CameraArmComp->SetupAttachment(RootComp);
	CameraComp->SetupAttachment(CameraArmComp);

	//���ò���
	//CameraArmComp->TargetArmLength = 1000.0f;
	CameraArmComp->bEnableCameraLag = false;
	//CameraArmComp->CameraLagSpeed = 6.0f;
	
	//��������Ч��Ϊ��
	SphereMeshComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ASphereBase::BeginPlay()
{
	Super::BeginPlay();
	//SphereBeginLocation = SphereMeshComp->GetComponentLocation();//��ó�ʼС��λ��
}

// Called every frame
void ASphereBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,SphereMeshComp->CurrentTag->t);//������ʾ������Ϣ

	if (!AngularVector.IsZero())
	{
		FVector NewVector = FVector(0, 0, 0);
		
		NewVector += AngularVector.X  * CameraArmComp->GetForwardVector() * SphereSpeed;
		NewVector += AngularVector.Y  * CameraArmComp->GetRightVector() * SphereSpeed;
		
		SphereMeshComp->SetPhysicsAngularVelocity(NewVector);//С����һ������������ת�ƶ�
	}
	

	{//�����������ת���������С�����ֵܹ�ϵ
		FRotator LRRotation = CameraArmComp->GetComponentRotation();
		//LRCameraRotation.Yaw = FMath::Clamp(LRCameraRotation.Yaw + CameraInput.X, -80.0f, 80.0f);//������ת��Χ
		// *** Root Actor����ת ��ı� -80 ���� 80�ĽǶ�
		LRRotation.Yaw += CameraInput.X;
		CameraArmComp->SetWorldRotation(LRRotation);
	}

	{//����۸���С��
		
		FVector NewLocation = SphereMeshComp->GetComponentLocation();// -SphereBeginLocation;//��ȡС���λ�ñ仯��
		CameraArmComp->SetWorldLocation(NewLocation);
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, NewLocation.ToString());

		/*DrawDebugLine(
			GetWorld(),
			SphereBeginLocation,
			SphereMeshComp->GetComponentLocation(),
			FColor::Red,
			false, -1, 0,
			3.
		);
		DrawDebugPoint(
			GetWorld(),
			CameraArmComp->GetComponentLocation(),
			20,  					//size
			FColor::Green,  //pink
			true,  				//persistent (never goes away)
			0.03 					//point leaves a trail on moving object
		);*/
	}

	 //�����������ת
	{
		FRotator UDRotation = CameraArmComp->GetComponentRotation();
		UDRotation.Pitch = FMath::Clamp(UDRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);//������ת��Χ
		CameraArmComp->SetWorldRotation(UDRotation);
	}//

	{//�������
		ZoomValue = FMath::Clamp<float>(ZoomValue, 0.0f, 1.0f);
		//����ZoomFActor��������������͵��ɱ۵ĳ���
		CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomValue);
		CameraArmComp->TargetArmLength = FMath::Lerp<float>(1500.0f, 500.0f, ZoomValue);//
	}

	{//��Ծ
		if (LinearVector != FVector(0, 0, 0))
		{
			SphereMeshComp->AddForce(LinearVector);
		}
	}
}

// Called to bind functionality to input
void ASphereBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)//pawn��ͬ��actor�ĵط�,���ڰ󶨰���
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASphereBase::MoveForward);//�� ǰ���ƶ�ӳ�� �ĺ���
	PlayerInputComponent->BindAxis("MoveRight", this, &ASphereBase::MoveRight);//������
	PlayerInputComponent->BindAction("MoveQuick", IE_Pressed, this, &ASphereBase::MoveQuick);//��ͬAxis�����������ڰ�������/̧�����
	PlayerInputComponent->BindAction("MoveQuick", IE_Released, this, &ASphereBase::MoveNormal);
	PlayerInputComponent->BindAxis("CameraYaw", this, &ASphereBase::YawCamera);
	PlayerInputComponent->BindAxis("CameraPitch", this, &ASphereBase::PitchCamera);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASphereBase::StartJump);//����Ծ
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASphereBase::StopJump);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ASphereBase::ZoomIn);
	PlayerInputComponent->BindAction("ZoomIn", IE_Released, this, &ASphereBase::ZoomStop);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ASphereBase::ZoomOut);
	PlayerInputComponent->BindAction("ZoomIn", IE_Released, this, &ASphereBase::ZoomStop);
}

//ǰ������
void ASphereBase::MoveForward(float AxisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::SanitizeFloat(val));//������ʾ������Ϣ
	if (IsInput)
	{
#ifdef WORLD_DIRECTION
		AngularVector.Y = SphereSpeed * AxisValue;//��
#else
		AngularVector.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f); //�ڢ�
#endif
	}
}

void ASphereBase::MoveRight(float AxisValue)
{
	if (IsInput)
	{
		AngularVector.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
}

void ASphereBase::MoveQuick()//����Shift��ո���������
{
	SphereSpeed = SpeedMax;
}

void ASphereBase::MoveNormal()
{
	SphereSpeed = SpeedMin;
}
//�����ת
void ASphereBase::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ASphereBase::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}
//��Ծ
void ASphereBase::StartJump()
{
	LinearVector.Z = 1000.0f;
	//bPressedJump = true;  Character����
}

void ASphereBase::StopJump()
{
	LinearVector.Z = 0.f;
}

void ASphereBase::ZoomIn()
{
	ZoomValue += 0.1f;
}

void ASphereBase::ZoomStop()
{
}

void ASphereBase::ZoomOut()
{
	ZoomValue -= 0.1f;
}
