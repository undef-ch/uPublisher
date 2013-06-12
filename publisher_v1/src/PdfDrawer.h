#ifndef PDFDRAWER_H
#define PDFDRAWER_H

#include "ofxBox.h"
#include "ofxLibharu.h"
#include "components/Text.h"
#include "Style.h"


using namespace boxModel::core;
using namespace boxModel::components;

class pdfDrawer
{
public:
	pdfDrawer();
	~pdfDrawer();
	
	void savePDF(string path,ComponentContainer* container);
	void drawIntoPDF(ComponentContainer* container);
	
	void drawBox(Box* box);
	void drawText(Box* box, Text* text, Color fg);
	
	void onGetBoxHeight(float& height, Text* info);
	
	ofxLibharu pdf;
	Color color;

};

#endif // PDFDRAWER_H
