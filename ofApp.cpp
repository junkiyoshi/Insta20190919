#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofNoFill();
	ofEnableDepthTest();

	int len = 400;
	int span = len * 0.1;
	for (int x = len * -0.5; x < len * 0.5; x += span) {

		for (int y = len * -0.5; y < len * 0.5; y += span) {

			int z = len * 0.5;
			for (int i = 0; i < 4; i++) {

				auto rotation_y = glm::rotate(glm::mat4(), (float)(i * 90 * DEG_TO_RAD), glm::vec3(0, 1, 0));

				vector<glm::vec3> rect;
				rect.push_back(glm::vec4(x, y, z, 0) * rotation_y);
				rect.push_back(glm::vec4(x + span, y, z, 0) * rotation_y);
				rect.push_back(glm::vec4(x + span, y + span, z, 0) * rotation_y);
				rect.push_back(glm::vec4(x, y + span, z, 0) * rotation_y);
				this->base_rect_list.push_back(rect);
			}

			for (int i = 0; i < 2; i++) {

				auto rotation_x = glm::rotate(glm::mat4(), (float)((90 + i * 180) * DEG_TO_RAD), glm::vec3(1, 0, 0));

				vector<glm::vec3> rect;
				rect.push_back(glm::vec4(x, y, z, 0) * rotation_x);
				rect.push_back(glm::vec4(x + span, y, z, 0) * rotation_x);
				rect.push_back(glm::vec4(x + span, y + span, z, 0) * rotation_x);
				rect.push_back(glm::vec4(x, y + span, z, 0) * rotation_x);
				this->base_rect_list.push_back(rect);
			}
		}
	}
}


//--------------------------------------------------------------
void ofApp::update() {

	this->draw_rect_list.clear();
	for (auto& base_rect : this->base_rect_list) {

		vector<glm::vec3> draw_rect;
		for (auto& point : base_rect) {

			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(point.y * 0.001 + ofGetFrameNum() * 0.015), 0, 1, -PI, PI), glm::vec3(0, 1, 0));
			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(point.x * 0.001 + ofGetFrameNum() * 0.015), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
			glm::vec3 location = glm::vec4(point, 0) * rotation_y * rotation_x;

			draw_rect.push_back(location);
		}

		this->draw_rect_list.push_back(draw_rect);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (auto& rect : this->draw_rect_list) {

		vector<glm::vec3> fill_rect;
		for (auto& point : rect) {

			fill_rect.push_back(point * 0.99);
		}

		ofFill();
		ofSetColor(239);
		ofBeginShape();
		ofVertices(fill_rect);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		ofVertices(rect);
		ofEndShape(true);
	}

	this->cam.end();

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}