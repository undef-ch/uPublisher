#include "PdfDrawer.h"

using namespace boxModel::components;
using namespace boxModel::core;

pdfDrawer::pdfDrawer() {
	//Text::onGetTextBoxHeight.connect<pdfDrawer,&pdfDrawer::onGetBoxHeight>(this);
	color = Color(0);
}

pdfDrawer::~pdfDrawer() {
}

void pdfDrawer::savePDF(string path, ofxBox* containers) {
	std::vector<ofxBox*> comps;
	comps.push_back(containers);
	savePDF(path, comps);
}

void pdfDrawer::savePDF(string path, std::vector<ofxBox*> containers) {
	pdf.setup();
	for(ofxBox* comp:containers){
		if(comp->hasComponent<Box>()){
			Box* b = comp->getComponent<Box>();
			pdf.setPageSize(b->size.x, b->size.y);
		}
		pdf.setFillType(OF_OUTLINE);
		pdf.setLineWidth(.1);
		
		drawIntoPDF(comp);
		if(comp != containers.back()){
			pdf.newPage(210, 297);
		}
	}
	
	pdf.save(path, true);
	pdf.openLastSave();
}

void pdfDrawer::drawIntoPDF(ComponentContainer* container) {

	if(container->hasComponent<Box>()) {
		Box* box = container->getComponent<Box>();
		drawBox(box);

		if(container->hasComponent<Text>()) {

			Color col = color;
			if(container->hasComponent<Style>()) {
				Style* style = container->getComponent<Style>();
				col = style->getColor();
			}

			Text* text = container->getComponent<Text>();
			drawText(box, text, col);
		}
	}

	if(container->hasComponent<Stack>()) {
		Stack* stack = container->getComponent<Stack>();
		for(Stack* stackChild: stack->getChildren()) {
			drawIntoPDF(stackChild->components);
		}
	}
}

void pdfDrawer::drawText(Box* box, Text* text, Color fg) {
	
	Point pos = box->getGlobalPosition() + box->contentPosition;
	curTextOffset.set(pos.x, pos.y);
	//pdf.pushMatrix();
	//pdf.translate(pos.x, pos.y);
	pdf.setFillColor(fg.r, fg.g, fg.b);
	pdf.beginText();
	text->getTextBlock().draw(this);
	pdf.endText();
	//pdf.popMatrix();
}

void pdfDrawer::drawBox(Box* box) {
	
	//
	Style* style;
	if(box->components->hasComponent<Style>()) {
		style = box->components->getComponent<Style>();
	} else {
		style = new Style();
		style->setBgColor(Color(255));
		style->setBorderColor(Color(0));
		style->setColor(color);
	}

	Color color = style->getColor();
	Color bgcol = style->getBgColor();
	Color brdcol = style->getBorderColor();

	//draw fill
	if(style->hasBgColor()) {
		pdf.setFillType(OF_FILLED);
		pdf.setFillColor(bgcol.r,bgcol.g,bgcol.b);
		pdf.drawRectangle(box->getGlobalPosition().x,box->getGlobalPosition().y,box->size.x, box->size.y);
	}

	//
	bool drawBorderTop = false, drawBorderLeft = false, drawBorderRight = false, drawBorderBottom = false;
	float borderTopWidth, borderLeftWidth, borderBottomWidth, borderRightWidth;

	BoxDefinition* boxDef;
	if(box->components->hasComponent<BoxDefinition>()) {
		boxDef = box->components->getComponent<BoxDefinition>();
		if(boxDef->border.top.getType()==Unit::Type_None) drawBorderTop = false;
		else drawBorderTop = true;
		if(boxDef->border.left.getType()==Unit::Type_None) drawBorderLeft = false;
		else drawBorderLeft = true;
		if(boxDef->border.right.getType()==Unit::Type_None) drawBorderRight = false;
		else drawBorderRight = true;
		if(boxDef->border.bottom.getType()==Unit::Type_None) drawBorderBottom = false;
		else drawBorderBottom = true;

		borderTopWidth = boxDef->border.top.getValueCalculated();
		borderLeftWidth = boxDef->border.left.getValueCalculated();
		borderBottomWidth = boxDef->border.bottom.getValueCalculated();
		borderRightWidth = boxDef->border.right.getValueCalculated();
	}

	//draw borders
	pdf.setFillType(OF_OUTLINE);
	pdf.setStrokeColor(brdcol.r,brdcol.g,brdcol.b);

	ofRectangle rect(box->getGlobalPosition().x+borderLeftWidth*.5,box->getGlobalPosition().y+borderTopWidth*.5,
	                 box->size.x-borderRightWidth*.5-borderLeftWidth*.5, box->size.y-borderBottomWidth*.5-borderTopWidth*.5);
	if(drawBorderTop) {
		pdf.setLineWidth(borderTopWidth);
		pdf.drawLine(rect.getTopLeft().x-borderLeftWidth*.5,rect.getTopLeft().y,rect.getTopRight().x+borderRightWidth*.5,rect.getTopRight().y);
	}
	if(drawBorderLeft) {
		pdf.setLineWidth(borderLeftWidth);
		pdf.drawLine(rect.getTopLeft().x,rect.getTopLeft().y-borderTopWidth*.5,rect.getBottomLeft().x,rect.getBottomLeft().y+borderBottomWidth*.5);
	}
	if(drawBorderRight) {
		pdf.setLineWidth(borderRightWidth);
		pdf.drawLine(rect.getTopRight().x,rect.getTopRight().y-borderTopWidth*.5,rect.getBottomRight().x,rect.getBottomRight().y+borderBottomWidth*.5);
	}
	if(drawBorderBottom) {
		pdf.setLineWidth(borderBottomWidth);
		pdf.drawLine(rect.getBottomLeft().x-borderLeftWidth*.5,rect.getBottomLeft().y,rect.getBottomRight().x+borderRightWidth*.5,rect.getBottomRight().y);
	}
	/*
	pdf.setFillType(OF_FILLED);
	pdf.setFillColor(0, 255, 0);
	pdf.drawRectangle(rect.x, rect.y, rect.width, rect.height);
	*/
}

void pdfDrawer::setFont(cppFont::Font* font, int fontSize){
	pdf.setFont(font->filePath);
	pdf.setFontSize(fontSize*1.4);
}

void pdfDrawer::drawCharacter(cppFont::Letter& letter){
	
	//std::string str = "";
	//str += letter.character;
	//pdf.drawText(str, letter.x, letter.y);
	pdf.drawChar(letter.character, letter.x + curTextOffset.x, (letter.y + letter.size*.065) + curTextOffset.y);
}

void pdfDrawer::drawRect(float x, float y, float width, float height){
	pdf.drawRectangle(x,y,width,height);
}

void pdfDrawer::drawLine(float x, float y, float x2, float y2){
	pdf.drawLine(x,y,x2,y2);
}

