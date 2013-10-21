#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    //-------------------------
    // We can change translate mode.
    // Choose OFX_GEO_JSON_MERCATROE mode or OFX_GEO_JSON_EQUIRECTANGULAR mode. Default is OFX_GEO_JSON_MERCATROE.
    //-------------------------
    
    geojson.setMode(OFX_GEO_JSON_MERCATROE);
    
    //-------------------------
    // Set scale and translate
    //-------------------------

    geojson.setScale(250.0);
    geojson.setTranslate(0, 0);
    
    //-------------------------
    // Load GeoJSON file from project's data path.
    // If it's loaded ofxGeoJSON makes ofMesh's vector array in this transcation.
    //-------------------------
    
    if (geojson.load("countries.geo.json")) {
        ofLog(OF_LOG_NOTICE, "Succeed to load geojson..");
    } else {
        ofLog(OF_LOG_NOTICE, "Fale to load geojson..");
    };

    //set the camera
    cam.setAutoDistance(true);
    cam.setNearClip(0.01);
    cam.setFarClip(100000);
    cam.setFov(45);
    cam.setDistance(500);

}

//--------------------------------------------------------------
void testApp::update(){
    cam.lookAt(ofVec3f(0,0,0));
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255, 255, 255);
    cam.begin();
    
    ///-------------------------
    // draw mashes
    //-------------------------
    
    geojson.draw();
    
    cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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
