#pragma once

#include "Loader.h"
#include "FontRenderer.h"

class TextMaster
{

private:
	Loader loader;

	//a map of fontTypes containing a list of each text needing to be rendered
	std::unordered_map<FontType*, std::vector<GUIText*>, hash_textMap, equal_textMap> texts;
	FontRenderer* renderer;

public:

#pragma region void init(Loader loader, DisplayManager* display)
	/// Constructs the loader
	void init(Loader loader, DisplayManager* display);
#pragma endregion

#pragma region void render();
	/// Simply renders all of the text by calling the FontRenderer's render method
	void render();
#pragma endregion

#pragma region void loadText(GUIText* text);
	/// Loads the text and adds it to the screen
	/// Find which font this text is using
	/// create the quads using the font.loadText
	/// load up these quods using loadToVao
	/// Set the VAO to the text
	/// Then, find which list this font needs to be added to (the texts map)
	/// add it to an existing one or null one
	void loadText(GUIText* text);
#pragma endregion

#pragma region void removeText(GUIText* text);
	/// Removes text from the screen
	void removeText(GUIText* text);
#pragma endregion

	void cleanUp();
};

