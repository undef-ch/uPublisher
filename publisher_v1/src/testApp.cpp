#include "testApp.h"

using namespace boxModel::components;
using namespace boxModel::core;

//--------------------------------------------------------------
void testApp::setup(){
	
	Layouter::autoLayout = false;
	
	root.setId("root");
	
	root.width = 210;
	root.height = 297;
	
	for(unsigned int i = 0; i<10; i++) {

		TextBox* b = new TextBox();
		string text = "box Nr."+ofToString(i)+ "\nLorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
		
		//b->text = "Box Nr. "+ofToString(i)+"\nLorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
		
		b->text = text.substr (0,(int)ofRandom(text.size()));
		b->addClass("outerBox");
		
		
		int amount = ofRandom(2, 90);
		
		for(int j=0; j<amount; j++) {
			TextBox* b2 = new TextBox();
			b2->addClass("innerBox");
			b2->text = ofToString(j);
			b->addChild(b2);
		}
		
		root.addChild(b);		
	}
	
	root.loadCss(ofToDataPath("style.css", true));
	
	root.layouter.layout(true);
		
	pdf.savePDF("test.pdf", &root);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	debugDrawer.draw(&root);
	
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