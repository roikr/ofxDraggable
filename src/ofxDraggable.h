//
//  ofxDraggable.h
//  imageLoaderExample
//
//  Created by Roee Kremer on 6/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"

class ofxDraggable {
  public:
    void setup(ofMatrix4x4 mat);
    void begin();
    void end();
    

    void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);
	void touchCancelled(ofTouchEventArgs &touch);
    
        
    vector<ofTouchEventArgs> touches;
    
    
    ofMatrix4x4 mat;
    ofMatrix4x4 imat;
    
    
};
