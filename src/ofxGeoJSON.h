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

typedef struct Coordinate {
    float latitude;
    float longtitude;
} COORDINATE;

enum ofx_geo_json_mode {
    OFX_GEO_JSON_MERCATROE = 0,
    OFX_GEO_JSON_EQUIRECTANGULAR,
    OFX_GEO_JSON_AZIMUTHAL_EQUALAREA,
    OFX_GEO_JSON_STEREOGRAPHIC,
    OFX_GEO_JSON_SPHERICAL,
};

class ofxGeoJSONFeature : public ofNode {
public:
    vector< ofPtr<ofMesh> > meshes;
    string name;
};

class ofxGeoJSON {
public:
    ofxGeoJSON();
    virtual ~ofxGeoJSON() {
        map<string, ofxGeoJSONFeature>::iterator it = features.begin();
        while( it != features.end() ) {
            features.erase (it++);
        }
    };
    bool load(string _path);
    ofPoint convertToProject(Coordinate _coordinate);
    ofPoint mercator(Coordinate _coordinate);
    ofPoint equirectangular(Coordinate _coordinate);
    ofPoint azimuthal(Coordinate _coordinate);
    ofPoint spherical(Coordinate _coordinate);
    void setMode(ofx_geo_json_mode _mode);
    void setScale(float scale);
    void setTranslate(float _transelateX, float _transelateY);
    void draw();
    vector< ofPtr<ofMesh> > getFeature(string name);
  
private:
    const float E_R = 6378.137; // Earth radius
    ofx_geo_json_mode mode;
    float scale;
    float translateX;
    float translateY;
    float pvRadians(float degrees);
    map<string, ofxGeoJSONFeature> features;
    ofxJSONElement result;
};

#endif
