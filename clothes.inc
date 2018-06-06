// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_clothes
	#undef _inc_clothes
#endif
// custom include-guard to ensure we don't duplicate
#if defined _clothes_included
	#endinput
#endif
#define _clothes_included


#include <a_samp>
#include <item>
#include <item-array-data>
#include <hold-action>
#include <YSI\y_hooks>


// MAX_CLOTHES_TYPES Controls the maximum amount of clothes that can be defined.
#if !defined MAX_CLOTHES_TYPES
	#define MAX_CLOTHES_TYPES (ClothesType:32)
#endif

// MAX_SKIN_NAME contorls the maximum length for the name of a clothes type.
#if !defined MAX_SKIN_NAME
	#define MAX_SKIN_NAME (32)
#endif


enum E_GENDER {
	GENDER_NEUTRAL,
	GENDER_MALE,
	GENDER_FEMALE,
}

enum E_SKIN_DATA
{
	skin_model,
	skin_name[MAX_SKIN_NAME],
	E_GENDER:skin_gender,
	Float:skin_lootSpawnChance,
	skin_canWearHats,
	skin_canWearMasks
}


static
	ItemType:skin_ItemType,
	skin_Total,
	skin_Data[MAX_CLOTHES_TYPES][E_SKIN_DATA],
	ClothesType:skin_CurrentClothes[MAX_PLAYERS],
	skin_CurrentlyUsing[MAX_PLAYERS];


// -
// API
// -


DefineItemTypeClothes(ItemType:itemtype) {
	SetItemTypeMaxArrayData(itemtype, 1);
	skin_ItemType = itemtype;
}

ClothesType:DefineClothesType(modelid, name[MAX_SKIN_NAME], E_GENDER:gender, Float:spawnchance, bool:wearhats, bool:wearmasks) {
	new ClothesType:id = ClothesType:skin_Total++;
	skin_Data[id][skin_model] = modelid;
	skin_Data[id][skin_name] = name;
	skin_Data[id][skin_gender] = gender;
	skin_Data[id][skin_lootSpawnChance] = spawnchance;
	skin_Data[id][skin_canWearHats] = wearhats;
	skin_Data[id][skin_canWearMasks] = wearmasks;
	return id;
}

stock IsValidClothes(ClothesType:skinid) {
	if(!(ClothesType:0 <= skinid < ClothesType:skin_Total)) {
		return 0;
	}

	return 1;
}

stock GetPlayerClothes(playerid, &clothes) {
	if(!(0 <= playerid < MAX_PLAYERS)) {
		return 1;
	}

	clothes = skin_CurrentClothes[playerid];
	return 0;
}

stock SetPlayerClothes(playerid, ClothesType:clothesType) {
	if(!IsValidClothes(clothesType)) {
		return 1;
	}

	SetPlayerSkin(playerid, skin_Data[clothesType][skin_model]);
	skin_CurrentClothes[playerid] = clothesType;

	return 0;
}

stock GetClothesModel(skinid, &model) {
	if(!IsValidClothes(clothesType)) {
		return 1;
	}

	model = skin_Data[skinid][skin_model];
	return 0;
}

stock GetClothesName(skinid, name[]) {
	if(!IsValidClothes(clothesType)) {
		return 1;
	}

	name[0] = EOS;
	strcat(name, skin_Data[skinid][skin_name], MAX_SKIN_NAME);

	return 0;
}

stock GetClothesGender(skinid, &E_GENDER:gender) {
	if(!IsValidClothes(clothesType)) {
		return 1;
	}

	gender = skin_Data[skinid][skin_gender];
	return 0;
}

stock GetClothesHatStatus(skinid, &bool:allowed) {
	if(!IsValidClothes(clothesType)) {
		return 1;
	}

	allowed = skin_Data[skinid][skin_canWearHats];
	return 0;
}

stock GetClothesMaskStatus(skinid, &bool:allowed) {
	if(!IsValidClothes(clothesType)) {
		return 1;
	}

	allowed = skin_Data[skinid][skin_canWearMasks];
	return 0;
}


// -
// Internal
// -


hook OnPlayerConnect(playerid) {
	skin_CurrentlyUsing[playerid] = INVALID_ITEM_ID;
}

hook OnItemCreate(itemid) {
	if(GetItemType(itemid) == skin_ItemType) {
		new
			list[MAX_CLOTHES_TYPES],
			idx;

		for(new i; i < skin_Total; i++) {
			if(frandom(1.0) < skin_Data[ClothesType:i][skin_lootSpawnChance]) {
				list[ClothesType:idx++] = i;
			}
		}

		if(idx == 0) {
			idx = 1;
		}

		SetItemArrayDataLength(itemid, 1);
		SetItemArrayDataAtCell(itemid, list[ClothesType:random(idx)], 0);
	}

	return 1;
}

hook OnItemNameRender(itemid, ItemType:itemtype) {
	if(itemtype == skin_ItemType) {
		new
			exname[32],
			ClothesType:clothesType;

		GetItemArrayDataAtCell(itemid, 0, _:clothesType);

		if(skin_Data[clothesType][skin_gender] == GENDER_MALE) {
			strcat(exname, "Male ");
		} else {
			strcat(exname, "Female ");
		}

		strcat(exname, skin_Data[clothesType][skin_name]);

		SetItemNameExtra(itemid, exname);
	}

	return Y_HOOKS_CONTINUE_RETURN_0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(newkeys == 16) {
		new itemid = GetPlayerItem(playerid);

		if(GetItemType(itemid) == skin_ItemType) {
			_clothes_start(playerid, itemid);
		}
	}

	if(oldkeys == 16) {
		if(skin_CurrentlyUsing[playerid] != INVALID_ITEM_ID) {
			_clothes_stop(playerid);
		}
	}

	return 1;
}

_clothes_start(playerid, itemid) {
	StartHoldAction(playerid, 3000);
	ClearAnimations(playerid);
	skin_CurrentlyUsing[playerid] = itemid;
}

_clothes_stop(playerid) {
	if(skin_CurrentlyUsing[playerid] != INVALID_ITEM_ID) {
		StopHoldAction(playerid);
		ClearAnimations(playerid);
		skin_CurrentlyUsing[playerid] = INVALID_ITEM_ID;
	}
}

hook OnHoldActionFinish(playerid) {
	if(skin_CurrentlyUsing[playerid] != INVALID_ITEM_ID) {
		new
			ClothesType:currentclothes = skin_CurrentClothes[playerid],
			ClothesType:newClothes;

		GetItemArrayDataAtCell(skin_CurrentlyUsing[playerid], 0, _:newClothes);
		SetPlayerClothes(playerid, newClothes);
		SetItemArrayDataAtCell(skin_CurrentlyUsing[playerid], _:currentclothes, 0);
		_clothes_stop(playerid);

		return Y_HOOKS_BREAK_RETURN_1;
	}

	return Y_HOOKS_CONTINUE_RETURN_0;
}
