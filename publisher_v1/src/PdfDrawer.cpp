#include "PdfDrawer.h"


pdfDrawer::pdfDrawer() {

	pdf.setup();
	Text::onGetTextBoxHeight.connect<pdfDrawer,&pdfDrawer::onGetBoxHeight>(this);
	color = Color(0);
}

pdfDrawer::~pdfDrawer() {
}

void pdfDrawer::savePDF(string path,ComponentContainer* container) {

	if(!container->hasComponent<Box>()) return;

	Box* b = container->getComponent<Box>();
	pdf.setPageSize(b->size.x,b->size.y);

	pdf.setFillType(OF_OUTLINE);
	pdf.setLineWidth(.1);

	drawIntoPDF(container);

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

	string fontName = text->fontName.get();
	if(ofIsStringInString(fontName,".ttf")) pdf.setFont(ofToDataPath(fontName));
	else pdf.setFont(fontName);

	pdf.setTextAlignment((ofxLibharu::TEXT_ALIGNMENT)text->textAlignment);
	pdf.setFontSize(text->fontSize.getValueCalculated());
	pdf.setTextLeading(text->leading.getValueCalculated());
	pdf.setFillColor(fg.r,fg.g,fg.b);
	pdf.setCharSpacing(text->letterSpacing.getValueCalculated());
	pdf.setWordSpacing(text->wordSpacing.getValueCalculated());

	pdf.drawTextBox(text->text, pos.x, pos.y, box->contentSize.x,box->contentSize.y);

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
	bool drawBorderTop = true, drawBorderLeft = true, drawBorderRight = true, drawBorderBottom = true;
	float borderTopWidth=1, borderLeftWidth=1, borderBottomWidth=1, borderRightWidth=1;

	BoxDefinition* boxDef;
	if(box->components->hasComponent<BoxDefinition>()) {
		boxDef = box->components->getComponent<BoxDefinition>();
		if(boxDef->border.top.getType()==Unit::Type_None) drawBorderTop = false;
		if(boxDef->border.left.getType()==Unit::Type_None) drawBorderLeft = false;
		if(boxDef->border.right.getType()==Unit::Type_None) drawBorderRight = false;
		if(boxDef->border.bottom.getType()==Unit::Type_None) drawBorderBottom = false;

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
	//---> lineWidth
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

void pdfDrawer::onGetBoxHeight(float& height, Text* info) {
	Box* box = info->components->getComponent<Box>();

	//cout << box->contentSize.x << " " << " " << info->fontName.get() << " " << info->fontSize << " " << info->leading<< " " << info->letterSpacing << " " << info->wordSpacing << endl;

	string fontName = info->fontName;
	if(ofIsStringInString(fontName,".ttf")) fontName = ofToDataPath(info->fontName);

	height = pdf.getTextBoxHeight(box->contentSize.x, info->text, fontName, info->fontSize, info->leading, info->letterSpacing, info->wordSpacing);

}
