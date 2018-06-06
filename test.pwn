// generated by "sampctl package generate"

#include "clothes.inc"

#include <test-boilerplate>


main() {
	new ItemType:item_Clothes		= DefineItemType("Clothes",				"Clothes",			2891,	2,	0.0, 0.0, 0.0,			0.0,	0.269091, 0.166367, 0.000000, 90.000000, 0.000000, 0.000000, .maxhitpoints = 2);

	DefineItemTypeClothes(item_Clothes);

	// male civilian
	DefineClothesType(60,	"Civilian",			GENDER_MALE, 1.0,		true, true);
	DefineClothesType(170,	"Civilian",			GENDER_MALE, 1.0,		true, true);
	DefineClothesType(250,	"Civilian",			GENDER_MALE, 1.0,		true, true);
	DefineClothesType(188,	"Civilian",			GENDER_MALE, 1.0,		true, true);
	DefineClothesType(206,	"Civilian",			GENDER_MALE, 1.0,		true, true);
	DefineClothesType(44,	"Civilian",			GENDER_MALE, 1.0,		true, true);
	DefineClothesType(289,	"Civilian",			GENDER_MALE, 1.0,		false, false);
	// male special
	DefineClothesType(50,	"Mechanic",			GENDER_MALE, 0.6,		true, true);
	DefineClothesType(254,	"Biker",			GENDER_MALE, 0.3,		true, true);
	DefineClothesType(283,	"Cop",				GENDER_MALE, 0.3,		false, false);
	DefineClothesType(287,	"Military",			GENDER_MALE, 0.2,		false, true);
	DefineClothesType(285,	"S.W.A.T.",			GENDER_MALE, 0.1,		false, false);
	DefineClothesType(294,	"Triad",			GENDER_MALE, 0.2,		false, false);
	DefineClothesType(101,	"Southclaws",		GENDER_MALE, 0.1,		true, true);
	DefineClothesType(156,	"Morgan Freeman",	GENDER_MALE, 0.01,	true, true);

	// female civilian
	DefineClothesType(192,	"Civilian",			GENDER_FEMALE, 1.0,		true, true);
	DefineClothesType(93,	"Civilian",			GENDER_FEMALE, 1.0,		true, true);
	DefineClothesType(233,	"Civilian",			GENDER_FEMALE, 1.0,		true, true);
	DefineClothesType(193,	"Civilian",			GENDER_FEMALE, 1.0,		true, true);
	DefineClothesType(90,	"Civilian",			GENDER_FEMALE, 1.0,		false, false);
	DefineClothesType(190,	"Civilian",			GENDER_FEMALE, 1.0,		false, false);
	DefineClothesType(195,	"Civilian",			GENDER_FEMALE, 1.0,		true, true);
	DefineClothesType(41,	"Civilian",			GENDER_FEMALE, 1.0,		false, false);
	// female special
	DefineClothesType(131,	"Indian",			GENDER_FEMALE, 0.6,		true, true);
	DefineClothesType(157,	"Country",			GENDER_FEMALE, 0.7,		false, false);
	DefineClothesType(201,	"Country",			GENDER_FEMALE, 0.7,		false, false);
	DefineClothesType(298,	"Country",			GENDER_FEMALE, 0.6,		false, false);
	DefineClothesType(191,	"Military",			GENDER_FEMALE, 0.2,		true, true);
	DefineClothesType(141,	"Business",			GENDER_FEMALE, 0.1,		false, false);

	CreateItem(item_Clothes, 302.0, 1800.0, 16.5);
	CreateItem(item_Clothes, 302.0, 1801.0, 16.5);
	CreateItem(item_Clothes, 302.0, 1802.0, 16.5);
	CreateItem(item_Clothes, 302.0, 1803.0, 16.5);
	CreateItem(item_Clothes, 302.0, 1804.0, 16.5);
	CreateItem(item_Clothes, 302.0, 1805.0, 16.5);
	CreateItem(item_Clothes, 302.0, 1806.0, 16.5);
	CreateItem(item_Clothes, 302.0, 1807.0, 16.5);
	CreateItem(item_Clothes, 302.0, 1808.0, 16.5);
	CreateItem(item_Clothes, 302.0, 1809.0, 16.5);
}

public OnPlayerSpawn(playerid) {
	SetPlayerClothes(playerid, ClothesType:0);
}
