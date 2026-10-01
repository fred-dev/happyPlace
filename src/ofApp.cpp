#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    codedColour = true;
    takecolor("mary source.jpeg");
    ofSetBackgroundColor(255);     //framerate(30);
    
    ofSetFrameRate(50);

    resetAll();
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
  
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofTranslate((ofGetWidth() - dimension)/2, (ofGetHeight()-dimension)/2,0);
    for (int c=0;c<num;c++) {
        friends[c].move();
    }
    for (int f=0;f<num;f++) {
        friends[f].expose();
        exposeConnections(f);
    }
    if (time%2==0){
        findHappyPlace();
    }
    time++;
    
    for (int c=0;c<num;c++) {

        for (int i =0; i<3; i++) {
            friends[c].sands[i].sandMesh.draw();
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    

    if (key == 'r') {
        resetAll();
    }
    
    if(key == 's'){
        ofSaveScreen(ofGetTimestampString()+ ".png");
    }
    
    if(key == 'S'){
        string date = ofGetTimestampString();
        ofMesh saveMeshCol1, saveMeshCol2, saveMeshCol3;
        for (int c=0;c<num;c++) {
            
            for (int i =0; i<3; i++) {
                if(friends[c].sands[i].sandMesh.getColors().size()> 0){

                    if (ofColor(friends[c].sands[i].sandMesh.getColor(0)).r == 147 && ofColor(friends[c].sands[i].sandMesh.getColor(0)).g == 255 && ofColor(friends[c].sands[i].sandMesh.getColor(0)).b == 216) {
                        saveMeshCol1.append(friends[c].sands[i].sandMesh);

                    }
                    else if (ofColor(friends[c].sands[i].sandMesh.getColor(0)).r == 255 && ofColor(friends[c].sands[i].sandMesh.getColor(0)).g == 166 && ofColor(friends[c].sands[i].sandMesh.getColor(0)).b == 158) {
                        saveMeshCol2.append(friends[c].sands[i].sandMesh);

                    }
                    else if (ofColor(friends[c].sands[i].sandMesh.getColor(0)).r == 70 && ofColor(friends[c].sands[i].sandMesh.getColor(0)).g == 34 && ofColor(friends[c].sands[i].sandMesh.getColor(0)).b == 85) {
                        saveMeshCol3.append(friends[c].sands[i].sandMesh);

                    }
                }
                
            }
        }
        
        saveMeshCol1.save(date +  "_col_1.ply");
        saveMeshCol2.save(date +  "_col_2.ply");
        saveMeshCol3.save(date +  "_col_3.ply");
    }
   
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

void ofApp::resetAll() {
    // make some friend entities
    for (int x=0;x<num;x++) {
        float fx = dimension/2 + 0.4*dimension*cos(TWO_PI*x/num);
        float fy = dimension/2 + 0.4* dimension*sin(TWO_PI*x/num);
        friends[x].initFriend(fx,fy,x,somecolor());
        for(int i = 0; i < 3;  i++){
            friends[x].sands[i].sandMesh.clear();
        }
    }
    
    // make some random friend connections
    for (int k=0;k<num*2.2;k++) {
        
        int a = int(floor(ofRandom(num)));
        int b = int(floor(a+ int(ofRandom(22) ) % num));
        if (b>=num) {
            b=0;
        } else if (b<0) {
            b=0;
        }
        if (a!=b) {
            friends[a].connectTo(b);
            friends[b].connectTo(a);
        }
    }
    
}



ofColor ofApp::somecolor() {
    // pick some random good color
    return goodcolor[int(ofRandom(0, maxpal))];
}

void ofApp::takecolor(string fn) {
    if (codedColour) {
        for (int i = 0 ; i < maxpal - 3; i+=3) {
            goodcolor[i] = ofColor(147,255,216,255);
            goodcolor[i+1] = ofColor(255,166,158,255);
            goodcolor[i+2] = ofColor(70,34,85,255);
        }
    }
    else{
        ofImage b;
        b.load(fn);
        
        int colourGrabHStep;
        int colourGrabVStep;
        
        colourGrabHStep =  b.getWidth()/ 32;
        colourGrabVStep = b.getHeight()/ 16;
        
        for (int j = 0; j < 16; j++) {
            for (int i = 0; i <32; i++) {
                

                goodcolor[ ((j * 32 + i))] = b.getColor( (i *colourGrabHStep),  (j *colourGrabVStep));


            }
        }
    }
    

    
//    // pump black and white in
//    for (int x=0;x<22;x++) {
//        goodcolor[numpal]=ofColor(0);
//        numpal++;
//        goodcolor[numpal]=ofColor(255);
//        numpal++;
//    }
    
    //    for (int i = 0 ; i < maxpal ; i++) {
    //        cout << ofToString(goodcolor[i])<<endl;
    //    }
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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

void ofApp::findHappyPlace(){
    // set destination to a happier place
    // (closer to friends, further from others)
    
    for (int jumpCounter =0; jumpCounter < num; jumpCounter++) {
        float ax = 0.0;
        float ay = 0.0;
        
        for (int n=0;n<num;n++) {
           
            if (n != jumpCounter) {
     
                
                float ddx = friends[n].x-friends[jumpCounter].x;
                float ddy = friends[n].y-friends[jumpCounter].y;
                
                float d = sqrt(ddx*ddx + ddy*ddy);
                float t = atan2(ddy,ddx);
                
                bool isFriend = false;
                for (int j=0;j<friends[jumpCounter].numcon;j++){
                    if (friends[jumpCounter].connections[j]==n){
                        isFriend=true;
                        
                    }
                    if (isFriend) {
                        // attract
                        if (d>friends[jumpCounter].lencon) {
                            ax += 4.0*cos(t);
                            ay += 4.0*sin(t);
                        }
                    } else {
                        // repulse
                        if (d<friends[jumpCounter].lencon) {
                            ax += (friends[jumpCounter].lencon-d)*cos(t+PI);
                            ay += (friends[jumpCounter].lencon-d)*sin(t+PI);
                        }
                    }
                }
                
                
            }
        }
        friends[jumpCounter].vx+=ax/42.22;
        friends[jumpCounter].vy+=ay/42.22;
    }
    // find mean average of all friends and non-friends
    
}

void ofApp::exposeConnections(int friendFinder) {
    // draw connection lines to all friends
    for (int n=0;n<friends[friendFinder].numcon;n++) {
        // find axis distances
        float ox = friends[friends[friendFinder].connections[n]].x;
        float oy = friends[friends[friendFinder].connections[n]].y;
        
        for (int s=0;s<friends[friendFinder].numsands;s++) {
            friends[friendFinder].sands[s].render(friends[friendFinder].x,friends[friendFinder].y,ox,oy);
        }
    }
}
