#ifndef PDFDRAWER_H
#define PDFDRAWER_H

#include "ofxBox.h"
#include "ofxLibharu.h"
#include "components/Text.h"
#include "Style.h"
#include "TextBlockDrawer.h"

class pdfDrawer: public cppFont::TextBlockDrawer
{
public:
	pdfDrawer();
	~pdfDrawer();
	
	void savePDF(string path, boxModel::core::ComponentContainer* container);
	void drawIntoPDF(boxModel::core::ComponentContainer* container);
	
	void drawBox(boxModel::components::Box* box);
	void drawText(boxModel::components::Box* box, boxModel::components::Text* text, boxModel::core::Color fg);
	
	void onGetBoxHeight(float& height, boxModel::components::Text* info);
	
	ofxLibharu pdf;
	boxModel::core::Color color;

	//for font rendering
	void setFont(cppFont::Font* font, int fontSize);
	void drawCharacter(cppFont::Letter& letter);
	void drawRect(float x, float y, float width, float height);
	void drawLine(float x, float y, float x2, float y2);
};

#endif // PDFDRAWER_H
