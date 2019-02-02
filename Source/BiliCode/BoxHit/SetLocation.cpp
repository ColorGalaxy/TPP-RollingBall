// Fill out your copyright notice in the Description page of Project Settings.

#include "SetLocation.h"
#include "Player/SphereBase.h"
#include "GameMode/BiliCodeGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"


ASetLocation::ASetLocation()
{
	SetMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SetMesh"));//���캯���г�ʼ��ģ��
	HitBoxComp->SetupAttachment(SetMeshComp);//��ײ�и���������Ϊģ��Mesh  ���ƫ��������
}
void ASetLocation::OnHitSphere(AActor * sphere)
{
	ABiliCodeGameModeBase * GameModeBase = Cast<ABiliCodeGameModeBase>(GetWorld()->GetAuthGameMode());
	GameModeBase->SetStartPosition(HitBoxComp->GetComponentLocation());//��ײʱ���ݼ̳е���ײ�У���������꣩������

	//FVector NewLocation = sphere->GetActorLocation();
	// ʵ��������
	//// Spawn the new actor (Using GetClass() instead of AMySpawner so that if someone derives a new class  
	//// from AMySpawner we spawn an instance of that class instead)  
	//ASphereBase* NewActor = GetWorld()->SpawnActor<ASphereBase>(sphere->GetClass(), NewLocation, FRotator::ZeroRotator);
}



