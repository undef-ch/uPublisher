#pragma once

#include "ofMain.h"
#include "ofxBox.h"
#include "PdfDrawer.h"
#include "debug/DebugDrawer.h"
#include "components/Text.h"
#include "tools/Instancer.h"
#include "tools/Xml.h"
#include "tools/Templater.h"


class TextBox: public ofxBox, public boxModel::components::Text{
public:
	TextBox(){
		addComponent<Text>(this);
		width = boxModel::core::Unit::Percent;
		width = 100;
	}
	
	virtual string getType(){
		return "p";
	}
};

class H1: public TextBox{
public:
	H1(){
	}
	
	string getType(){
		return "h1";
	}
};

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxBox root;
		std::vector<ofxBox*> pages;
		pdfDrawer pdf;
		boxModel::debug::DebugDrawer debugDrawer;
		
		boxModel::tools::Templater templater;
		
};
