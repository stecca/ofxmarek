/**
 * Resources.h
 * emptyExample
 *
 * Created by Marek Bereza on 29/06/2011.
 *
 */
#pragma once
#include "ofMain.h"

namespace gui {
	class Resources {
	public:
		static void drawString(string str, int x, int y);
		static ofTrueTypeFont *font;
		static ofImage *getImage(string path);
		
	private:
		static bool customFontNotAvailable;
		static map<string,ofImage*> images;
	};
};