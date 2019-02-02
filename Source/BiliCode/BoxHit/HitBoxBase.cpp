// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxHit/HitBoxBase.h"
#include "Components/BoxComponent.h"
#include "Player/SphereBase.h"//�ж���ײ�Ƿ���С��

// Sets default values
AHitBoxBase::AHitBoxBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxComp"));//��ʼ�����
	HitBoxComp-> OnComponentBeginOverlap.AddDynamic(this, &AHitBoxBase::BeginHit);//������ͼBeginOverLap
}

// Called when the game starts or when spawned
void AHitBoxBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitBoxBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//BeginOverLap��ͼ���кܶ�������󶨺��������
//UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult
void AHitBoxBase::BeginHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//�ж���ײ�Ƿ�ΪС��
	//����ת��Cast<ת������>(ת������)
	if (Cast<ASphereBase>(OtherActor))
	{ 
		OnHitSphere(Cast<ASphereBase>(OtherActor));
	}
}

void AHitBoxBase::OnHitSphere(AActor * sphere)
{
}

