/**
 * Inspector.cpp
 * emptyExample
 *
 * Created by Marek Bereza on 01/07/2011.
 *
 */

#include "Inspector.h"
#include "Instantiator.h"
using namespace gui;
Inspector::Inspector(): Container() {
	width = 150;
	addControl("Inspector", "title", NULL);
	
	setLayoutType(LayoutType_vertical);
	x = 10;
	y = 20;

	addListener(this);
	
}
void gui::Inspector::clearControls() {
	// 1 is the title
	while(children.size()>1) {
		
		Control *c = children.back();
		children.pop_back();
		delete c;
	}
}
void gui::Inspector::addControl(string id, string type, void *pointer) {
	Control *c = INSTANTIATE(type);
	c->id = id;
	c->name = id;
	if(pointer!=NULL) {
		c->pointToValue(pointer);
	}
	addChild(c);
	c->x = 5;
	c->width = width - 10;
}

void gui::Inspector::setControl(Control *currentControl) {
	
	// a new control has been selected so we need to load a new set of Inspector controls 
	this->currentControl = currentControl;
	clearControls();
	
	if(this->currentControl!=NULL) {

		
		addControl("id",	"textfield",	&this->currentControl->id);
		addControl("name",  "textfield",    &this->currentControl->name);
		addControl("x",		"floatfield",	&this->currentControl->x);
		addControl("y",		"floatfield",	&this->currentControl->y);
		addControl("width",	"floatfield",	&this->currentControl->width);
		addControl("height","floatfield",	&this->currentControl->height);
		

				
		
		vector<ParameterInfo> paramInfo;
		currentControl->getParameterInfo(paramInfo);
		for(int i = 0; i < paramInfo.size(); i++) {
			addControl(paramInfo[i].name, paramInfo[i].type, paramInfo[i].value);
		}
		addControl("reload", "pushbutton", NULL);
	}
}

void gui::Inspector::controlChanged(Control *ctrl) {
	// reload a control if it's file has changed
	if((ctrl->id=="reload" || ctrl->type=="file") && this->currentControl!=NULL) {
		this->currentControl->load();
	}
}

void gui::Inspector::draw() {
	x = ofGetWidth() - width;
	if(children.size()>0) {
		height = children.back()->y+children.back()->height + 5;
	}
	ofSetHexColor(0x002244);
	ofRect(x, y, width, height);
	Container::draw();
}