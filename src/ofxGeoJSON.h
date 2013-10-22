//
//  ofxGeoJSON.h
//  example-loading
//
//  Created by Koichiro Mori on 2013/10/21.
//
//

#ifndef __example_loading__ofxGeoJSON__
#define __example_loading__ofxGeoJSON__

#include <iostream>
#include "ofMain.h"
#include "ofxJSONElement.h"

typedef struct Coodinate {
    float latitude;
    float longtitude;
} COORDINATE;

enum ofx_geo_json_mode {
    OFX_GEO_JSON_MERCATROE = 0,
    OFX_GEO_JSON_EQUIRECTANGULAR = 1,
    OFX_GEO_JSON_AZIMUTHAL_EQUALAREA = 2,
    OFX_GEO_JSON_STEREOGRAPHIC = 3
};

class ofxGeoJSON {
public:
    ofxGeoJSON();
    bool load(string _path);
    ofPoint mercator(Coodinate _coordinate);
    ofPoint equirectangular(Coodinate _coordinate);
    ofPoint azimuthal(Coodinate _coordinate);
    void setMode(ofx_geo_json_mode _mode);
    void setScale(float scale);
    void setTranslate(float _transelateX, float _transelateY);
    void draw();
    ofMesh* getMesh();
    
private:
    ofx_geo_json_mode mode;
    float scale;
    float translateX;
    float translateY;
    float pvRadians(float degrees);
    vector<ofMesh> meshes;
    ofxJSONElement result;
};

#endif
