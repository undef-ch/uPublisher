#include "testApp.h"

using namespace boxModel::tools;

//--------------------------------------------------------------
void testApp::setup(){
	Instancer::addInstancer<ofxBox>();
	Instancer::addInstancer<H1>();
	Instancer::addInstancer<TextBox>();


	root = Xml::load<ofxBox>(ofToDataPath("template.xml"));
	
	Xml::loadInto(root, ofToDataPath("content.xml"));
		
	root->loadCss(ofToDataPath("style.css", true));
	root->layouter.layout();
	
	pdf.savePDF("test.pdf", root);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	ofPushMatrix();
	ofScale(2.3, 2.3);
	debugDrawer.draw(root);
	ofPopMatrix();
	
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 30, 30);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	ofExit();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}