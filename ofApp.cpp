#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	float span = 3;
	vector<ofColor> color_list = { ofColor(255, 0, 0), ofColor(0, 255, 0), ofColor(0, 0, 255) };
	for (int i = 0; i < color_list.size(); i++) {

		ofMesh mesh;
		auto noise_value = ofRandom(1000);

		for (float x = 75; x < ofGetWindowWidth() - 10 - span - 75; x += span) {

			for (float y = 75; y < ofGetWindowHeight() - 10 - span - 75; y += span) {

				if ((int)(x - 75) % 200 < 150 && (int)(y - 75) % 200 < 150) {

					mesh.addVertex(glm::vec3(x, y, 0));
					mesh.addVertex(glm::vec3(x + span, y, 0));
					mesh.addVertex(glm::vec3(x + span, y + span, 0));
					mesh.addVertex(glm::vec3(x, y + span, 0));

					for (int k = mesh.getNumVertices() - 4; k < mesh.getNumVertices(); k++) {

						auto noise_value = ofNoise(mesh.getVertex(k).x * 0.01, mesh.getVertex(k).y * 0.01, ofGetFrameNum() * 0.08 + i * 0.15);
						int int_noise_value = noise_value;
						float param = noise_value - int_noise_value;
						param = abs(param - 0.5);

						auto color = ofColor(color_list[i], param < 0.15 ? ofMap(param, 0, 0.15, 255, 0) : 0);
						mesh.addColor(color);
					}

					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 3);
					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 3); mesh.addIndex(mesh.getNumVertices() - 4);
				}
			}
		}

		mesh.draw();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}