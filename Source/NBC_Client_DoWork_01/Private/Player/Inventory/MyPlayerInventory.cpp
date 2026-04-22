#include "NBC_Client_DoWork_01/Public/Player/Inventory/MyPlayerInventory.h"

#include "Player/MyPlayer.h"
#include "Player/Controller/MyPlayerControlloer.h"
#include "UObject/FastReferenceCollector.h"


UMyPlayerInventory::UMyPlayerInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	InventoryCapacity = 30;
	
	Inventory.SetNum(InventoryCapacity);
}

void UMyPlayerInventory::BeginPlay()
{
	Super::BeginPlay();
	
	if (ItemDataTable)
	{
		static const FString ContextString = "DataTableSearch";
		TArray<FItemDataTable*> TempRowArray;
		ItemDataTable->GetAllRows(ContextString,TempRowArray);
		for (int32 i = 0; i < TempRowArray.Num(); i++)
		{
			ItemInfo.Add(TempRowArray[i]->ItemName, TempRowArray[i]->ItemDescription);
		}
	}
	
	for (auto i : ItemInfo)
	{
		UE_LOG(LogTemp,Warning,TEXT("Map Key : %s | Value : %s"),*i.Key.ToString(), *i.Value.ToString());
	}
}

void UMyPlayerInventory::AddInventoryItem(FName ItemName)
{
	if (!ItemDataTable) return;
	
	FItemDataTable* EmptySlot = Inventory.FindByPredicate([](const FItemDataTable& Item){return Item.ItemName.IsNone();});
	if (!EmptySlot)
	{
		UE_LOG(LogTemp,Warning,TEXT("인벤토리 가득참"));
		return;
	}
	
	
	if (Inventory.Num() <= InventoryCapacity)
	{
		for (int32 i = 0; i < Inventory.Num(); i++)
		{
			UE_LOG(LogTemp,Warning,TEXT("Index %d : ItemName is %s"),i, *Inventory[i].ItemName.ToString());
			if (Inventory[i].ItemName.IsNone())
			{
				UE_LOG(LogTemp,Warning,TEXT("AddInventory"));
				Inventory[i] = *FindItemFromDataTable(ItemDataTable,ItemName);
				break;
			}
		}
	}
	
	if (AMyPlayerControlloer* PC  = Cast<AMyPlayerControlloer>(GetOwner()->GetInstigatorController()))
	{
		PC->GetInventoryWidget()->UpdateInventoryItem(this);
	}
}

FItemDataTable* UMyPlayerInventory::FindItemFromDataTable(UDataTable* DataTable,FName ItemName)
{
	static const FString ContextString = "DataTableSearch";
	
	if (DataTable)
	{
		FItemDataTable* FindRow = DataTable->FindRow<FItemDataTable>(ItemName, ContextString);
		return FindRow;
	}
	return nullptr;
}

void UMyPlayerInventory::DeleteItemFromInventory(int32 index)
{
	if (Inventory.IsValidIndex(index))
	{
		UE_LOG(LogTemp,Warning,TEXT("인벤토리 배열 삭제 완료!!"));
		Inventory[index] = FItemDataTable();
	}
}

bool UMyPlayerInventory::UseItem(int32 index)
{
	if (!Inventory.IsValidIndex(index))
	{
		UE_LOG(LogTemp,Warning,TEXT("해당 인벤토리 [%d]에는 아이템이 존재하지 않습니다!!"),index);
		return false;
	}

	AMyPlayer* MyPlayer = Cast<AMyPlayer>(GetOwner());
	
	
	if (!MyPlayer) return false;
	
	if (!MyPlayer->GetPlayerTitle().Contains(EPlayer_Title::Newbie))
	{
		if (Inventory[index].ItemName == "Gold")
		{
			UEnum* Enumptr = StaticEnum<EPlayer_Title>();
			if (Enumptr)
			{
				FString EnumToString = Enumptr->GetNameStringByValue(static_cast<int64>(EPlayer_Title::Newbie));
				UE_LOG(LogTemp,Warning,TEXT("해당 아이템은 %s 칭호가 있어야 사용 가능합니다."),*EnumToString);
			}
			return false;
		}
	}
	if (!MyPlayer->GetPlayerTitle().Contains(EPlayer_Title::Magician))
	{
		if (Inventory[index].ItemName == "MagicBook")
		{
			UEnum* Enumptr = StaticEnum<EPlayer_Title>();
			if (Enumptr)
			{
				FString EnumToString = Enumptr->GetNameStringByValue(static_cast<int64>(EPlayer_Title::Magician));
				UE_LOG(LogTemp,Warning,TEXT("해당 아이템은 %s 칭호가 있어야 사용 가능합니다."),*EnumToString);
			}
			return false;
		}
	}
	if (!MyPlayer->GetPlayerTitle().Contains(EPlayer_Title::Warrior))
	{
		if (Inventory[index].ItemName == "Sword")
		{
			UEnum* Enumptr = StaticEnum<EPlayer_Title>();
			if (Enumptr)
			{
				FString EnumToString = Enumptr->GetNameStringByValue(static_cast<int64>(EPlayer_Title::Warrior));
				UE_LOG(LogTemp,Warning,TEXT("해당 아이템은 %s 칭호가 있어야 사용 가능합니다."),*EnumToString);
			}
			return false;
		}
	}
	if (!MyPlayer->GetPlayerTitle().Contains(EPlayer_Title::Priest))
	{
		if (Inventory[index].ItemName == "Potion")
		{
			UEnum* Enumptr = StaticEnum<EPlayer_Title>();
			if (Enumptr)
			{
				FString EnumToString = Enumptr->GetNameStringByValue(static_cast<int64>(EPlayer_Title::Priest));
				UE_LOG(LogTemp,Warning,TEXT("해당 아이템은 %s 칭호가 있어야 사용 가능합니다."),*EnumToString);
			}
			return false;
		}
	}
	
	UE_LOG(LogTemp,Warning,TEXT("아이템 사용 완료!!"));
	DeleteItemFromInventory(index);
	return true;
}





