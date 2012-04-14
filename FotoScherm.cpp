/*
 * FotoScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer, Marijn
 */

#include "FotoScherm.h"

// variabelen voor schermgrootte
int screenWidth;
int screenHeight;

FotoScherm::FotoScherm()
{
	//het optiescherm
	this->optieScherm = new OptieScherm( this );

	//bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	screenWidth = EXTENT_X( screenSize );
	screenHeight = EXTENT_Y( screenSize );

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	achtergrondLabel = new Label(0, 0, 0, 0, NULL);
	achtergrondLabel->setBackgroundColor(0xd3d3d3);

	//maak een plaatje (laden uit de resource file res.lst) en voeg label als parent toe
	this->image = new Image( (screenWidth / 2) - (176 / 2), (screenHeight / 2) - (153 / 2), 176, 153, achtergrondLabel, false, false, RES_IMAGE );

	//maak tekst bij het plaatje met een label
	this->imageTekst = new Label( (screenWidth / 2) - (176 / 2), 250, 176, 30, achtergrondLabel, "Onderwater spoorlijn ", 0, font );
	this->imageTekst->setPaddingLeft(5);
	this->imageTekst->setPaddingTop(5);
	this->imageTekst->setSkin(skin);

	//stel dit scherm in als het main scherm, met achtergrondlabel als de basis widget
	this->setMain( this->achtergrondLabel );
}

FotoScherm::~FotoScherm()
{

}

//show() override de show() van de super klasse (Screen), omdat we bij showen eerst opties willen ophalen
void FotoScherm::show()
{
	//roep de show() van de superklasse (Screen) aan
	this->Screen::show();

	//haal informatie achtergrondkleur op van optiescherm
	this->achtergrondLabel->setBackgroundColor( this->optieScherm->getAchtergrondOptie() );

	// haal de imageTekst op
	this->imageTekst->setCaption( this->optieScherm->getImagetekst() );

	// haal grootte van plaatje op en pas formaat plaatje aan
	this->image->setWidth(this->optieScherm->getGrootte());
	this->image->setHeight(this->optieScherm->getGrootte());
}

//afvangen toetsinvoer
void FotoScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//bij indrukken van de MAK_FIRE toets, laat optiescherm zien
	if (keyCode == MAK_FIRE)
	{
		optieScherm->show();
	}
}

//afvangen aanraking
void FotoScherm::pointerPressEvent(MAPoint2d point)
{
	//bij touch, laat optiescherm zien
	optieScherm->show();
}

