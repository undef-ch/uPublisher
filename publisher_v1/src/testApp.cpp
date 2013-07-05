#include "testApp.h"
#include "Globals.h"
#include "components/Text.h"

using namespace boxModel::tools;
using namespace boxModel::core;
using namespace boxModel::debug;

struct headerPos {
	int pageNumber;
	std::string text;
};

//--------------------------------------------------------------
void testApp::setup() {

//	cout << (u1.getType() == Unit::Auto) << endl;
	
	//settings
	Globals::get().dataRoot = ofToDataPath("", true);
	boxModel::components::Text::enableHyphenation("de");

	root.setId("root");
	root.loadCss("appStyle.css");

	//
	Instancer::addInstancer<ofxBox>();
	Instancer::addInstancer<H1>();
	Instancer::addInstancer<TextBox>();

	templater.setTemplate("template.xml");

	pages = templater.loadContent<ofxBox>("content.xml", "#column1");
	
	//CREATE INDEX
	int curPage = 0;
	std::vector<headerPos> headersPos;
	for(ofxBox* box: pages) {
		ofxBox* page = box;
		std::vector<H1*> headers = page->findByAddress<H1>("h1");
		for(H1* header: headers) {
			H1* h1 = header;
			headerPos hp;
			hp.pageNumber = curPage;
			hp.text = h1->text;
			headersPos.push_back(hp);
		}
		curPage++;
	}
	
	ofxBox* indexPage = new ofxBox();
	indexPage->addClass("page");
	indexPage->addClass("index");
	indexPage->loadCss("contentStyle.css");
	
	for(headerPos hp:headersPos){
		H1* header = new H1();
		header->text =  ofToString(hp.pageNumber+2) + "           " + hp.text ;
		indexPage->addChild(header);
	}
	
	indexPage->flush();
	//end index
	
	int pageNumber = 2;
	for(ofxBox* page:pages) {
		ofxBox* p = page;
		TextBox* footer = p->findByAddress<TextBox>("#footer p")[0];
		footer->text = ofToString(pageNumber);
		pageNumber++;
	}
	
	pages.insert(pages.begin(), indexPage);

	pdf.savePDF("test.pdf", pages);

	for(ofxBox* page:pages) {
		root.addChild(page);
	}
	
	root.width = Unit::Pixel;
	root.width = ofGetWidth();
	root.height = ofGetHeight();

	root.flush();
}

//--------------------------------------------------------------
void testApp::update() {
}

//--------------------------------------------------------------
void testApp::draw() {
	ofPushMatrix();
	debugDrawer.draw(&root);
	ofPopMatrix();

	//ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	ofExit();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
	root.width = ofGetWidth();
	root.height = ofGetHeight();
	root.flush();
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}
