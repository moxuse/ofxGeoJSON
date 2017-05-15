#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
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
        ofLog(OF_LOG_NOTICE, "Failed to load geojson..");
    };

    //set the camera
    cam.setAutoDistance(true);
    cam.setNearClip(0.01);
    cam.setFarClip(100000);
    cam.setFov(45);
    cam.setDistance(500);

}

//--------------------------------------------------------------
void ofApp::update(){
    cam.lookAt(ofVec3f(0,0,0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    cam.begin();
    
    
    //-------------------------
    // draw mashes
    //-------------------------
    
    geojson.draw();
    
    
    
    //-------------------------
    // get meshes of feature
    //-------------------------
    
    vector< ofPtr<ofMesh> > japan = geojson.getFeature("Japan");
    
    for (int i = 0; i<japan.size(); i++) {
        int size = japan[i].get()->getNumColors();
        for (int j = 0; j < size; j++) {
            japan[i].get()->setColor(j, ofColor(255.0,0.0,0.0));
        }
    };
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
